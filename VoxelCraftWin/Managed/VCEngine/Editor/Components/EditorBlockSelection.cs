using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EditorBlockSelection : Component
    {
        private bool m_isEyedrop;
        private Random m_random = new Random();
        private bool m_suppressUp;
        private Location m_startLocation;

        public override void Update()
        {
            // Ray cast
            Ray ray = Camera.MainCamera.ScreenPointToRay(Input.MousePoistion, 1000);
            RaycastHit hit;

            if (EditorWorld.World.Raycast(ray, out hit))
            {
                Vector3 block = new Vector3(hit.CubeLocation);
                Location blockLoc = hit.CubeLocation;
                Vector3 normalBlock = block + hit.Normal;
                Location normalBlockLoc = new Location (normalBlock);

                if (Input.GetMouse(0) == TriState.None && Input.GetMouse(1) == TriState.None)
                    Debug.DrawCube(block - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);

                // Set start / Eye Dropper out
                if (Input.GetMouse(0) == TriState.Pressed)
                {
                    if (m_isEyedrop)
                    {
                        m_isEyedrop = false;
                        m_suppressUp = true;
                        EditorGui.ColorPicker.ColorRGB = EditorWorld.World.GetBlock(block).Color;
                    }

                    else
                    {
                        m_startLocation = normalBlockLoc;
                        m_suppressUp = false;
                    }
                }

                // Highlight blocks
                else if (Input.GetMouse(0) == TriState.Replete && !m_suppressUp)
                {
                    foreach (Location loc in World.GetBlocksInRegion(normalBlockLoc, m_startLocation))
                        Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlGreen);
                }

                // Set all blocks between start and end
                else if (Input.GetMouse(0) == TriState.Up && !m_suppressUp)
                {
                    float Value = EditorGui.RandomColorFactor.Value;

                    foreach (Location loc in World.GetBlocksInRegion(normalBlockLoc, m_startLocation))
                    {
                        float RandOffset = (float)m_random.NextDouble() * Value - (Value * 0.5f);
                        Vector4 hsl = EditorGui.ColorPicker.ColorHSL;
                        hsl.Z += RandOffset;
                        hsl.Z = MathHelper.Clamp(hsl.Z, 0.0f, 1.0f);
                        Color c = Color.HslToRgba(hsl);

                        EditorWorld.World.SetBlock(loc, new Block(c));
                    }

                    EditorWorld.World.ReBuild();
                }

                // Set Start
                if (Input.GetMouse(1) == TriState.Pressed)
                    m_startLocation = blockLoc;

                // Highlight blocks
                else if (Input.GetMouse(1) == TriState.Replete)
                {
                    foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                        if (loc.Y > 0)
                            Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlRed);
                }

                // Set all blocks between start and end
                else if (Input.GetMouse(1) == TriState.Up)
                {
                    foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                        if (loc.Y > 0)
                            EditorWorld.World.SetBlock(loc, Block.Empty);

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
