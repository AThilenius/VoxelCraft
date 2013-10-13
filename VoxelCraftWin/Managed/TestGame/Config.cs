using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using VCEngine;

namespace TestGame
{
    public class Config : StaticInstance
    {
        private Camera m_camera;
        private World m_world;
        private TabbedContainer m_inspector;
        private HslColorPicker m_picker;

        public override void Start()
        {
            Gui.LoadFontsFromForlder(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\Fonts");
            //Gui.LoadFontsFromForlder(Environment.CurrentDirectory + @"\Fonts");
            
            m_camera = new Camera();
            m_camera.Transform.Position = new Vector3(50, 20, 50);
            SimpleFPSController simpleController = new SimpleFPSController();
            m_camera.AttachComponent(simpleController);

            m_world = new World();
            m_world.Generator = new FlatChunkGenerator();
            m_world.ViewDistance = 2;
            m_world.Initialize();
            m_world.GenerateRegenerate();
            m_world.ReBuild();

            m_inspector = new TabbedContainer();
            m_inspector.ScreenFrame = new Rectangle(Window.Size.X - 300, 0, 300, Window.Size.Y);
            Control.MainControl.AddControl(m_inspector);

            m_picker = new HslColorPicker();
            m_inspector.AddTab("Color", m_picker);
            m_inspector.AddTab("Test", new Button("Test"));
            //m_picker.ScreenFrame = new Rectangle(100, 100, 300, 140);

            Vector4 HSL = Color.RgbaToHsl(new Color(24, 48, 92, 255));
            Console.WriteLine("RGB: 24, 48, 92 => HSL: " + HSL);
            Color RGB = Color.HslToRgba(HSL);
            Console.WriteLine("HSL: " + HSL + " => RGB: " + RGB);
        }

        public override void Update()
        {
            Ray ray = m_camera.ScreenPointToRay(Input.MousePoistion, 1000);
            RaycastHit hit;

            if (m_world.Raycast(ray, out hit))
            {
                Vector3 block = new Vector3(hit.X, hit.Y, hit.Z);
                Vector3 normalBlock = new Vector3(hit.X, hit.Y, hit.Z) + hit.Normal;
                Debug.DrawCube(block - new Vector3(0.1f, 0.1f, 0.1f), new Vector3(1.2f, 1.2f, 1.2f), Color.ControlGreen);

                if (Input.GetMouse(0) == TriState.Pressed)
                {
                    m_world.SetBlock(normalBlock, new Block(m_picker.ColorRGB));
                    m_world.ReBuild();
                }

                if (Input.GetMouse(1) == TriState.Pressed)
                {
                    m_world.SetBlock(hit.X, hit.Y, hit.Z, new Block(0, 0, 0, 0));
                    m_world.ReBuild();
                }
            }

        }

        


    }
}
