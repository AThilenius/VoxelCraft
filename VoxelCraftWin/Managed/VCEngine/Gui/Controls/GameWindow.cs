using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class GameWindow : Control
    {
        public World World;

        // Selection
        private bool m_isEyedrop;
        private bool m_isCircle;
        private Random m_random = new Random();
        private bool m_suppressUp;
        private Location m_startLocation;

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
        }

        protected override void Update()
        {
            if (!IsHovered)
                return;

            // Ray cast
            Ray ray = World.Camera.ScreenPointToRay(GlfwInputState.MouseLocation, 1000);
            RaycastHit hit;

            if (World.Raycast(ray, out hit))
            {
                Vector3 block = new Vector3(hit.CubeLocation);
                Location blockLoc = hit.CubeLocation;
                Vector3 normalBlock = block + hit.Normal;
                Location normalBlockLoc = new Location(normalBlock);

                if (GlfwInputState.MouseStates[0].State == TriState.None && GlfwInputState.MouseStates[1].State == TriState.None)
                    World.Camera.Debug.DrawCube(normalBlock - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);

                // Set start / Eye Dropper out
                if (GlfwInputState.MouseStates[0].State == TriState.Pressed)
                {
                    if (m_isEyedrop)
                    {
                        m_isEyedrop = false;
                        m_suppressUp = true;
                        EditorGui.ColorPicker.ColorRGB = World.GetBlock(block).Color;
                    }

                    else
                    {
                        m_startLocation = normalBlockLoc;
                        m_suppressUp = false;
                    }
                }

                // Highlight blocks
                else if (GlfwInputState.MouseStates[0].State == TriState.Replete && !m_suppressUp)
                {
                    if (m_isCircle)
                    {
                        int distance = (int)Math.Abs((normalBlock - new Vector3(m_startLocation)).Length);
                        foreach (Location loc in World.GetBlocksInSphere(m_startLocation, distance))
                            World.Camera.Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);
                    }

                    else
                    {
                        foreach (Location loc in World.GetBlocksInRegion(normalBlockLoc, m_startLocation))
                            World.Camera.Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);
                    }
                }

                // Set all blocks between start and end
                else if (GlfwInputState.MouseStates[0].State == TriState.Up && !m_suppressUp)
                {
                    float Value = EditorGui.RandomColorFactor.Value;

                    if (m_isCircle)
                    {
                        int distance = (int)Math.Abs((normalBlock - new Vector3(m_startLocation)).Length);
                        foreach (Location loc in World.GetBlocksInSphere(m_startLocation, distance))
                        {
                            float RandOffset = (float)m_random.NextDouble() * Value - (Value * 0.5f);
                            Vector4 hsl = EditorGui.ColorPicker.ColorHSL;
                            hsl.Z += RandOffset;
                            hsl.Z = MathHelper.Clamp(hsl.Z, 0.0f, 1.0f);
                            Color c = Color.HslToRgba(hsl);

                            if (loc.Y > 0)
                                World.SetBlock(loc, new Block(c));
                        }

                        m_isCircle = false;
                    }

                    else
                    {
                        foreach (Location loc in World.GetBlocksInRegion(normalBlockLoc, m_startLocation))
                        {
                            float RandOffset = (float)m_random.NextDouble() * Value - (Value * 0.5f);
                            Vector4 hsl = EditorGui.ColorPicker.ColorHSL;
                            hsl.Z += RandOffset;
                            hsl.Z = MathHelper.Clamp(hsl.Z, 0.0f, 1.0f);
                            Color c = Color.HslToRgba(hsl);

                            if (loc.Y > 0)
                                World.SetBlock(loc, new Block(c));
                        }
                    }

                    World.ReBuild();
                }

                // Set Start
                if (GlfwInputState.MouseStates[1].State == TriState.Pressed)
                    m_startLocation = blockLoc;

                // Highlight blocks
                else if (GlfwInputState.MouseStates[1].State == TriState.Replete)
                {
                    foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                        if (loc.Y > 0)
                            World.Camera.Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlRed);
                }

                // Set all blocks between start and end
                else if (GlfwInputState.MouseStates[1].State == TriState.Up)
                {
                    foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                        if (loc.Y > 0)
                            World.SetBlock(loc, Block.Empty);

                    World.ReBuild();
                }

            }

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
            m_isEyedrop = true;
        }

        internal void RequestCircle()
        {
            m_isCircle = true;
        }

    }
}
