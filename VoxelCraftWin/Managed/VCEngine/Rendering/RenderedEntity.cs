using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    public class RenderedEntity : MarshaledGameObject
    {

        #region Bindings

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropEntityNew();

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropEntityRelease(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropEntitySetModelMatrix(int handle, Matrix4 modelMatrix);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VCInteropEntitySetModel(int handle, String modelPath);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropEntitySetMaterial(int handle, int matIndex, String materialPath);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropEntityNew; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropEntityRelease; } }

        #endregion

        public RenderedEntity()
        {

        }

        public RenderedEntity (String modelPath, params String[] materialsPaths)
        {
            VCInteropEntitySetModel(UnManagedHandle, modelPath);
            
            for (int i = 0; i < materialsPaths.Length; i++)
                VCInteropEntitySetMaterial(UnManagedHandle, i, materialsPaths[i]);
        }

        public override void PreRender()
        {
            base.PreRender();
            VCInteropEntitySetModel(UnManagedHandle, "Models\\Sphere.obj");
            VCInteropEntitySetModelMatrix(UnManagedHandle, Transform.TransformMatrix);
        }

    }
}
