using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VCEngine;

namespace TestGame
{
    public class SimpleFPSController : Component
    {

        public Vector3 m_rot = new Vector3(1.5f, 0, 0);
        Point m_startPosition;

        public override void Update()
        {
            if (Input.GetMouse(1) == TriState.Pressed)
            {
                m_startPosition = Input.MousePoistion;
                Input.MouseMode = MouseMoveMode.Locked;
            }

            if (Input.GetMouse(1) != TriState.None)
            {
                m_rot.X -= Input.DeltaLook.Y * 0.0174532925f * 0.1f;
                m_rot.Y += Input.DeltaLook.X * 0.0174532925f * 0.1f;
            }

            if (Input.GetMouse(1) == TriState.Up)
            {
                Input.MouseMode = MouseMoveMode.Free;
                Input.MousePoistion = m_startPosition;
            }

            if (m_rot.X > 90.0f * 0.0174532925f)
                m_rot.X = 90.0f *0.0174532925f;

            if (m_rot.X < -90.0f * 0.0174532925f)
                m_rot.X = -90.0f *0.0174532925f;

            Transform.Rotation = Quaternion.FromEuler(m_rot);

            Transform.Position -= Transform.Rotation.Forward * Input.Strafe.X * Time.DeltaTime * 10.0f;
            Transform.Position -= Transform.Rotation.Right * Input.Strafe.Y * Time.DeltaTime * 10.0f;
        }

    }
}
