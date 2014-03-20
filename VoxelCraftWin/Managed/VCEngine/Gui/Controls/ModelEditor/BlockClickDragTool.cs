using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class BlockClickDragTool : ModelTool
    {
        private Location m_startLocation;
        private bool m_isDraggingLeft;
        private bool m_isDraggingRight;
        private Random m_random = new Random();

        public BlockClickDragTool(Window window, GameWindow parent) : base(window, parent)
        {

        }

        public override void Update(RaycastHit? rayHit)
        {
            if (rayHit == null)
            {
                m_isDraggingLeft = false;
                m_isDraggingRight = false;

                return;
            }

            RaycastHit hit = (RaycastHit) rayHit;

            Vector3 block = new Vector3(hit.CubeLocation);
            Location blockLoc = hit.CubeLocation;
            Vector3 normalBlock = block + hit.Normal;
            Location normalBlockLoc = new Location(normalBlock);

            // Draw Normal if nothing is down
            if (m_glfwInputState.MouseStates[0].State == TriState.None && m_glfwInputState.MouseStates[1].State == TriState.None)
                World.Camera.Debug.DrawCube(normalBlock - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.White);


            // ======   Left Mouse   ============================================================

            // Set start
            if (m_glfwInputState.MouseStates[0].State == TriState.Pressed)
            {
                m_startLocation = normalBlockLoc;
                m_isDraggingLeft = true;
            }

            // Highlight blocks
            else if (m_glfwInputState.MouseStates[0].State == TriState.Replete && m_isDraggingLeft)
            {
                foreach (Location loc in World.GetBlocksInRegion(normalBlockLoc, m_startLocation))
                    World.Camera.Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.White);
            }

            // Create an Undo Token, Set all blocks between start and end
            else if (m_glfwInputState.MouseStates[0].State == TriState.Up && m_isDraggingLeft)
            {
                BlockChangeUndoToken undoToken = new BlockChangeUndoToken(World);
                float Value = EditorGui.VoxelEditor.ColorPicker.RandomMultiplier;

                foreach (Location loc in World.GetBlocksInRegion(normalBlockLoc, m_startLocation))
                {
                    float RandOffset = (float)m_random.NextDouble() * Value - (Value * 0.5f);
                    Vector4 hsl = EditorGui.VoxelEditor.ColorPicker.ColorHSL;
                    hsl.Z += RandOffset;
                    hsl.Z = MathHelper.Clamp(hsl.Z, 0.0f, 1.0f);
                    Color c = Color.HslToRgba(hsl);

                    if (loc.Y > 0)
                    {
                        undoToken.AddBlock(loc, World.GetBlock(loc).Color, c);
                        World.SetBlock(loc, new Block(c));
                    }
                }

                Parent.UndoStack.AddToken(undoToken);
                World.ReBuild();
                m_isDraggingLeft = false;
            }


            // ======   Right Mouse   ============================================================

            // Set Start
            if (m_glfwInputState.MouseStates[1].State == TriState.Pressed)
            {
                m_startLocation = blockLoc;
                m_isDraggingRight = true;
            }

            // Highlight blocks
            else if (m_glfwInputState.MouseStates[1].State == TriState.Replete && m_isDraggingRight)
            {
                foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                    if (loc.Y > 0)
                        World.Camera.Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.ControlRed);
            }

            // Create an undo token, Set all blocks between start and end
            else if (m_glfwInputState.MouseStates[1].State == TriState.Up && m_isDraggingRight)
            {
                BlockChangeUndoToken undoToken = new BlockChangeUndoToken(World);

                foreach (Location loc in World.GetBlocksInRegion(blockLoc, m_startLocation))
                    if (loc.Y > 0)
                    {
                        undoToken.AddBlock(loc, World.GetBlock(loc).Color, Block.Empty.Color);
                        World.SetBlock(loc, Block.Empty);
                    }

                Parent.UndoStack.AddToken(undoToken);
                World.ReBuild();
                m_isDraggingRight = false;
            }

        }

    }
}
