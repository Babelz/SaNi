using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    public sealed class WrappedProperty
    {
        #region Properties
        public string Name
        {
            get;
            private set;
        }
        public bool GenerateBackingField
        {
            get;
            private set;
        }
        public string Typename
        {
            get;
            private set;
        }
        public PropertySettings PropertyFlags
        {
            get;
            private set;
        }
        public PropertyReadSettings ReadFlags
        {
            get;
            private set;
        }
        #endregion

        public WrappedProperty(string name, bool generateBackingField, string typename, PropertySettings propertyFlags, PropertyReadSettings readFlags)
        {
            Name                    = name;
            GenerateBackingField    = generateBackingField;
            Typename                = typename;
            PropertyFlags           = propertyFlags;
            ReadFlags               = readFlags;
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }
        public override string ToString()
        {
            var sb = new StringBuilder();

            // Property header.
            sb.Append("public ");
            sb.Append(Typename);
            sb.Append(" ");
            sb.Append(Name);
            sb.Append("\n{\n");

            if ((PropertyFlags & PropertySettings.Get) == PropertySettings.Get)
            {
                // Generate getter.
                sb.Append("get\n{\n");

                var field = string.Empty;

                if (GenerateBackingField)
                {
                    field = Name.ToLower();
                }
                else
                {
                    sb.Append(Typename);
                    sb.Append(" value = new ");
                    sb.Append(Typename);
                    sb.Append("();\n");

                    field = "value";
                }
                
                var head = string.Empty;
                
                if ((ReadFlags & PropertyReadSettings.Default) == PropertyReadSettings.Default)          head = field;
                else if ((ReadFlags & PropertyReadSettings.Reference) == PropertyReadSettings.Reference) head = "ref " + field;
                else                                                                                     throw new InvalidOperationException("invalid get flags");

                sb.Append("Get");
                sb.Append(Name);
                sb.Append("(");
                sb.Append(head);
                sb.Append(");\n");
                sb.Append("return ");
                sb.Append(field);
                sb.Append(";\n}\n");
            }
            if ((PropertyFlags & PropertySettings.Set) == PropertySettings.Set)
            {
                // Generate setter.
                sb.Append("set\n{\n");
                sb.Append("Set");
                sb.Append(Name);
                sb.Append("(");
                sb.Append("value);\n}");
            }

            sb.Append("\n}\n");

            return sb.ToString();
        }

        public string GetBackingField()
        {
            if (!GenerateBackingField) return string.Empty;

            return string.Format("{0} {1} {2};\n", "private", Typename, Name.ToLower());
        }
        public string GetBackingFieldInitializer()
        {
            if (!GenerateBackingField) return string.Empty;

            return string.Format("{0} = new {1}();\n", Name.ToLower(), Typename);
        }
    }
}
