using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TestFixture
    {
        static RenderWindow m_renderWindow;
        static RenderedEntity m_entity;

        public static PxScene scene;
        public static PxMaterial material;
        public static PxShape boxShape;
        public static PxShape planeShape;
        public static PxRigidStatic floor;
        public static PxRigidDynamic box;

        internal static void OnStart()
        {
            m_renderWindow = new RenderWindow();
            m_renderWindow.MainCamera.Fullscreen = true;
            //m_renderWindow.MainCamera.Viewport = new Rectangle(0, 0, 1280, 600);

            m_entity = new RenderedEntity();
            m_entity.Transform.Position = new Vector3(0, -5, -20);

            m_renderWindow.Entities.Add(m_entity);

            scene = new PxScene();
            material = new PxMaterial(0.5f, 0.5f, 0.5f);

            boxShape = PxShape.CreateBoxShape(material, new Vector3(0.5f, 0.5f, 0.5f));
            planeShape = PxShape.CreatePlaneShape(material);

            floor = new PxRigidStatic(Vector3.Zero, Quaternion.FromAxisAngle(Vector3.UnitZ, (float)Math.PI / 2.0f));
            floor.AttachShape(planeShape);

            box = new PxRigidDynamic(new Vector3(0, 10, 0), Quaternion.Identity);
            box.AttachShape(boxShape);

            scene.AddActor(floor);
            scene.AddActor(box);
        }

        public static void PerUpdate()
        {
        }

        public static void LatePerUpdate()
        {
            scene.Simulate();
        }


    }
}
