using SaNi.CodeGenerator.ClassGenerator;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                Console.WriteLine("usage:");
                Console.WriteLine("\targs[0] = in class definition file");
                Console.WriteLine("\targs[1] = out C# class file");

                return;
            }
            else
            {
                var inPath = args[0];
                var outPath = args[1];

                if (!File.Exists(inPath))
                {
                    Console.WriteLine("in file does not exist!");
                    return;
                }

                if (!File.Exists(outPath))
                {
                    Console.WriteLine("out file does not exists, creating...");
                    CreateOutFile(outPath);
                }

                Console.WriteLine("Parsing class definition...");
                var classDefinition = Parse(inPath);

                if (classDefinition == null) return;

                Console.WriteLine("Generating code...");
                var code = classDefinition.ToString();

                Console.WriteLine("Saving C# class file...");
                Write(outPath, code);

                Console.WriteLine("All ok, file saved at " + outPath);
                Console.WriteLine("");
            }
        }

        private static void CreateOutFile(string outPath)
        {
            File.Create(outPath);
        }
        private static void WriteResults(string outPath, string contents)
        {
            File.WriteAllText(outPath, contents);
        }

        private static bool IsClassDefinitionFile(string[] lines)
        {
            return lines.First() == StringConsts.ClassDefinition;
        }
        private static string[] ReadInFile(string inPath)
        {
            var lines = File.ReadAllLines(inPath);
            lines = LinkFiles(lines.ToList());

            if (lines == null)
            {
                Console.WriteLine("LNK errors ocurred, stopping parsing");

                return null;
            }

            var results = lines
                .Where(l => !string.IsNullOrEmpty(l))
                .Select(l => l.Replace("\t", "").Trim())
                .Where(l => !l.StartsWith(StringConsts.Comment));
            
            return results.ToArray();
        }
        private static string[] LinkFiles(List<string> results)
        {
            foreach (var line in results)
            {
                if (line.StartsWith(StringConsts.IncludeProperties))
                {
                    Console.WriteLine("LNK: PROPS " + line.Split(' ').Last().Trim());
                    
                    if (!LinkProperties(results, line)) return null;
                    
                    LinkFiles(results);

                    break;
                }
                if (line.StartsWith(StringConsts.IncludeMethods))
                {
                    Console.WriteLine("LNK: METHODS " + line.Split(' ').Last().Trim());
                    
                    if (!LinkMethods(results, line)) return null;

                    LinkFiles(results);

                    break;
                }
            }

            return results.ToArray();
        }
        private static bool Link(List<string> lines, string line, string what)
        {
            var path = line.Split(' ').Last();
            var includeLine = line;

            if (!File.Exists(path))
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("LNK error, file not found - \"" + line + "\", skipping...");
                Console.ResetColor();

                return false;
            }

            var linesToLink = File.ReadAllLines(path)
                .Where(l => !string.IsNullOrEmpty(l))
                .Select(l => l.Replace("\t", "").Trim())
                .Where(l => !l.StartsWith(StringConsts.Comment))
                .ToArray();

            var i = 0;
            var toInsert = new List<string>();

            while (i < linesToLink.Length)
            {
                line = linesToLink[i];

                if (line.StartsWith(what))
                {
                    // Extract.
                    toInsert.Add(linesToLink[i]);
                    toInsert.Add(linesToLink[i + 1]);
                    
                    // Pre inc skip cur.
                    i++;

                    // Inc + get.
                    while (!linesToLink[i].StartsWith(what)) toInsert.Add(linesToLink[++i]);

                    // Post inc skip cur.
                    i++;
                }

                // Next.
                i++;
            }

            // Insert lines we linked.
            lines.InsertRange(lines.IndexOf(includeLine), toInsert);
            // Remove include directive.
            lines.Remove(includeLine);

            return true;
        }
        private static bool LinkProperties(List<string> lines, string line)
        {
            return Link(lines, line, StringConsts.PropertyDefinition);
        }
        private static bool LinkMethods(List<string> lines, string line)
        {
            return Link(lines, line, StringConsts.MethodDefinition);
        }

        private static ClassDefinition Parse(string inFile)
        {
            var lines = ReadInFile(inFile);

            if (lines == null) return null;

            var name = string.Empty;
            var ns   = string.Empty;
            
            var settings = ClassSettings.None;
            
            var properties  = new List<PropertyDefinition>();
            var methods     = new List<MethodDefinition>();

            var i = 0;

            while (i < lines.Length)
            {
                var line = lines[i];

                if      (line.StartsWith(StringConsts.ClassDefinition))            ParseClass(lines, ref name, ref ns, ref settings, ref i);
                else if (line.StartsWith(StringConsts.PropertyDefinition))         ParseProperty(lines, properties, ref i);
                else if (line.StartsWith(StringConsts.MethodDefinition))           ParseMethod(lines, methods, ref i);
                else
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine("invalid line found, skipping...");
                    Console.ResetColor();

                    i++;
                }
            }

            return new ClassDefinition(name, ns, settings, properties, methods);
        }
        private static void ParseClass(string[] lines, ref string name, ref string ns, ref ClassSettings settings, ref int i)
        {
            var line = lines[i];

            line = line.Replace(StringConsts.ClassDefinition, "").Trim();

            name    = line.Substring(line.LastIndexOf(".") + 1).Trim();
            ns      = line.Substring(0, line.LastIndexOf(".")).Replace(name, "").Trim();

            var names   = Enum.GetNames(typeof(ClassSettings));
            var values  = Enum.GetValues(typeof(ClassSettings)).Cast<int>().ToArray();

            while (i < lines.Length)
            {
                line = lines[++i];

                if (line == StringConsts.ClassDefinition)
                {
                    i++;

                    break;
                }

                if (names.Contains(line)) settings |= (ClassSettings)values[Array.IndexOf(names, line)];
                else 
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("invalid class setting name \"" + line + "\", skipping...");
                    Console.ResetColor();
                }
            }
        }
        private static void ParseProperty(string[] lines, List<PropertyDefinition> properties, ref int i)
        {
            var line = lines[i];

            if (line == StringConsts.PropertyDefinition)
            {
                // Empty header definition, normally end of an def.
                i++;

                return;
            }

            line = line.Replace(StringConsts.PropertyDefinition, "").Trim();

            var typename        = line.Substring(0, line.LastIndexOf(" ")).Trim();
            var name            = line.Substring(line.LastIndexOf(" ")).Trim();

            var propSettingsNames  = Enum.GetNames(typeof(PropertySettings));
            var propSettingsValues = Enum.GetValues(typeof(PropertySettings)).Cast<int>().ToArray();
            
            var propReadSettingsNames  = Enum.GetNames(typeof(PropertyReadSettings));
            var propReadSettingsValues = Enum.GetValues(typeof(PropertyReadSettings)).Cast<int>().ToArray();

            var propSettings     = PropertySettings.None;
            var propReadSettings = PropertyReadSettings.None;

            while (i < lines.Length)
            {
                line = lines[++i];

                // Do not inc i since this can be an header for new def, 
                // not an ending!
                if (line.StartsWith(StringConsts.PropertyDefinition)) break;

                if      (propSettingsNames.Contains(line))           propSettings |= (PropertySettings)propSettingsValues[Array.IndexOf(propSettingsNames, line)];
                else if (propReadSettingsNames.Contains(line))       propReadSettings |= (PropertyReadSettings)propReadSettingsValues[Array.IndexOf(propReadSettingsNames, line)];
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("invalid property setting name \"" + line + "\", skipping...");
                    Console.ResetColor();
                }
            }

            if (propReadSettings == PropertyReadSettings.None)
            {
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine("no read settings found for prop " + name + "!" + " using default settings..."); Console.ResetColor();
                Console.ResetColor();

                propReadSettings = PropertyReadSettings.Default;
            }

            properties.Add(new PropertyDefinition(name, typename, propSettings, propReadSettings));
        }
        private static void ParseMethod(string[] lines, List<MethodDefinition> methods, ref int i)
        {
            var line = lines[i];

            if (line == StringConsts.MethodDefinition)
            {
                i++;

                return;
            }

            line = line.Replace(StringConsts.MethodDefinition, "").Trim();

            var tokens = line.Split(' ');

            var typename    = tokens[0].Trim();
            var name        = tokens[1].Trim();
            var args        = tokens.Length > 2 ? tokens[2].Replace("(", "").Replace(")", "").Trim() : String.Empty;

            var settingNames = Enum.GetNames(typeof(MethodSettings)).ToArray();
            var settingValues = Enum.GetValues(typeof(MethodSettings)).Cast<int>().ToArray();

            var settings = MethodSettings.None;

            while (i < lines.Length)
            {
                line = lines[++i];

                if (line.StartsWith(StringConsts.MethodDefinition)) break;

                if (settingNames.Contains(line)) settings |= (MethodSettings)settingValues[Array.IndexOf(settingNames, line)];
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("invalid method setting name \"" + line + "\", skipping...");
                    Console.ResetColor();
                }
            }

            methods.Add(new MethodDefinition(name, typename, args, settings));
        }

        private static void Write(string outFile, string code) 
        {
            File.WriteAllText(outFile, code);
        }
    }
}
