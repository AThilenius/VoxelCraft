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

        float next;
		public override void Update ()
		{
			base.Update ();

            //if (Time.TotalTime > next)
            //{
                Ray ray = m_camera.ScreenPointToRay(640, 400);

                RaycastHit hit;
                if (Physics.Raycast(ray, out hit))
                    Console.WriteLine("Hit: " + hit.X + " | " + hit.Y + " | " + hit.Z);

                else
                    Console.WriteLine("Missed. Ray: " + ray);

                next = Time.TotalTime + 1.0f;
            //}
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

