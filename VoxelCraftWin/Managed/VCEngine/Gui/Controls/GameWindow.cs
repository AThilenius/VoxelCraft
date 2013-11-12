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
            World.GenerateRegenerate();
            World.ReBuild();

            Resize += GameWindow_Resize;
            GPMouseEvent += GameWindow_GPMouseEvent;
        }

        void GameWindow_Resize(object sender, ResizeEventArgs e)
        {
            World.Camera.Viewport = ScreenFrame;
            World.Camera.AspectRatio = (float)Frame.Width / (float)Frame.Height;
        }

        void GameWindow_GPMouseEvent(object sender, GPMouseEventArgs e)
        {
            // Ray cast
            Ray ray = World.Camera.ScreenPointToRay(e.MousePoistion, 1000);
            RaycastHit hit;

            if (World.Raycast(ray, out hit))
            {
                Vector3 block = new Vector3(hit.CubeLocation);
                Location blockLoc = hit.CubeLocation;
                Vector3 normalBlock = block + hit.Normal;
                Location normalBlockLoc = new Location(normalBlock);

                if (e.ButtonStates[0] == TriState.None && e.ButtonStates[1] == TriState.None)
                    Debug.DrawCube(normalBlock - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);

                // Set start / Eye Dropper out
                if (e.ButtonStates[0] == TriState.Pressed)
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
                else if (e.ButtonStates[0] == TriState.Replete && !m_suppressUp)
                {
                    if (m_isCircle)
                    {
                        int distance = (int)Math.Abs((normalBlock - new Vector3(m_startLocation)).Length);
                        foreach (Location loc in World.GetBlocksInSphere(m_startLocation, distance))
                            Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);
                    }

                    else
                    {
                        foreach (Location loc in World.GetBlocksInRegion(normalBlockLoc, m_startLocation))
                            Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);
                    }
                }

                // Set all blocks between start and end
                else if (e.ButtonStates[0] == TriState.Up && !m_suppressUp)
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
                if (e.ButtonStates[1] == TriState.Pressed)
                    m_startLocation = blockLoc;

                // Highlight blocks
                else if (e.ButtonStates[1] == TriState.Replete)
                {
                    foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                        if (loc.Y > 0)
                            Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlRed);
                }

                // Set all blocks between start and end
                else if (e.ButtonStates[1] == TriState.Up)
                {
                    foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                        if (loc.Y > 0)
                            World.SetBlock(loc, Block.Empty);

                    World.ReBuild();
                }

            }

            Debug.DrawCube(Vector3.Zero, Vector3.One * 32 * World.ViewDistance, Color.ControlGreen);

            // Camera
            if (e.ButtonStates[2] == TriState.Pressed || e.ButtonStates[3] == TriState.Pressed || e.ButtonStates[4] == TriState.Pressed)
            {
                m_startPosition = Input.MousePoistion;
                Input.MouseMode = MouseMoveMode.Locked;
            }

            if (e.ButtonStates[2] != TriState.None || e.ButtonStates[3] != TriState.None || e.ButtonStates[4] != TriState.None)
            {
                m_rot.X -= Input.DeltaLook.Y * 0.0174532925f * 0.1f;
                m_rot.Y += Input.DeltaLook.X * 0.0174532925f * 0.1f;
            }

            if (e.ButtonStates[2] == TriState.Up || e.ButtonStates[3] == TriState.Up || e.ButtonStates[4] == TriState.Up)
            {
                Input.MouseMode = MouseMoveMode.Free;
                Input.MousePoistion = m_startPosition;
            }

            //if (Input.GetKey(Input.Keys.LeftControl) != TriState.None)
            //    m_speed = 5.0f;
            //else
            //    m_speed = 20.0f;

            m_rot.X = MathHelper.Clamp(m_rot.X, MathHelper.DegreesToRadians(-89.0f), MathHelper.DegreesToRadians(89.0f));

            World.Camera.Transform.Rotation = Quaternion.FromEuler(m_rot);

            Vector3 forward = World.Camera.Transform.Rotation.Forward;
            forward.Y = 0;
            forward.Normalize();
            forward *= Input.Strafe.X * Time.DeltaTime * m_speed;

            World.Camera.Transform.Position -= forward;
            World.Camera.Transform.Position -= World.Camera.Transform.Rotation.Right * Input.Strafe.Y * Time.DeltaTime * m_speed;

            if (Input.GetKey(Input.Keys.LeftShift) != TriState.None)
                World.Camera.Transform.Position -= Vector3.UnitY * Time.DeltaTime * m_speed;

            if (Input.GetKey(' ') != TriState.None)
                World.Camera.Transform.Position += Vector3.UnitY * Time.DeltaTime * m_speed;
        }

        void GameWindow_RightClick(object sender, MouseEventArgs e)
        {
            throw new NotImplementedException();
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
