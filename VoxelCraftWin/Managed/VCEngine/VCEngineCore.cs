using System;
using System.Runtime.CompilerServices;
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

            try
            {
                SceneGraph.RootNode = new GameObject();
                Window.Initialize();
                Gui.LoadFontsFromForlder(Environment.CurrentDirectory + @"\Resources\Fonts");

                if (!EditorMode)
                    AssemblyLoader.UseAssembly(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\TestGame.dll");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
		}

        public static void Start()
        {
            try
            {
                if (!EditorMode)
                {
                    foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                        inst.Start();
                }

                SceneGraph.RootNode.PropagateStart();

                TestFixture.OnStart();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

        internal static void PropagateUpdates()
        {
            VCEngineCore.Update();
            VCEngineCore.LateUpdate();
            VCEngineCore.PreRender();
        }
        public static void Update() 
		{
            try
            {
                Time.Update();
                Gui.PreUpdate();

                if (!EditorMode)
                {
                    foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                        inst.Update();
                }

                SceneGraph.RootNode.PropagateUpdate();

                // Debug
                TestFixture.PerUpdate();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
		}

        public static void LateUpdate() 
		{
            try
            {
                if (!EditorMode)
                {
                    foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                        inst.LateUpdate();
                }

                SceneGraph.RootNode.PropagateLateUpdate();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
		}

        public static void PreRender()
        {
            try
            {
                if (!EditorMode)
                {
                    foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                        inst.PreRender();
                }

                SceneGraph.RootNode.PropagatePreRender();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

    }
}

