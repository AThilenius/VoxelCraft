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
            World.ViewDistance = 2;
            World.Initialize();
            World.GenerateRegenerate();
            World.SetBlock(0, 0, 0, new Block(0, 254, 0, 254));
            World.ReBuild();
        }

        internal static void ResetWorld()
        {
            World.Dispose();
            World = null;

            World = new World();
            World.Generator = new FlatChunkGenerator();
            World.ViewDistance = 1;
            World.Initialize();
            World.GenerateRegenerate();
            World.ReBuild();
        }

    }
}
