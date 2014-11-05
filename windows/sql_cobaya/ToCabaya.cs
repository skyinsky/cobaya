using System;
using System.IO;
using System.IO.Pipes;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;

public partial class StoredProcedures
{
    private static Object thisLock = new Object();
    private static NamedPipeClientStream pipe = new NamedPipeClientStream("cobaya_pipe");
    private static StreamWriter writer = new StreamWriter(pipe);

    [Microsoft.SqlServer.Server.SqlProcedure]
    public static void ToCabaya(string msg)
    {
        if (msg == null)
            return;
        bool retry = true;
        
        retry_once:
        try
        {
            lock (thisLock)
            {
                if (!pipe.IsConnected)
                {
                    pipe.Connect(1000);
                    writer.AutoFlush = true;
                }

                writer.WriteLine(msg);
            }
        }
        catch (Exception e)
        {
            if (retry && !pipe.IsConnected)
            {
                retry = false;
                goto retry_once;
            }

            SqlPipe sp = SqlContext.Pipe;

            sp.Send(e.Message);
        }
    }
};
