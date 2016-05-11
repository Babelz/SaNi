using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    public sealed class PropertyDefinition
    {
        #region Fields
        private string name;
        private string typename;

        private bool backingField;
        
        private PropertySettings propertySettings;
        private PropertyReadSettings readSettings;
        #endregion

        #region Properties
        public bool GenerateBackingField
        {
            get
            {
                return backingField;
            }
        }
        #endregion

        public PropertyDefinition(string name, bool backingField, string typename, PropertySettings propertySettings, PropertyReadSettings readSettings)
        {
            this.name               = name;
            this.backingField       = backingField;
            this.typename           = typename;
            this.propertySettings   = propertySettings;
            this.readSettings       = readSettings;
        }

        public override int GetHashCode()
        {
            return name.GetHashCode();
        }
        public override string ToString()
        {
            var sb = new StringBuilder();

            // Property header.
            sb.Append("public ");
            sb.Append(typename);
            sb.Append(" ");
            sb.Append(name);
            sb.Append("\n{\n");

            if ((propertySettings & PropertySettings.Get) == PropertySettings.Get)
            {
                // Generate getter.
                sb.Append("get\n{\n");

                var field = string.Empty;

                if (backingField)
                {
                    field = name.ToLower();
                }
                else
                {
                    sb.Append(typename);
                    sb.Append(" value = new ");
                    sb.Append(typename);
                    sb.Append("();\n");

                    field = "value";
                }
                
                var args = string.Empty;
                
                if      ((readSettings & PropertyReadSettings.Default) == PropertyReadSettings.Default)          args = field;
                else if ((readSettings & PropertyReadSettings.Reference) == PropertyReadSettings.Reference)      args = "ref " + field;
                else                                                                                             throw new InvalidOperationException("invalid get flags");

                sb.Append("Get");
                sb.Append(name);
                sb.Append("(");
                sb.Append(args);
                sb.Append(");\n");
                sb.Append("return ");
                sb.Append(field);
                sb.Append(";\n}\n");
            }

            if ((propertySettings & PropertySettings.Set) == PropertySettings.Set)
            {
                // Generate setter.
                sb.Append("set\n{\n");
                sb.Append("Set");
                sb.Append(name);
                sb.Append("(value);\n}");
            }

            sb.Append("\n}\n");

            return sb.ToString();
        }

        public string GetBackingField()
        {
            if (!backingField) return string.Empty;

            return string.Format("{0} {1} {2};\n", "private", typename, name.ToLower());
        }
        public string GetBackingFieldInitializer()
        {
            if (!backingField) return string.Empty;

            return string.Format("{0} = new {1}();\n", name.ToLower(), typename);
        }

        public string GetInternalGet()
        {
            var sb = new StringBuilder();

            sb.Append("[MethodImpl(MethodImplOptions.InternalCall)]\n");

            var args = string.Empty;
            
            if      ((readSettings & PropertyReadSettings.Default) == PropertyReadSettings.Default)          args = typename + " value";
            else if ((readSettings & PropertyReadSettings.Reference) == PropertyReadSettings.Reference)      args = "ref " + typename + " value";

            sb.Append("private extern void ");
            sb.Append("Get");
            sb.Append(name);
            sb.Append("(");
            sb.Append(args);
            sb.Append(");\n");

            return sb.ToString();
        }
        public string GetInternalSet()
        {
            var sb = new StringBuilder();

            sb.Append("[MethodImpl(MethodImplOptions.InternalCall)]\n");
            sb.Append("private extern void ");
            sb.Append("Set");
            sb.Append(name);
            sb.Append("(");
            sb.Append(typename);
            sb.Append(" ");
            sb.Append("value");
            sb.Append(");\n");

            return sb.ToString();
        }
    }
}
