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
        public UndoStack<BlockChangeUndoToken> UndoStack = new UndoStack<BlockChangeUndoToken>();
        
        // Camera
        private float m_speed = 20.0f;
        private Vector3 m_rot = new Vector3(0.5f, -0.2f, 0);
        private Point m_startPosition;

        // Diagnostics
        private float m_lastDeltaTime = 0.001f;
        private int m_yOffset = 0;

        public GameWindow(int viewDistance)
        {
            BackgroundColor = Color.Trasparent;
            DrawHover = false;

            World = new World();
            World.ViewDistance = viewDistance;
            World.Initialize();
            World.Camera.Fullscreen = false;
            World.Camera.Transform.Position = new Vector3(50, 20, 50);
            World.Camera.Transform.Rotation = Quaternion.FromEuler(m_rot);
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

            // Undo / ReDo
            if (GlfwInputState.KeyStates[Input.Keys.LeftControl].State != TriState.None &&
                GlfwInputState.KeyStates[Input.Keys.LeftAlt].State == TriState.None &&
                GlfwInputState.KeyStates['Z'].State == TriState.Pressed)
                UndoStack.UndoLast();

            if (GlfwInputState.KeyStates[Input.Keys.LeftControl].State != TriState.None &&
                GlfwInputState.KeyStates[Input.Keys.LeftAlt].State != TriState.None &&
                GlfwInputState.KeyStates['Z'].State == TriState.Pressed)
                UndoStack.ReDoLast();
            

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

        protected override void Draw()
        {
            base.Draw();
            Rectangle sf = ScreenFrame;

            m_lastDeltaTime = 0.95f * m_lastDeltaTime + 0.05f * Time.DeltaTime;
            m_yOffset = 20;

            DrawText("Frame Time: " + (int)Math.Round(m_lastDeltaTime * 1000.0f) + " ms.", sf);
            DrawText("Estimated FPS: " + (int)Math.Round(1.0f / m_lastDeltaTime), sf);
            DrawText("Resolution: " + Window.Size, sf);


            // Outline each chunk World (Should be fine to invoke from a draw call...)
            for (int x = 0; x < World.ViewDistance; x++)
                for (int y = 0; y < World.ViewDistance; y++)
                    for (int z = 0; z < World.ViewDistance; z++)
                        World.Camera.Debug.DrawCube(new Vector3(x * 32, y * 32, z * 32), Vector3.One * 32, Color.ControlGreen);

            for (int x = 1; x < World.ViewDistance * 32; x++)
                World.Camera.Debug.DrawLine(new Vector3(x, 1, 0), new Vector3(x, 1, World.ViewDistance * 32), Color.ControlGreen);

            for (int z = 1; z < World.ViewDistance * 32; z++)
                World.Camera.Debug.DrawLine(new Vector3(0, 1, z), new Vector3(World.ViewDistance * 32, 1, z), Color.ControlGreen);
        }

        private void DrawText(string text, Rectangle sf)
        {
            Font.DrawString(text, new Point(sf.X + 5, sf.Y + sf.Height - m_yOffset), Color.White);
            m_yOffset += 20;
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
