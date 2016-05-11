using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    public sealed class MethodDefinition
    {
        #region Fields
        private readonly string name;
        private readonly string returnType;
        private readonly string args;

        private MethodSettings settings;
        #endregion

        #region Properties
        public int Weight
        {
            get
            {
                if ((settings & MethodSettings.Private) == MethodSettings.Private)       return 1;
                if ((settings & MethodSettings.Protected) == MethodSettings.Protected)   return 2;
                if ((settings & MethodSettings.Public) == MethodSettings.Public)         return 3;

                throw new InvalidOperationException("invalid access modifier");
            }
        }
        #endregion

        public MethodDefinition(string name, string returnTypename, string args, MethodSettings settings)
        {
            this.name        = name;
            this.returnType  = returnTypename;
            this.args        = args;
            this.settings    = settings;
        }

        public override int GetHashCode()
        {
            return name.GetHashCode();
        }
        public override string ToString()
        {
            var format = "{0} {1} {2} {3}({4}){5}\n\n";
            
            // Check for errors.
            if (!MethodSettingsHelper.HasOneAccessModifierToggled(settings))
            {
                throw new InvalidOperationException("too many access modifier specified");
            }

            var attributes      = MethodSettingsHelper.GetAttributes(settings);
            var accessModifier  = MethodSettingsHelper.GetAccessModifier(settings);
            var keywords        = MethodSettingsHelper.GetKeywords(settings);
            var body            = MethodSettingsHelper.GetMethodBody(settings);

            var method          = string.Format(format, accessModifier, keywords, returnType, name, args, body);

            // Check if we need to append attributes to the beginning.
            if (!string.IsNullOrEmpty(attributes)) method = attributes + "\n" + method;

            return method;
        }
    }
}
