using System;
using System.Runtime.InteropServices;

namespace VCEngine
{
    public class Camera : MarshaledGameObject
	{
		#region Bindings

		[DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
		extern static int VCInteropNewCamera();

		[DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropReleaseCamera(int handle);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropCameraSetProjectionViewMatrix(int handle, Matrix4 projMatrix, Matrix4 viewMatrix);

        [DllImport("VCEngine.UnManaged.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void VCInteropCameraSetViewport(int handle, Rectangle viewport);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewCamera; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseCamera; } }

        #endregion

        public VC3DLineDrawer Debug;
        public float FieldOfViewDegrees
        {
            get { return MathHelper.RadiansToDegrees(m_fieldOfViewRadians); }
            set
            {
                m_fieldOfViewRadians = MathHelper.DegreesToRadians(value);
                m_needsRebuild = true;
            }
        }
        public float NearClip
        {
            get { return m_nearClip; }
            set
            {
                m_nearClip = value;
                m_needsRebuild = true;
            }
        }
        public float FarClip
        {
            get { return m_farClip; }
            set
            {
                m_farClip = value;
                m_needsRebuild = true;
            }
        }
        public float AspectRatio
        {
            get { return m_aspectRatio; }
            set
            {
                if (value < 0.0f || float.IsNaN(value))
                    return;

                m_aspectRatio = value;
                m_needsRebuild = true;
            }
        }
        public bool Fullscreen
        {
            get { return m_fullscreen; }
            set
            {
                m_fullscreen = value;
                m_needsRebuild = true;
            }
        }
        public Rectangle Viewport
        {
            get { return Fullscreen ? Window.FullViewport : m_viewport; }
            set
            {
                m_viewport = value;

                if (m_viewport.X < 0) m_viewport.X = 0;
                if (m_viewport.Y < 0) m_viewport.Y = 0;
                if (m_viewport.Width < 0) m_viewport.Width = 0;
                if (m_viewport.Height < 0) m_viewport.Height = 0;

                VCInteropCameraSetViewport(UnManagedHandle, m_viewport);
            }
        }
        public Matrix4 ProjectionMatrix
        {
            get
            {
                if (m_needsRebuild)
                {
                    m_projectionMatrix = Matrix4.CreatePerspectiveFieldOfView(m_fieldOfViewRadians, m_aspectRatio, m_nearClip, m_farClip);
                    m_inverseProjMatrix = Matrix4.Invert(m_projectionMatrix);
                }

                return m_projectionMatrix;
            }
        }

        private Rectangle m_viewport = new Rectangle(0, 0, 100, 100);
        private float m_fieldOfViewRadians = MathHelper.DegreesToRadians(65.0f);
        private float m_nearClip = 0.1f;
        private float m_farClip = 500.0f;
        private float m_aspectRatio = 1.0f;
        private bool m_fullscreen;
        private Matrix4 m_projectionMatrix;
        private Matrix4 m_inverseProjMatrix;
        private Boolean m_needsRebuild = true;

		public Camera ()
		{
            Transform.InvertPosition = true;
            Debug = new VC3DLineDrawer(this);
		}

        public Camera(int existingHandle) : base(existingHandle)
        {
            Transform.InvertPosition = true;
            Debug = new VC3DLineDrawer(this);
        }

        public Ray ScreenPointToRay(Point point, float maxViewDistance)
        {
	        Rectangle screenBounds = Window.FullViewport;
            Rectangle viewPort = Fullscreen ? Window.FullViewport : Viewport;

	        Vector2 ll = new Vector2 (viewPort.X, viewPort.Y);
	        Vector2 ur = new Vector2 (viewPort.X + viewPort.Width, viewPort.Y + viewPort.Height);
	        Vector2 sp = new Vector2 (point.X, point.Y);

	        Vector2 delta = ur - ll;
	        Vector2 spInViewport = new Vector2 (2.0f * ((sp.X - ll.X) / delta.X) - 1.0f, 2.0f * ((sp.Y - ll.Y) / delta.Y) - 1.0f);

	        Vector4 ray_clip = new Vector4 (spInViewport.X, spInViewport.Y, -1.0f, 1.0f);

	        Vector4 ray_eye = Vector4.Transform(ray_clip, m_inverseProjMatrix);
	        ray_eye = new Vector4 (ray_eye.X, ray_eye.Y, -1.0f, 0.0f);

	        Vector4 rayWorld4 = Vector4.Transform(ray_eye, Matrix4.Invert(Transform.TransformMatrix));
	        Vector3 ray_wor = new Vector3(rayWorld4);
            ray_wor.Normalize();

            return new Ray
            {
                Direction = ray_wor,
                Origin = Transform.Position,
                MaxDistance = float.PositiveInfinity
            };
        }

        public override void PreRender()
        {
            // Ensure View matrix is up to date
            Transform.PreRender();

            VCInteropCameraSetProjectionViewMatrix(UnManagedHandle, ProjectionMatrix, Transform.TransformMatrix);
            VCInteropCameraSetViewport(UnManagedHandle, Viewport);

            base.PreRender();
        }

	}
}

