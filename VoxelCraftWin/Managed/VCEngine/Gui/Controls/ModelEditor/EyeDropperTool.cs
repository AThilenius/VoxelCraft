using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class EyeDropperTool : ModelTool
    {
        public event EventHandler OnPicked = delegate { };
        public Color ColorRGB;

        private bool m_isDragging;
        private Location m_startLoc;

        public EyeDropperTool(Window window, GameWindow parent) : base(window, parent)
        {

        }

        public override void Update(RaycastHit? rayHit)
        {
            if (rayHit == null)
                return;

            RaycastHit hit = (RaycastHit)rayHit;
            Vector3 block = new Vector3(hit.CubeLocation);

            if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.Pressed)
            {
                m_isDragging = true;
                m_startLoc = hit.CubeLocation;
                ColorRGB = World.GetBlock(block).Color;
            }

            if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.Replete && m_isDragging)
            {
                // Sample all blocks and average
                ColorRGB = GetAverage(hit.CubeLocation, m_startLoc);
            }

            if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.Up && m_isDragging)
            {
                m_isDragging = false;

                // Sample all blocks and average
                ColorRGB = GetAverage(hit.CubeLocation, m_startLoc);

                OnPicked(this, EventArgs.Empty);
            }

            if (ParentWindow.GlfwInputState.MouseStates[0].State == TriState.None)
            {
                World.Camera.Debug.DrawCube(block - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.White);
                ParentWindow.GuiDrawer.DrawBorderedRect(new Rectangle(ParentWindow.GlfwInputState.MouseLocation.X + 15, ParentWindow.GlfwInputState.MouseLocation.Y, 40, 40), World.GetBlock(block).Color, Color.White, 1);
            }

            else
            {
                // Draw blocks in selected range
                foreach (Location loc in World.GetBlocksInRegion(hit.CubeLocation, m_startLoc))
                    World.Camera.Debug.DrawCube(new Vector3(loc) - new Vector3(0.05f, 0.05f, 0.05f), new Vector3(1.1f, 1.1f, 1.1f), Color.White);

                ParentWindow.GuiDrawer.DrawBorderedRect(new Rectangle(ParentWindow.GlfwInputState.MouseLocation.X + 15, ParentWindow.GlfwInputState.MouseLocation.Y, 40, 40), ColorRGB, Color.White, 1);
            }

        }

        private Color GetAverage(Location from, Location to)
        {
            if (from.Y == 0)
                from.Y = 1;

            if (to.Y == 0)
                to.Y = 1;

            Location[] locs = World.GetBlocksInRegion(from, to);

            int r = 0;
            int g = 0;
            int b = 0;
            int count = 0;

            foreach (Location loc in locs)
            {
                Color c = World.GetBlock(loc).Color;

                if (c.A != 255)
                    continue;

                r += c.R;
                g += c.G;
                b += c.B;
                count++;
            }

            r = MathHelper.RoundedDevision(r, count);
            g = MathHelper.RoundedDevision(g, count);
            b = MathHelper.RoundedDevision(b, count);

            return new Color(r, g, b, 255);
        }
    }
}
