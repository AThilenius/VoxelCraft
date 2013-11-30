using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace VCEngine
{
    public class VC3DLineDrawer : MarshaledObject
    {
        #region Bindings

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static int VCInteropNew3DLineDrawer(int cameraHandle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropRelease3DLineDrawer(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInterop3DLineDrawerDrawLine(int handle, Vector3 from, Vector3 to, Color color);

        // Custom CTor, Standard DTor //
        protected override UnManagedCTorDelegate UnManagedCTor { get { return null; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropRelease3DLineDrawer; } }

        #endregion

        public Camera AttachedCamera { get; private set; }

        public VC3DLineDrawer(Camera camera)
        {
            AttachedCamera = camera;
            UnManagedHandle = VCInteropNew3DLineDrawer(camera.UnManagedHandle);
            ObjectStore.RegisterObject(this, UnManagedHandle);
        }

        public void DrawLine(Vector3 from, Vector3 to, Color color)
        {
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, from, to, color);
        }

        public void DrawCube(Vector3 corner, Vector3 scale, Color color)
        {        
            Vector3 V1 = corner + new Vector3(0,		0,			0);
            Vector3 V2 = corner + new Vector3(scale.X,  0,          0);
            Vector3 V3 = corner + new Vector3(scale.X,  0,          scale.Z);
            Vector3 V4 = corner + new Vector3(0,        0,          scale.Z);

            Vector3 V5 = corner + new Vector3(0,        scale.Y,    0);
            Vector3 V6 = corner + new Vector3(scale.X,  scale.Y,    0);
            Vector3 V7 = corner + new Vector3(scale.X,  scale.Y,    scale.Z);
            Vector3 V8 = corner + new Vector3(0,        scale.Y,    scale.Z);

            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V1, V2, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V2, V3, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V3, V4, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V4, V1, color);

            // Top
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V5, V6, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V6, V7, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V7, V8, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V8, V5, color);

            // Vertical
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V1, V5, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V2, V6, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V3, V7, color);
            VCInterop3DLineDrawerDrawLine(UnManagedHandle, V4, V8, color);
        }
        
        //void VCDebug::DrawCube( glm::vec3 corner, glm::vec3 scale, GLubyte4 color )
        //{
        //    glm::vec3 V1 = corner + glm::vec3(0,			0,			0);
        //    glm::vec3 V2 = corner + glm::vec3(scale.x,	0,			0);
        //    glm::vec3 V3 = corner + glm::vec3(scale.x,	0,			scale.z);
        //    glm::vec3 V4 = corner + glm::vec3(0,			0,			scale.z);

        //    glm::vec3 V5 = corner + glm::vec3(0,			scale.y,	0);
        //    glm::vec3 V6 = corner + glm::vec3(scale.x,	scale.y,	0);
        //    glm::vec3 V7 = corner + glm::vec3(scale.x,	scale.y,	scale.z);
        //    glm::vec3 V8 = corner + glm::vec3(0,			scale.y,	scale.z);

        //    // Bot
        //    DrawLine(V1, V2, color);
        //    DrawLine(V2, V3, color);
        //    DrawLine(V3, V4, color);
        //    DrawLine(V4, V1, color);

        //    // Top
        //    DrawLine(V5, V6, color);
        //    DrawLine(V6, V7, color);
        //    DrawLine(V7, V8, color);
        //    DrawLine(V8, V5, color);

        //    // Vertical
        //    DrawLine(V1, V5, color);
        //    DrawLine(V2, V6, color);
        //    DrawLine(V3, V7, color);
        //    DrawLine(V4, V8, color);
        //}
    }
}
