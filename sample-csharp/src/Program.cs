using System;
using System.Diagnostics;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using R3E.Data;

namespace R3E
{
    class Sample : IDisposable
    {
        private bool Mapped 
        {
            get { return (_file != null && _view != null); }
        }

        private MemoryMappedFile _file;
        private MemoryMappedViewAccessor _view;

        private readonly TimeSpan _timeAlive = TimeSpan.FromMinutes(10);
        private readonly TimeSpan _timeInterval = TimeSpan.FromMilliseconds(100);

        public void Dispose()
        {
            _view.Dispose();
            _file.Dispose();
        }

        public void Run()
        {
            var timeReset = DateTime.UtcNow;
            var timeLast = timeReset;

            Console.WriteLine("Looking for RRRE.exe...");

            while(true)
            {
                var timeNow = DateTime.UtcNow;

                if(timeNow.Subtract(timeReset) > _timeAlive)
                {
                    break;
                }

                if(timeNow.Subtract(timeLast) < _timeInterval)
                {
                    Thread.Sleep(1);
                    continue;
                }

                timeLast = timeNow;

                if(Utilities.IsRrreRunning() && !Mapped)
                {
                    Console.WriteLine("Found RRRE.exe, mapping shared memory...");

                    if(Map())
                    {
                        Console.WriteLine("Memory mapped successfully");
                        timeReset = DateTime.UtcNow;
                    }
                }

                if(Mapped)
                {
                    Print();
                }
            }

            Console.WriteLine("All done!");
        }

        private bool Map()
        {
            try
            {
                _file = MemoryMappedFile.OpenExisting(Constant.SharedMemoryName);
                _view = _file.CreateViewAccessor(0, Marshal.SizeOf(typeof(Shared)));
                return true;
            }
            catch(FileNotFoundException)
            {
                return false;
            }
        }

        private void Print()
        {
            Shared data;
            _view.Read(0, out data);

	        if(data.Gear >= -1)
	        {
				Console.WriteLine("Gear: {0}", data.Gear);
	        }

	        if(data.EngineRps > -1.0f)
	        {
				Console.WriteLine("RPM: {0}", Utilities.RpsToRpm(data.EngineRps));
		        Console.WriteLine("Speed: {0}", Utilities.MpsToKph(data.CarSpeed));
	        }

            Console.WriteLine("");
        }
    }

    class Program
    {
        static void MainSafe(string[] args)
        {
            using(var sample = new Sample())
            {
                sample.Run();
            }
        }

        static void Main(string[] args)
        {
            if(Debugger.IsAttached)
            {
                MainSafe(args);
            }
            else
            {
                try
                {
                    MainSafe(args);
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }
            }
        }
    }
}
