﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class RenderViewport : MarshaledObject
    {
        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropRenderWindowNew();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropRenverIndowRelease(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static  void VCInteropRenderWindowRenderToScreen(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropRenderWindowRenderToTexture(int handle, int textureHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropRenderWindowSetCamera(int handle, int cameraHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropRenderWindowAddEntity(int handle, int entityHandle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropRenderWindowRemoveEntity(int handle, int entityHandle);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropRenderWindowNew; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropRenverIndowRelease; } }

        #endregion

        public Camera MainCamera
        {
            get { return m_camera; }
            set
            {
                m_camera = value;
                VCInteropRenderWindowSetCamera(UnManagedHandle, m_camera.UnManagedHandle);
            }
        }
        public ObservableHashSet<RenderedEntity> Entities = new ObservableHashSet<RenderedEntity>();

        private Camera m_camera;

        public RenderViewport(Window window)
        {
            MainCamera = new Camera(window);
            Entities.OnCollectionChanged += (s, a) =>
                {
                    if (a.WasRemoved)
                        VCInteropRenderWindowRemoveEntity(UnManagedHandle, a.Item.UnManagedHandle);

                    else
                        VCInteropRenderWindowAddEntity(UnManagedHandle, a.Item.UnManagedHandle);
                };
            Entities.OnBeforeClear += (s, a) =>
                {
                    foreach (RenderedEntity entity in Entities)
                        VCInteropRenderWindowRemoveEntity(UnManagedHandle, entity.UnManagedHandle);
                };
        }

        public void Render()
        {
            VCInteropRenderWindowRenderToScreen(UnManagedHandle);
        }

        public void RenderToTexture()
        {
            throw new NotImplementedException();
        }

    }
}