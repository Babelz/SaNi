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
        private readonly List<WrappedProperty> properties;
        
        private readonly List<MethodDefinition> methods;
        #endregion

        #region Properties
        public IEnumerable<WrappedProperty> Properties
        {
            get
            {
                return properties;
            }
        }
        public IEnumerable<MethodDefinition> Methods
        {
            get
            {
                return methods;
            }
        }
        #endregion

        public ClassDefinition(List<WrappedProperty> properties, List<MethodDefinition> methods, ClassSettings settings)
        {

        }
    }
}
