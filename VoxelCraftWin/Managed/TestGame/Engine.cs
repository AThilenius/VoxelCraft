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

            Ray ray = new Ray
            {
                Origin = new Vector3(0.5f, 252, 0.5f),
                Direction = new Vector3( 0.0f, -1.0f, 0.0f ),
                MaxDistance = 1000.0f
            };
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                Console.WriteLine("Ray-cast hit: " + hit);
            }

            else
            {
                Console.WriteLine("Ray-cast did not hit :( " + hit);
            }
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

