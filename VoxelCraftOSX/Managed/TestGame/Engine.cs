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
            m_camera.Transform.Position = new Vector3(-100, 20, -120);
            //camera.Transform.Rotation = new Quaternion(0, 20.0f * 0.0174532925f, 0);

            //Console.WriteLine("= Position Check: " + m_camera.Transform.Position.ToString());
		}

		public override void Update ()
		{
			base.Update ();
		}

		public override void LateUpdate ()
		{
			base.LateUpdate ();
		}

	}
}

