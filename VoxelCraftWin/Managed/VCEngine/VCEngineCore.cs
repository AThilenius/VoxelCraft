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
        public VCEngineCore()
        {
            AppDomain.CurrentDomain.UnhandledException += UnhandledExceptionOccurred;

            Console.WriteLine("VCEngineCore::CTor");
        }

        private static void UnhandledExceptionOccurred(object sender, UnhandledExceptionEventArgs e)
        {
            Console.WriteLine(e.ExceptionObject.ToString());
        }

		public void Initialize()
		{
			Console.WriteLine ("= VCEngineCore::Initialize");
            try
            {
                SceneGraph.RootNode = new GameObject();

                Console.WriteLine("Loading: ");
                Console.WriteLine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\TestGame.dll");
                AssemblyLoader.UseAssembly(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\TestGame.dll");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();
            }
		}

        public void Start()
        {
            try
            {
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

        public void Update() 
		{
            try
            {
                Time.Update();
                Input.Update();

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

		public void LateUpdate() 
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

        public void PreRender()
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

