using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class GameWindow : Control
    {
        public World World;

        // Active Tool
        public ModelTool ActiveTool;
        
        // Camera
        private float m_speed = 20.0f;
        private Vector3 m_rot = new Vector3(0.5f, -0.2f, 0);
        private Point m_startPosition;

        public GameWindow(int viewDistance)
        {
            BackgroundColor = Color.Trasparent;
            DrawHover = false;

            BorderColor = Color.ControlBlue;
            BorderWidth = 1;

            World = new World();
            World.Generator = new FlatChunkGenerator();
            World.ViewDistance = viewDistance;
            World.Initialize();
            World.Camera.Fullscreen = false;
            World.Camera.Transform.Position = new Vector3(50, 20, 50);
            World.Camera.Transform.Rotation = Quaternion.FromEuler(m_rot);
            World.GenerateRegenerate();
            World.ReBuild();

            Resize += GameWindow_Resize;

            // Default Tool
            ActiveTool = new BlockClickDragTool(this);
        }

        protected override void Update()
        {
            if (!IsHovered)
            {
                ActiveTool.Update(null);
                return;
            }

            // Ray cast
            Ray ray = World.Camera.ScreenPointToRay(GlfwInputState.MouseLocation, 1000);
            RaycastHit hit;

            // Pass tool update
            if (World.Raycast(ray, out hit))
                ActiveTool.Update(hit);

            else
                ActiveTool.Update(null);

            // Outline World
            World.Camera.Debug.DrawCube(Vector3.Zero, Vector3.One * 32 * World.ViewDistance, Color.ControlGreen);

            // Camera
            if (GlfwInputState.MouseStates[2].State == TriState.Pressed || 
                GlfwInputState.MouseStates[3].State == TriState.Pressed || 
                GlfwInputState.MouseStates[4].State == TriState.Pressed ||
                GlfwInputState.KeyStates[Input.Keys.LeftControl].State == TriState.Pressed )
            {
                m_startPosition = GlfwInputState.MouseLocation;
                GlfwInputState.MouseVisible = false;
            }

            if (GlfwInputState.MouseStates[2].State != TriState.None || 
                GlfwInputState.MouseStates[3].State != TriState.None ||
                GlfwInputState.MouseStates[4].State != TriState.None ||
                GlfwInputState.KeyStates[Input.Keys.LeftControl].State != TriState.None)
            {
                m_rot.X -= GlfwInputState.DeltaMouseLocation.Y * 0.0174532925f * 0.1f;
                m_rot.Y += GlfwInputState.DeltaMouseLocation.X * 0.0174532925f * 0.1f;
                GlfwInputState.MouseLocation = m_startPosition;
            }

            if (GlfwInputState.MouseStates[2].State == TriState.Up || 
                GlfwInputState.MouseStates[3].State == TriState.Up ||
                GlfwInputState.MouseStates[4].State == TriState.Up ||
                GlfwInputState.KeyStates[Input.Keys.LeftControl].State == TriState.Up)
            {
                GlfwInputState.MouseLocation = m_startPosition;
                GlfwInputState.MouseVisible = true;
            }

            m_rot.X = MathHelper.Clamp(m_rot.X, MathHelper.DegreesToRadians(-89.0f), MathHelper.DegreesToRadians(89.0f));
            World.Camera.Transform.Rotation = Quaternion.FromEuler(m_rot);

            if (GlfwInputState.KeyStates[Input.Keys.LeftControl].State != TriState.None)
                m_speed = 5.0f;
            else
                m_speed = 20.0f;

            Vector2 strafeVec = new Vector2(0.0f, 0.0f);

            if (GlfwInputState.KeyStates['W'].State != TriState.None) strafeVec.X += 1.0f;
            if (GlfwInputState.KeyStates['S'].State != TriState.None) strafeVec.X += -1.0f;

            if (GlfwInputState.KeyStates['A'].State != TriState.None) strafeVec.Y += 1.0f;
            if (GlfwInputState.KeyStates['D'].State != TriState.None) strafeVec.Y += -1.0f;

            if (strafeVec.X > 0.1f || strafeVec.X < -0.1f || strafeVec.Y > 0.1f || strafeVec.Y < -0.1f)
                strafeVec.Normalize();

            Vector3 forward = World.Camera.Transform.Rotation.Forward;
            forward.Y = 0;
            forward.Normalize();
            forward *= strafeVec.X * Time.DeltaTime * m_speed;

            World.Camera.Transform.Position -= forward;
            World.Camera.Transform.Position -= World.Camera.Transform.Rotation.Right * strafeVec.Y * Time.DeltaTime * m_speed;

            if (GlfwInputState.KeyStates[Input.Keys.LeftShift].State != TriState.None)
                World.Camera.Transform.Position -= Vector3.UnitY * Time.DeltaTime * m_speed;

            if (GlfwInputState.KeyStates[' '].State != TriState.None)
                World.Camera.Transform.Position += Vector3.UnitY * Time.DeltaTime * m_speed;
        }

        void GameWindow_Resize(object sender, ResizeEventArgs e)
        {
            World.Camera.Viewport = ScreenFrame;
            World.Camera.AspectRatio = (float)Frame.Width / (float)Frame.Height;
        }

        internal void RequestEyeDrop()
        {
            //m_isEyedrop = true;
        }

        internal void RequestCircle()
        {
            //m_isCircle = true;
        }

    }
}
