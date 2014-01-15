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
            //box.Children.Add(m_entity);

            //m_renderWindow.Entities.Add(m_entity);

            IconLabelTreeNode head = new IconLabelTreeNode("Hello World");
            head.DoubleClick += (s, a) => Console.WriteLine("head");
            head.ClientHeight = 40;

            IconLabelTreeNode child1 = new IconLabelTreeNode("Hello Child 1"); head.AddControl(child1);
            child1.DoubleClick += (s, a) => Console.WriteLine("child1");
            IconLabelTreeNode child2 = new IconLabelTreeNode("Hello Child 2"); head.AddControl(child2);
            child2.DoubleClick += (s, a) => Console.WriteLine("child2");
            IconLabelTreeNode grandChild1 = new IconLabelTreeNode("Hello Grand Child"); child1.AddControl(grandChild1);
            grandChild1.DoubleClick += (s, a) => Console.WriteLine("grandChild1");

            TreeView<IconLabelTreeNode> view = new TreeView<IconLabelTreeNode>();
            view.Frame = new Rectangle(300, 50, 250, 300);
            view.Head = head;

            Control.MainControl.AddControl(view);
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
