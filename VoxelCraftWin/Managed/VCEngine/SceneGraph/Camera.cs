using System;
using System.Runtime.CompilerServices;

namespace VCEngine
{
	public class Camera : GameObject
	{
		#region Bindings

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static int VCInteropNewCamera();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern static void VCInteropReleaseCamera(int handle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Vector3 VCInteropCameraScreenPointToDirection(int handle, Rectangle viewPort, Point screenPoint);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip, Rectangle viewport, int fullscreen);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropCameraGetFields(int handle, out float fovDeg, out float aspect, out float nearClip, out float farClip, out Rectangle viewport, out int fullscreen);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewCamera; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseCamera; } }

        #endregion

        public VC3DLineDrawer Debug;

        public float FieldOfViewDegrees
        {
            get
            {
                GetData();
                return m_fov;
            }

            set
            {
                m_fov = value;
                SetData();
            }
        }
        public float AspectRatio
        {
            get
            {
                GetData();
                return m_aspect;
            }

            set
            {
                m_aspect = value;
                SetData();
            }
        }
        public float NearClip
        {
            get
            {
                GetData();
                return m_near;
            }

            set
            {
                m_near = value;
                SetData();
            }
        }
        public float FarClip
        {
            get
            {
                GetData();
                return m_far;
            }

            set
            {
                m_far = value;
                SetData();
            }
        }
        public Rectangle Viewport
        {
            get
            {
                GetData();
                return m_viewport;
            }

            set
            {
                m_viewport = value;

                if (m_viewport.X < 0) m_viewport.X = 0;
                if (m_viewport.Y < 0) m_viewport.Y = 0;
                if (m_viewport.Width < 0) m_viewport.Width = 0;
                if (m_viewport.Height < 0) m_viewport.Height = 0;

                SetData();
            }
        }
        public bool Fullscreen
        {
            get
            {
                GetData();
                return m_fullscreen;
            }

            set
            {
                m_fullscreen = value;
                SetData();
            }
        }

        private float m_fov;
        private float m_aspect;
        private float m_near;
        private float m_far;
        private Rectangle m_viewport;
        private bool m_fullscreen;

		public Camera ()
		{
            Transform.InvertPosition = true;
            GetData();
            AspectRatio = (float)Window.ScaledSize.X / (float)Window.ScaledSize.Y;
            Debug = new VC3DLineDrawer(this);
		}

        public Camera(int existingHandle) : base(existingHandle)
        {
            Transform.InvertPosition = true;
            GetData();
            AspectRatio = (float)Window.ScaledSize.X / (float)Window.ScaledSize.Y;
            Debug = new VC3DLineDrawer(this);
        }

        public Ray ScreenPointToRay(Point point, float maxViewDistance)
        {
            Vector3 direction = VCInteropCameraScreenPointToDirection(
                    UnManagedHandle,
                    Fullscreen ? Window.FullViewport : m_viewport, 
                    point);

            return new Ray
            {
                Direction = direction,
                Origin = Transform.Position,
                MaxDistance = float.PositiveInfinity
            };
        }

        public Ray ScreenPointToRay(Point point, float maxViewDistance, Rectangle viewport)
        {
            Vector3 direction = VCInteropCameraScreenPointToDirection(
                    UnManagedHandle,
                    viewport,
                    point);

            return new Ray
            {
                Direction = direction,
                Origin = Transform.Position,
                MaxDistance = float.PositiveInfinity
            };
        }

        private void SetData()
        {
            VCInteropCameraSetFields(UnManagedHandle, m_far, m_aspect, m_near, m_far, m_viewport, m_fullscreen ? 1 : 0);
        }

        private void GetData()
        {
            int fullScreen;
            VCInteropCameraGetFields(UnManagedHandle, out m_fov, out m_aspect, out m_near, out m_far, out m_viewport, out fullScreen);
            m_fullscreen = fullScreen > 0;
        }

	}
}

