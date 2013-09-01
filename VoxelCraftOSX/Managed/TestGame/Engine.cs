using System;
using VCEngine;

namespace VCEngine
{
	public class Engine : VCEngineCore
	{
		// For now it MUST be overridden. I'll find a work around later
		public override void Initalize ()
		{
			base.Initalize ();
			Console.WriteLine ("= Engine::Intalize");

			Console.WriteLine ("= Creating GameObject, CameraObject");
			GameObject cameraObject = new GameObject ();
			cameraObject.Transform.Position = new Vector3(50, -25, -120);
			cameraObject.Transform.Rotation = new Quaternion(0, 20.0f * 0.0174532925f, 0);
			//cameraObject.Transform.SetRotationEler (0, 0.7f, 0);

			Console.WriteLine ("= Got: " + cameraObject.Transform.Position);

			Console.WriteLine ("= Creating Camera");
			Camera camera = new Camera ();
			cameraObject.AttachComponent (camera);
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

