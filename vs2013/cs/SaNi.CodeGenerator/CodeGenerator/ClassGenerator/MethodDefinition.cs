using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    public sealed class MethodDefinition
    {
        #region Properties
        public string Name
        {
            get;
            private set;
        }
        public string ReturnTypename
        {
            get;
            private set;
        }
        public string Args 
        {
            get;
            private set;
        }
        public MethodSettings MethodFlags
        {
            get;
            private set;
        }
        #endregion

        public MethodDefinition(string name, string returnTypename, string args, MethodSettings methodFlags)
        {
            Name            = name;
            ReturnTypename  = returnTypename;
            Args            = args;
            MethodFlags     = methodFlags;
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }
        public override string ToString()
        {
            var format = "{0} {1} {2}({3}){4}";
            
            // Check for errors.
            if (!MethodSettingsHelper.HasOneAccessModifierToggled(MethodFlags))
            {
                throw new InvalidOperationException("too many access modifier specified");
            }

            var attributes      = MethodSettingsHelper.GetAttributes(MethodFlags);
            var accessModifier  = MethodSettingsHelper.GetAccessModifier(MethodFlags);
            var keywords        = MethodSettingsHelper.GetKeywords(MethodFlags);
            var body            = MethodSettingsHelper.GetMethodBody(MethodFlags);

            var method          = string.Format(format, accessModifier, keywords, Name, Args, body);

            // Check if we need to append attributes to the beginning.
            if (!string.IsNullOrEmpty(attributes)) method = attributes + "\n" + method;

            return method;
        }
    }
}
