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
            Console.WriteLine("= Creating Camera");
            m_camera = new Camera();
            m_camera.Transform.Position = new Vector3(0, -25, -50);

            SimpleFPSController simpleController = new SimpleFPSController();
            m_camera.AttachComponent(simpleController);
        }

        public override void Update()
        {
            Gui.Clear();

            Gui.DrawRectangle(new Rectangle(100, 100, 250, 40), Color.Black);
            Gui.DrawString("Hello Managed GUI!", new Point(110, 135), Color.White);
        }

    }
}
