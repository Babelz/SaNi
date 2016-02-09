using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Tests
{
    internal enum TestExecutionMethod
    {
        Unsafe,
        Safe
    }

    internal sealed class PerformanceTestCase
    {
        #region Fields
        private readonly Stopwatch timer;

        private readonly string name;
        private readonly ITest test;
        #endregion

        #region Properties
        public TimeSpan Time
        {
            get
            {
                return timer.Elapsed;
            }
        }
        public string Name
        {
            get
            {
                return name;
            }
        }
        #endregion

        public PerformanceTestCase(string name, ITest test)
        {
            if (string.IsNullOrEmpty(name)) throw new ArgumentNullException("name");
            if (test == null) throw new ArgumentNullException("test");

            this.name = name;
            this.test = test;

            timer = new Stopwatch();
        }

        private void UnsafeRunTest()
        {
            test.Run();
        }
        private void SafeRunTest()
        {
            try
            {
                test.Run();
            }
            catch (Exception e)
            {
                Console.WriteLine("An exception occured while running test \"{0}\", exception message: {1}", name, e.Message);
            }
        }

        public void Run(TestExecutionMethod testExecutionMethod)
        {
            timer.Reset();

            Console.WriteLine("Running test: {0}", name);

            timer.Start();

            switch (testExecutionMethod)
            {
                case TestExecutionMethod.Unsafe:
                    UnsafeRunTest();
                    break;
                case TestExecutionMethod.Safe:
                    SafeRunTest();
                    break;
            }

            timer.Stop();

            Console.WriteLine("Test complete: {0}\n", name);
        }
    }
}
