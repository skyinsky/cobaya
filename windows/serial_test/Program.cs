using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.IO.Ports;

namespace ConsoleApplication1
{
        class Program
    {
        static void Main(string[] args)
        {
            string port;
            SerialPort _serialPort;

            if (args.Length != 1)
            {
                Console.WriteLine("serial_test comx");
                return;
            }

            try
            {
                port = args[0];

                // Create a new SerialPort object with default settings.
                _serialPort = new SerialPort();

                // Allow the user to set the appropriate properties.
                _serialPort.PortName = port;
                _serialPort.BaudRate = 9600;
                _serialPort.Parity = Parity.None;
                _serialPort.DataBits = 8;
                _serialPort.StopBits = StopBits.One;
                _serialPort.Handshake = Handshake.None;

                // Set the read/write timeouts
                _serialPort.ReadTimeout = 10000;
                //_serialPort.WriteTimeout = 10000;

                _serialPort.Open();

                while (true)
                {
                    //int val = _serialPort.ReadChar();
                    string line = _serialPort.ReadLine();

                    Console.WriteLine(line);
                }
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (TimeoutException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
