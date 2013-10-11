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

		public static void Initialize()
		{
            AppDomain.CurrentDomain.UnhandledException += (obj, e) => Console.WriteLine(e.ExceptionObject.ToString());

            try
            {
                SceneGraph.RootNode = new GameObject();
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
                Input.Start();

                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.Start();

                SceneGraph.RootNode.PropagateStart();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
        }

        public static void Update() 
		{
            try
            {
                Time.Update();
                Gui.PreUpdate();
                Debug.Reset();

                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.Update();

                SceneGraph.RootNode.PropagateUpdate();
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
                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.LateUpdate();

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
                foreach (StaticInstance inst in AssemblyLoader.StaticInstances)
                    inst.PreRender();

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

