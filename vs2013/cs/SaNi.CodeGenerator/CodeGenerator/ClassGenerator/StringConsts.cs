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
    }
}
