using System;
using TestGame;
using VCEngine;

namespace VCEngine
{
	public class Engine : VCEngineCore
	{
        private Camera m_camera;

		public override void Initalize ()
		{
			base.Initalize ();

            Console.WriteLine("= Creating Camera");
            m_camera = new Camera();
            m_camera.Transform.Position = new Vector3(0, -25, -50);

            SimpleFPSController simpleController = new SimpleFPSController();
            m_camera.AttachComponent(simpleController);
		}

        public override void Start()
        {
            base.Start();
        }

		public override void Update ()
		{
			base.Update ();
		}

		public override void LateUpdate ()
		{
			base.LateUpdate ();
		}

        public override void PreRender()
        {
            base.PreRender();
        }

	}
}

