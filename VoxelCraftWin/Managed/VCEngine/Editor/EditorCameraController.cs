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
        private bool m_isEyedrop;

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


            // Ray
            Ray ray = Camera.MainCamera.ScreenPointToRay(Input.MousePoistion, 1000);
            RaycastHit hit;

            if (EditorWorld.World.Raycast(ray, out hit))
            {
                Vector3 block = new Vector3(hit.X, hit.Y, hit.Z);
                Vector3 normalBlock = new Vector3(hit.X, hit.Y, hit.Z) + hit.Normal;
                Debug.DrawCube(block - new Vector3(0.1f, 0.1f, 0.1f), new Vector3(1.2f, 1.2f, 1.2f), Color.ControlGreen);

                if (Input.GetMouse(0) == TriState.Pressed)
                {
                    if (m_isEyedrop)
                    {
                        m_isEyedrop = false;
                        EditorGui.ColorPicker.ColorRGB = EditorWorld.World.GetBlock(block).Color;
                    }

                    else
                    {
                        EditorWorld.World.SetBlock(normalBlock, new Block(EditorGui.ColorPicker.ColorRGB));
                        EditorWorld.World.ReBuild();
                    }
                }

                if (Input.GetMouse(1) == TriState.Pressed && block.Y > 0)
                {
                    EditorWorld.World.SetBlock(hit.X, hit.Y, hit.Z, new Block(0, 0, 0, 0));
                    EditorWorld.World.ReBuild();
                }
            }

            Debug.DrawCube(Vector3.Zero, Vector3.One * 32 * EditorWorld.World.ViewDistance, Color.ControlGreen);
        }

        internal void RequestEyeDrop()
        {
            m_isEyedrop = true;
        }
    }
}
