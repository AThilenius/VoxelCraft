using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class RenderWindow : Control
    {

        public RenderViewport GLRenderViewport;

        public RenderWindow(Window window) : base(window)
        {
            GLRenderViewport = new RenderViewport(ParentWindow);
            GLRenderViewport.MainCamera.Fullscreen = false;
            GLRenderViewport.MainCamera.Viewport = new Rectangle(0, 0, 1024, 1024);
        }

        protected override void Draw()
        {
            // Update the Viewport every frame
            GLRenderViewport.MainCamera.Viewport = ScreenFrame;

            // Force a pipe flush
            ParentWindow.FlushRenderQueue();

            // Draw window
            GLRenderViewport.Render();

            // Just clear the ZBuffer
            FrameBufferObject.Default.Clear(false, true);
        }

    }
}
