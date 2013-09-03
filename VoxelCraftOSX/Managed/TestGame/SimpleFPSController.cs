using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VCEngine;

namespace TestGame
{
    public class SimpleFPSController : Component
    {

        public Vector3 m_rot = Vector3.Zero;

        public override void Update()
        {
            m_rot.X += Input.Look.Y * 2;
            m_rot.Y += Input.Look.X * 2;

            if (m_rot.X > 90.0f * 0.0174532925f)
                m_rot.X = 90.0f *0.0174532925f;

            if (m_rot.X < -90.0f * 0.0174532925f)
                m_rot.X = -90.0f *0.0174532925f;

            Transform.Rotation = Quaternion.FromEuler(m_rot);

            Vector3 forward = Vector3.UnitZ;
            forward = Vector3.Transform(forward, Transform.Rotation);

            Vector3 right = Vector3.UnitX;
            right = Vector3.Transform(right, Transform.Rotation);

            Transform.Position += forward * Input.Strafe.X * 0.25f;
            Transform.Position += right * Input.Strafe.Y * 0.25f;
        }

    }
}
