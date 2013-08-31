using System;

namespace VCEngine
{
	public class EntryPoint
	{
		public EntryPoint ()
		{
			Console.WriteLine ("Managed: VCEngine.EntryPoint::CTor()");


			Console.WriteLine ("Managed: Creating GameObject, CameraObject");
			GameObject cameraObject = new GameObject ();
			cameraObject.Transform.SetPosition (50, -25, -120);
			cameraObject.Transform.SetRotationEler (0, 0.7f, 0);

			Console.WriteLine ("Managed: Creating Camera");
			Camera camera = new Camera ();
			cameraObject.AttachComponent (camera);
		}


	}
}

