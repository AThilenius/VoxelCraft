using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VCEngine;

namespace TestGame
{
    public class Config : StaticInstance
    {
        private Camera m_camera;
        private World m_world;

        public override void Start()
        {
            Gui.LoadFontsFromForlder(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\Fonts");

            m_camera = new Camera();
            m_camera.Transform.Position = new Vector3(20, 80, 20);
            SimpleFPSController simpleController = new SimpleFPSController();
            m_camera.AttachComponent(simpleController);

            m_world = new World();
            m_world.Generator = new FlatChunkGenerator();
            m_world.ViewDistance = 4;
            m_world.Initialize();
            m_world.GenerateRegenerate();
            m_world.ReBuild();
        }

        public override void Update()
        {
            Gui.DrawBorderedRect(new Rectangle(1100, 138, 150, 25), Color.ControlDisabled, Color.ControlBorder, 1);
            Gui.DrawString("Hello Managed GUI!", new Point(1100, 138), Color.Black, "Lucida Sans-13-Bold");

            //if (Input.GetMouse(0) == TriState.Pressed)
            //{
            //    Console.Write("Raycasting... ");
            //    Ray ray = m_camera.ScreenPointToRay(0, 0);
            //    RaycastHit hit;

            //    if (m_world.Raycast(ray, out hit))
            //    {
            //        Console.WriteLine("Hit at: " + hit.X + ", " + hit.Y + ", " + hit.Z + ". Normal: " + hit.Normal);
            //        Vector3 block = new Vector3(hit.X, hit.Y, hit.Z) + hit.Normal;
            //        m_world.SetBlock(block, new Block(255, 0, 0, 255));
            //        m_world.ReBuild();
            //    }
            //    else
            //        Console.WriteLine("Missed");

            //}

            //if (Input.GetMouse(1) == TriState.Pressed)
            //{
            //    Ray ray = m_camera.ScreenPointToRay(0, 0);
            //    RaycastHit hit;

            //    if (m_world.Raycast(ray, out hit))
            //    {
            //        m_world.SetBlock(hit.X, hit.Y, hit.Z, new Block(0, 0, 0, 0));
            //        m_world.ReBuild();
            //    }

            //}
        }

    }
}
