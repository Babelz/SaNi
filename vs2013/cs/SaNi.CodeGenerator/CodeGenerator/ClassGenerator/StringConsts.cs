using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    public static class StringConsts
    {
        public static readonly string FieldsRegionFormat            = "#region Fields\n{0}#endregion";
        public static readonly string PropertiesRegionFormat        = "#region Properties\n{0}#endregion";
        public static readonly string InternalGetSetRegionFormat    = "#region Internal get/set methods\n{0}#endregion";

        public static readonly string ClassDefinition               = "CLASS_DEF";
        
        public static readonly string PropertyDefinition            = "PROP_DEF";
        public static readonly string PropertyBackingField          = "BACKING_FIELD";

        public static readonly string MethodDefinition              = "METHOD_DEF";

        public static readonly string IncludeProperties             = "INCLUDE_PROPS";
        public static readonly string IncludeMethods                = "INCLUDE_METHODS";

        public static readonly string Comment                       = "--";
    }
}
