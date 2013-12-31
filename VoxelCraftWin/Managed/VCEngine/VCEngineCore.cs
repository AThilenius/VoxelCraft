using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Threading;
using System.IO;
using System.Reflection;
using System.Diagnostics;

namespace VCEngine
{
    public class VCEngineCore
    {
        public static bool EditorMode;

        public static void Initialize()
        {
            AppDomain.CurrentDomain.UnhandledException += (obj, e) => Console.WriteLine(e.ExceptionObject.ToString());

            SceneGraph.RootNode = new GameObject();
            Window.Initialize();

            if (!EditorMode)
                AssemblyLoader.UseAssembly(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\TestGame.dll");
        }

        public static void Start()
        {
            if (!EditorMode)
            {
                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.Start();
            }

            SceneGraph.RootNode.Start();

            TestFixture.OnStart();
        }

        internal static void PropagateUpdates()
        {
            VCEngineCore.Update();
            VCEngineCore.LateUpdate();
            VCEngineCore.PreRender();
        }
        public static void Update()
        {
            Time.Update();
            Gui.Reset();

            if (!EditorMode)
            {
                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.Update();
            }

            SceneGraph.RootNode.Update();

            // Debug
            TestFixture.PerUpdate();
        }

        public static void LateUpdate()
        {
            if (!EditorMode)
            {
                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.LateUpdate();
            }

            SceneGraph.RootNode.LateUpdate();
        }

        public static void PreRender()
        {
            if (!EditorMode)
            {
                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.PreRender();
            }

            SceneGraph.RootNode.PreRender();
        }

    }
}

