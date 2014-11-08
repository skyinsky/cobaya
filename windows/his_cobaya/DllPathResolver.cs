using System;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Collections.Generic;
using System.IO;

namespace cobaya
{

    public class DllPathResolver
    {
        static List<string> gAssemblyResolvePaths = new List<string>();
        static ResolveEventHandler gResolveHandler;

        static System.Reflection.Assembly OnAssemblyResolveFail(object sender, ResolveEventArgs args)
        {
            string dllName = args.Name.Substring(0, args.Name.IndexOf(",")) + ".dll";

            foreach (string resolvePath in gAssemblyResolvePaths)
            {
                string assemblyPath = Path.Combine(resolvePath, dllName);
                if (File.Exists(assemblyPath))
                {
                    //System.Console.WriteLine("DllPathResolver: Loading assembly from path: " + assemblyPath);
                    System.Reflection.Assembly tempAssembly = System.Reflection.Assembly.LoadFrom(assemblyPath);
                    return tempAssembly;
                }
            }
            return null;
        }

        static void AddPath(string dllPath)
        {
            dllPath = Path.GetFullPath(dllPath);
            if (!dllPath.EndsWith("\\"))
            {
                dllPath += "\\";
            }
            gAssemblyResolvePaths.Add(dllPath);
        }

        static string FindDistributionRootDir()
        {
            string codeBase = Assembly.GetExecutingAssembly().CodeBase;
            UriBuilder uri = new UriBuilder(codeBase);
            string path = Uri.UnescapeDataString(uri.Path);
            path = Path.GetDirectoryName(path);

            if (path == null || !Directory.Exists(path))
            {
                return "";
            }

            string dllPath =path + "\\RCFProto_NET.dll";
            if (File.Exists(dllPath))
            {
                return path;
            }

            return "";
        }

        public static bool Resolve()
        {
            // First, locate the root of the distribution, and use that to construct
            // paths for locating native DLL's.

            string rootDir = FindDistributionRootDir();
            if (rootDir == "")
                return false;

            string binRelativePath;
            if (IntPtr.Size == 4)
            {
                binRelativePath = "\\x86";
            }
            else
            {
                binRelativePath = "\\x64";
            }
            string rcfProtoBinDir = rootDir + binRelativePath;
            AddPath(rcfProtoBinDir);

            //string rcf = "rcf impl version is " + rcfProtoBinDir;
            //Log.WriteLog(rcf);

            string rcfProtoAssemblyDir = rootDir;
            AddPath(rcfProtoAssemblyDir);

            // Configure the assembly resolve handler (used to find .NET assemblies).
            gResolveHandler = new ResolveEventHandler(OnAssemblyResolveFail);
            AppDomain.CurrentDomain.AssemblyResolve += gResolveHandler;

            // Configure the PATH environment variable (used to find native DLL's).
            string envPath = Environment.GetEnvironmentVariable("PATH");
            foreach (string dllPath in gAssemblyResolvePaths)
            {
                envPath = envPath + ";" + dllPath;
            }
            Environment.SetEnvironmentVariable("PATH", envPath);

            return true;
        }

    }
}
