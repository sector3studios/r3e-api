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
            get { return (_file != null); }
        }

        private Shared _data;
        private MemoryMappedFile _file;
        private byte[] _buffer;

        private readonly TimeSpan _timeAlive = TimeSpan.FromMinutes(10);
        private readonly TimeSpan _timeInterval = TimeSpan.FromMilliseconds(100);

        public void Dispose()
        {
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

                        _buffer = new Byte[Marshal.SizeOf(typeof(Shared))];
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
                return true;
            }
            catch(FileNotFoundException)
            {
                return false;
            }
        }

        private bool Read()
        {
            try
            {
                var _view = _file.CreateViewStream();
                BinaryReader _stream = new BinaryReader(_view);
                _buffer = _stream.ReadBytes(Marshal.SizeOf(typeof(Shared)));
                GCHandle _handle = GCHandle.Alloc(_buffer, GCHandleType.Pinned);
                _data = (Shared)Marshal.PtrToStructure(_handle.AddrOfPinnedObject(), typeof(Shared));
                _handle.Free();

                return true;
            }
            catch(Exception)
            {
                return false;
            }
        }

        private void Print()
        {
            if (Read())
            {
                Console.WriteLine("Name: {0}", System.Text.Encoding.UTF8.GetString(_data.PlayerName).TrimEnd('\0'));

                if (_data.Gear >= -1)
                {
                    Console.WriteLine("Gear: {0}", _data.Gear);
                }

                if (_data.EngineRps > -1.0f)
                {
                    Console.WriteLine("RPM: {0}", Utilities.RpsToRpm(_data.EngineRps));
                    Console.WriteLine("Speed: {0}", Utilities.MpsToKph(_data.CarSpeed));
                }


                Console.WriteLine("");
            }
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
