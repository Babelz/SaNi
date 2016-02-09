using sanilib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Tests
{
    internal sealed class Program
    {
        [DllImport("sani dll.dll", CallingConvention = CallingConvention.StdCall)]
        [SuppressUnmanagedCodeSecurity()]
        internal static extern double run_sqrt(double val);
        
        [DllImport("sani dll.dll", CallingConvention = CallingConvention.StdCall)]
        [SuppressUnmanagedCodeSecurity()]
        internal static extern void long_job();

        #region Test classes and data

        const int Cases = 10000000;

        private sealed class CSharpSqrtTest : ITest
        {
            public void Run()
            {
                for (int i = 0; i < Cases; i++)
                {
                    double d = Math.Sqrt(i);
                }
            }
        }

        private sealed class CppPInvokeSqrtTest : ITest
        {
            public unsafe void Run()
            {
                for (int i = 0; i < Cases; i++)
                {
                    double d = run_sqrt(i);
                }
            }
        }
        private sealed class CppCliWrapperSqrtTest : ITest
        {

            public void Run()
            {
                var nativeWrapper = new NativeWrapper();

                for (int i = 0; i < Cases; i++)
                {
                    double d = nativeWrapper.run_sqrt(i);
                }
            }
        }

        private sealed class CSharpLongJobTest : ITest
        {
            private const int JobIterations = 1000000;

            public void Run()
            {
                int j = 0;
	            int i = 0; 
	
	            while (i < JobIterations) {
		            j++;
                    i++;
	            }
            }
        }

        private sealed class CppPInvokeLongJobTest: ITest
        {
            public void Run()
            {
                long_job();
            }
        }
        private sealed class CppCliWrapperLongJobTest : ITest
        {

            public void Run()
            {
                var nativeWrapper = new NativeWrapper();
                nativeWrapper.long_job();
            }
        }
        #endregion

        private static void Main(string[] args)
        {
            var tests = new PerformanceTestCase[] 
            {
                new PerformanceTestCase("C++ P\\Invoke sqrt", new CppPInvokeSqrtTest()),
                new PerformanceTestCase("C++\\CLI sqrt", new CppCliWrapperSqrtTest()),
                new PerformanceTestCase("C# sqrt", new CSharpSqrtTest()),

                new PerformanceTestCase("C++ P\\Invoke long job", new CppPInvokeLongJobTest()),
                new PerformanceTestCase("C++\\CLI long job", new CppCliWrapperLongJobTest()),
                new PerformanceTestCase("C# long job", new CSharpLongJobTest())
            };

            Array.ForEach(tests, t => t.Run(TestExecutionMethod.Unsafe));
            Array.ForEach(tests, t => Console.WriteLine("Time took by the \"{0}\" test: {1}ms", t.Name, Math.Round(t.Time.TotalMilliseconds, 2)));

            Console.ReadKey();
        }
    }
}
