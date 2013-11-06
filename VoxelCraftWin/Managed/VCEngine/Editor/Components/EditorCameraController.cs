using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorCameraController : Component
    {
        private float m_speed = 20.0f;
        private Vector3 m_rot = new Vector3(0.5f, -0.2f, 0);
        private Point m_startPosition;

        public override void Update()
        {
            if (Input.GetMouse(2) == TriState.Pressed || Input.GetMouse(3) == TriState.Pressed || Input.GetMouse(4) == TriState.Pressed)
            {
                m_startPosition = Input.MousePoistion;
                Input.MouseMode = MouseMoveMode.Locked;
            }

            if (Input.GetMouse(2) != TriState.None || Input.GetMouse(3) != TriState.None || Input.GetMouse(4) != TriState.None)
            {
                m_rot.X -= Input.DeltaLook.Y * 0.0174532925f * 0.1f;
                m_rot.Y += Input.DeltaLook.X * 0.0174532925f * 0.1f;
            }

            if (Input.GetMouse(2) == TriState.Up || Input.GetMouse(3) == TriState.Up || Input.GetMouse(4) == TriState.Up)
            {
                Input.MouseMode = MouseMoveMode.Free;
                Input.MousePoistion = m_startPosition;
            }

            if (Input.GetKey(Input.Keys.LeftControl) != TriState.None)
                m_speed = 5.0f;
            else
                m_speed = 20.0f;

            m_rot.X = MathHelper.Clamp(m_rot.X, MathHelper.DegreesToRadians(-89.0f), MathHelper.DegreesToRadians(89.0f));

            Transform.Rotation = Quaternion.FromEuler(m_rot);

            Vector3 forward = Transform.Rotation.Forward;
            forward.Y = 0;
            forward.Normalize();
            forward *= Input.Strafe.X * Time.DeltaTime * m_speed;

            Transform.Position -= forward;
            Transform.Position -= Transform.Rotation.Right * Input.Strafe.Y * Time.DeltaTime * m_speed;

            if (Input.GetKey(Input.Keys.LeftShift) != TriState.None)
                Transform.Position -= Vector3.UnitY * Time.DeltaTime * m_speed;

            if (Input.GetKey(' ') != TriState.None)
                Transform.Position += Vector3.UnitY * Time.DeltaTime * m_speed;
        }

    }
}
