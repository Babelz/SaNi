using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    public sealed class ClassDefinition
    {
        #region Fields
        private readonly ClassSettings settings;

        private readonly string name;
        private readonly string ns;

        private readonly List<PropertyDefinition> properties;
        
        private readonly List<MethodDefinition> methods;
        #endregion

        public ClassDefinition(string name, string ns, ClassSettings settings, List<PropertyDefinition> properties, List<MethodDefinition> methods)
        {
            this.name       = name;
            this.ns         = ns;
            this.settings   = settings;
            this.properties = properties;
            this.methods    = methods;
        }

        public override int GetHashCode()
        {
            return name.GetHashCode();
        }
        public override string ToString()
        {
            var sb = new StringBuilder();

            if (!ClassSettingsHelper.HasOneAccessModifierToggled(settings)) throw new InvalidOperationException("too many access modifiers");

            // Add namespace.
            sb.Append("namespace ");
            sb.Append(ns);
            sb.Append("\n{\n");
            
            // Add class header.
            var keywords = ClassSettingsHelper.GetKeywords(settings);
            sb.Append(keywords);
            sb.Append(" class ");
            sb.Append(name);
            sb.Append("\n{\n");

            // Gen fields.
            var fields = new StringBuilder();

            foreach (var property in properties) if (property.GenerateBackingField) fields.Append(property.GetBackingField());

            if (fields.Length != 0)
            {
                sb.Append(string.Format(StringConsts.FieldsRegionFormat, fields.ToString()));
                sb.Append("\n\n");
            }

            // Gen properties.
            var props = new StringBuilder();

            foreach (var property in properties) props.Append(property.ToString());

            sb.Append(string.Format(StringConsts.PropertiesRegionFormat, props.ToString()));
            sb.Append("\n\n");

            // Gen ctor.
            if ((settings & ClassSettings.Ctor) == ClassSettings.Ctor) 
            {
                sb.Append("public ");
                sb.Append(name);
                sb.Append("()\n{\n");

                foreach (var property in properties) if (property.GenerateBackingField) sb.Append(property.GetBackingFieldInitializer());

                sb.Append("\n}\n");
            }

            // Gen property methods.
            var propmethods = new StringBuilder();

            foreach (var property in properties)
            {
                var get = property.GetInternalGet();
                var set = property.GetInternalSet();

                if (!string.IsNullOrEmpty(get)) propmethods.Append(get);
                if (!string.IsNullOrEmpty(set)) propmethods.Append(set);

                propmethods.Append("\n");
            }

            var str = propmethods.ToString();
            str = str.Substring(0, str.LastIndexOf("\n"));

            sb.Append(string.Format(StringConsts.InternalGetSetRegionFormat, str));
            sb.Append("\n\n");

            // Gen methods.
            var methods = new StringBuilder();

            foreach (var method in this.methods.OrderBy(m => m.Weight)) methods.Append(method.ToString());

            sb.Append(methods.ToString());
            
            // Gen dtor.
            if ((settings & ClassSettings.Dtor) == ClassSettings.Dtor)
            {
                sb.Append("~");
                sb.Append(name);
                sb.Append("()\n{\n}\n");
            }

            sb.Append("\n}\n}\n");
            
            return sb.ToString();
        }
    }
}
