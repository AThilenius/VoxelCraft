using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VCEngine;

namespace TestGame
{
    public class SimpleFPSController : Component
    {

        public Vector3 m_rot = new Vector3(1.4f, 1.5f, 0);

        public override void Update()
        {
            m_rot.X += Input.Look.Y * 2;
            m_rot.Y += Input.Look.X * 2;

            if (m_rot.X > 90.0f * 0.0174532925f)
                m_rot.X = 90.0f *0.0174532925f;

            if (m_rot.X < -90.0f * 0.0174532925f)
                m_rot.X = -90.0f *0.0174532925f;

            Transform.Rotation = Quaternion.FromEuler(m_rot);

            Transform.Position -= Transform.Rotation.Forward * Input.Strafe.X * 0.25f;
            Transform.Position -= Transform.Rotation.Right * Input.Strafe.Y * 0.25f;
        }

    }
}
