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
        extern static Vector3 VCInteropCameraScreenPointToRay(int handle, int x, int y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip, RectangleF frame);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropCameraGetFields(int handle, out float fovDeg, out float aspect, out float nearClip, out float farClip, out RectangleF frame);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewCamera; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseCamera; } }

        #endregion

        private float m_fov;
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

        private float m_aspect;
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

        private float m_near;
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

        private float m_far;
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

        private RectangleF m_frame;
        public RectangleF Frame
        {
            get
            {
                GetData();
                return m_frame;
            }

            set
            {
                m_frame = value;
                SetData();
            }
        }

		public Camera ()
		{
            Transform.InvertPosition = true;

			Console.WriteLine("= Camera created with handle: " + UnManagedHandle);
		}

        public Ray ScreenPointToRay(int x, int y)
        {
            return new Ray
            {
                Direction = -Transform.Rotation.Forward,
                Origin = Transform.Position,
                MaxDistance = float.PositiveInfinity
            };
        }

        private void SetData()
        {
            VCInteropCameraSetFields(UnManagedHandle, m_far, m_aspect, m_near, m_far, m_frame);
        }

        private void GetData()
        {
            VCInteropCameraGetFields(UnManagedHandle, out m_fov, out m_aspect, out m_near, out m_far, out m_frame);
        }

	}
}

