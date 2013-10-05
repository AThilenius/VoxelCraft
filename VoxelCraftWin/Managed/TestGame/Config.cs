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

        public override void Start()
        {
            Gui.LoadFontsFromForlder(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\Fonts");

            Console.WriteLine("= Creating Camera");
            m_camera = new Camera();
            m_camera.Transform.Position = new Vector3(20, 80, 20);

            SimpleFPSController simpleController = new SimpleFPSController();
            m_camera.AttachComponent(simpleController);

            //m_camera.AttachComponent(new RidgedBody());
        }

        public override void Update()
        {
            Gui.DrawBorderedRect(new Rectangle(1100, 138, 150, 25), Color.ControlDisabled, Color.ControlBorder, 1);
            Gui.DrawString("Hello Managed GUI!", new Point(1100, 138), Color.Black, "Lucida Sans-13-Bold");
        }

    }
}
