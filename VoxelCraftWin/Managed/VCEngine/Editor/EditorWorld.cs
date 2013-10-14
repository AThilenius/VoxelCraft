using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorWorld
    {
        internal static World World;
        internal static EditorCameraController CameraController;

        internal static void Initialize()
        {
            Camera.MainCamera = new Camera();
            Camera.MainCamera.Transform.Position = new Vector3(50, 20, 50);

            CameraController = new EditorCameraController();
            Camera.MainCamera.AttachComponent(CameraController);

            World = new World();
            World.Generator = new FlatChunkGenerator();
            World.ViewDistance = 4;
            World.Initialize();
            World.GenerateRegenerate();
            World.ReBuild();
        }

    }
}
