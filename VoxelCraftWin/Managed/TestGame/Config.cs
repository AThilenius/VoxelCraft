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

        float next;
        public override void Update()
        {
            base.Update();

            //if (Time.TotalTime > next)
            //{
            Ray ray = m_camera.ScreenPointToRay(640, 400);

            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
                Console.WriteLine("Hit: " + hit.X + " | " + hit.Y + " | " + hit.Z);

            else
                Console.WriteLine("Missed. Ray: " + ray);

            next = Time.TotalTime + 1.0f;
            //}
        }

    }
}
