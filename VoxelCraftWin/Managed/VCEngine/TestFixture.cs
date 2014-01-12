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

        internal static void OnStart()
        {
            m_renderWindow = new RenderWindow();
            m_renderWindow.MainCamera.Fullscreen = true;
            //m_renderWindow.MainCamera.Viewport = new Rectangle(0, 0, 1280, 600);

            m_entity = new RenderedEntity();
            m_entity.Transform.Position = new Vector3(0, -5, -20);

            m_renderWindow.Entities.Add(m_entity);

            PxScene scene = new PxScene();
            PxMaterial material = new PxMaterial(0.5f, 0.5f, 0.5f);

            Console.WriteLine("yoloswaghashtagleahiisahottie");
        }

        public static void PerUpdate()
        {
        }

        public static void LatePerUpdate()
        {
        }


    }
}
