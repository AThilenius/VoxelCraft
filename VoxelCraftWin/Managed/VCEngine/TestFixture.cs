using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TestFixture
    {
        static RenderWindow m_renderWindow;
        static RenderedEntity m_entity;

        public static PxMaterial material;
        public static PxShape boxShape;
        public static PxShape planeShape;
        public static RigidBody floor;
        public static RigidBody box;

        internal static void OnStart()
        {
            // PhysX
            //material = new PxMaterial(0.5f, 0.5f, 0.5f);

            //boxShape = PxShape.CreateBoxShape(material, new Vector3(0.5f, 0.5f, 0.5f));
            //planeShape = PxShape.CreatePlaneShape(material);

            //box = new RigidBody(new Vector3(0, 10, -20), Quaternion.Identity, false, boxShape);
            //floor = new RigidBody(Vector3.Zero, Quaternion.FromAxisAngle(Vector3.UnitZ, (float)Math.PI / 2.0f), true, planeShape);


            // Rendering
            //m_renderWindow = new RenderWindow();
            //m_renderWindow.MainCamera.Fullscreen = true;

            //m_entity = new RenderedEntity();
            //m_entity.Transform.Position = new Vector3(0, 0, -15);
            ////box.Children.Add(m_entity);

            //m_renderWindow.Entities.Add(m_entity);


            // Directory Test
            //DirectyObserverTreeNode dir1 = new DirectyObserverTreeNode("Assets", @"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\VoxelCraftWin\Assets", true);
            //DirectyObserverTreeNode dir2 = new DirectyObserverTreeNode("Resources", @"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\VoxelCraftWin\Resources", false);

            //TreeView view = new TreeView();
            //view.Head.AddControl(dir1);
            //view.Head.AddControl(dir2);
            //view.Frame = new Rectangle(300, 50, 250, 300);

            //Control.MainControl.AddControl(view);


            // Image Grid View
            //DirectoryImageGrid dig = new DirectoryImageGrid(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\VoxelCraftWin\Resources\Images\Icons");
            //Control.MainControl.AddControl(dig);
            //dig.Frame = new Rectangle(250, 0, Window.ScaledSize.X - 500, Window.ScaledSize.Y - 75);

            // Jpeg Test
            //ImageView imageView = new ImageView();
            //imageView.ImagePath = @"2014-01-04 15.29.52.jpg";
            //Control.MainControl.AddControl(imageView);
            //imageView.Frame = new Rectangle(300, 0, 400, 300);
        }

        public static void PerUpdate()
        {
            //Console.WriteLine(box.Actor.GetPosition());
        }

        public static void LatePerUpdate()
        {
            //Gui.DrawRectangle(new Rectangle(300, 300, 100, 25), Color.ControlRed);
            //Gui.DrawButton(new Rectangle(200, 200, 300, 250));
            //Gui.Draw9SliceImage(@"Icons\ButtonHighlight.DDS", new Rectangle(400, 300, 100, 25));
            //Gui.Draw9SliceGui(@"Icons\GuiButton.DDS", new Color(145, 163, 180, 255),    new Rectangle(220, 400, 100, 25));
            //Gui.Draw9SliceGui(@"Icons\GuiButton.DDS", new Color(255, 0, 0, 255),        new Rectangle(320, 400, 100, 25));
            //Gui.Draw9SliceGui(@"Icons\GuiButton.DDS", new Color(150, 220, 150, 255),        new Rectangle(220, 350, 100, 25));
        }


    }
}
