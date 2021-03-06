﻿using System;
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

        public override void Start()
        {
            
            m_camera = new Camera();
            Camera.MainCamera = m_camera;
            m_camera.Transform.Position = new Vector3(50, 20, 50);
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
                    m_world.SetBlock(normalBlock, new Block(EditorGui.ColorPicker.ColorRGB));
                    m_world.ReBuild();
                }

                if (Input.GetMouse(1) == TriState.Pressed && block.Y > 0)
                {
                    m_world.SetBlock(hit.X, hit.Y, hit.Z, new Block(0, 0, 0, 0));
                    m_world.ReBuild();
                }
            }

            Debug.DrawCube(Vector3.Zero, Vector3.One * 32 * m_world.ViewDistance, Color.ControlGreen);

        }

        


    }
}
