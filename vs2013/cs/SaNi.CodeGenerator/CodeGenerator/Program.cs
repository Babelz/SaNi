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

                Console.WriteLine("Generating code...");
                var code = classDefinition.ToString();

                Console.WriteLine("Saving C# class file...");
                Write(outPath, code);

                Console.WriteLine("All ok, file saved at " + outPath);
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

            var results = lines.Where(l => !string.IsNullOrEmpty(l));
            results = results.Select(l => l.Trim());

            return results.ToArray();
        }

        private static ClassDefinition Parse(string inFile)
        {
            var lines = ReadInFile(inFile);

            var name = string.Empty;
            var ns   = string.Empty;
            
            var settings = ClassSettings.None;
            
            var properties  = new List<WrappedProperty>();
            var methods     = new List<MethodDefinition>();

            var i = 0;

            while (i < lines.Length)
            {
                var line = lines[i];

                if (line.StartsWith(StringConsts.ClassDefinition))            ParseClass(lines, ref name, ref ns, ref settings, ref i);
                else if (line.StartsWith(StringConsts.PropertyDefinition))    ParseProperty(lines, properties, ref i);
                else if (line.StartsWith(StringConsts.MethodDefinition))      ParseMethod(lines, methods, ref i);
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
        private static void ParseProperty(string[] lines, List<WrappedProperty> properties, ref int i)
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
            var backing         = false;

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

                // Special case.
                if (line == StringConsts.PropertyBackingField) backing = true;

                if (propSettingsNames.Contains(line))           propSettings |= (PropertySettings)propSettingsValues[Array.IndexOf(propSettingsNames, line)];
                else if (propReadSettingsNames.Contains(line))  propReadSettings |= (PropertyReadSettings)propReadSettingsValues[Array.IndexOf(propReadSettingsNames, line)];
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("invalid property setting name \"" + line + "\", skipping...");
                    Console.ResetColor();
                }
            }

            properties.Add(new WrappedProperty(name, backing, typename, propSettings, propReadSettings));
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
