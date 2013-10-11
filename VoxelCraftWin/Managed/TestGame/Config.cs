﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VCEngine;

namespace TestGame
{
    public class Config : StaticInstance
    {
        private Camera m_camera;
        private World m_world;

        public override void Start()
        {
            Gui.LoadFontsFromForlder(@"C:\Users\Alec\Documents\Development\CPP\VoxelCraft\Fonts");

            m_camera = new Camera();
            m_camera.Transform.Position = new Vector3(20, 80, 20);
            SimpleFPSController simpleController = new SimpleFPSController();
            m_camera.AttachComponent(simpleController);

            m_world = new World();
            m_world.Generator = new FlatChunkGenerator();
            m_world.ViewDistance = 4;
            m_world.Initialize();
            m_world.GenerateRegenerate();
            m_world.ReBuild();
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
                    Console.WriteLine("Hit at: " + hit.X + ", " + hit.Y + ", " + hit.Z + ". Normal: " + hit.Normal);
                    
                    m_world.SetBlock(normalBlock, new Block(255, 0, 0, 255));
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
