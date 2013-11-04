using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorCameraController : Component
    {
        private Vector3 m_rot = new Vector3(0.5f, -0.2f, 0);
        private Point m_startPosition;

        public override void Update()
        {
            if (Input.GetKey(' ') == TriState.Pressed)
            {
                m_startPosition = Input.MousePoistion;
                Input.MouseMode = MouseMoveMode.Locked;
            }

            if (Input.GetKey(' ') != TriState.None)
            {
                m_rot.X -= Input.DeltaLook.Y * 0.0174532925f * 0.1f;
                m_rot.Y += Input.DeltaLook.X * 0.0174532925f * 0.1f;
            }

            if (Input.GetKey(' ') == TriState.Up)
            {
                Input.MouseMode = MouseMoveMode.Free;
                Input.MousePoistion = m_startPosition;
            }

            if (m_rot.X > 90.0f * 0.0174532925f)
                m_rot.X = 90.0f * 0.0174532925f;

            if (m_rot.X < -90.0f * 0.0174532925f)
                m_rot.X = -90.0f * 0.0174532925f;

            Transform.Rotation = Quaternion.FromEuler(m_rot);

            Transform.Position -= Transform.Rotation.Forward * Input.Strafe.X * Time.DeltaTime * 10.0f;
            Transform.Position -= Transform.Rotation.Right * Input.Strafe.Y * Time.DeltaTime * 10.0f;
        }

    }
}
