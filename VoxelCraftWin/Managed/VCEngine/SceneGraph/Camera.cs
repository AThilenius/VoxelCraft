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
        extern static void VCInteropCameraSetFields(int handle, float fovDeg, float aspect, float nearClip, float farClip);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void VCInteropCameraGetFields(int handle, out float fovDeg, out float aspect, out float nearClip, out float farClip);

        protected override UnManagedCTorDelegate UnManagedCTor { get { return VCInteropNewCamera; } }
        protected override UnManagedDTorDelegate UnManagedDTor { get { return VCInteropReleaseCamera; } }

        #endregion

        public static Camera MainCamera;

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

		public Camera ()
		{
            Transform.InvertPosition = true;
            GetData();
            AspectRatio = (float)Window.Size.X / (float)Window.Size.Y;
		}

        public Ray ScreenPointToRay(Point point, float maxViewDistance)
        {
            Vector3 direction = VCInteropCameraScreenPointToDirection(
                    UnManagedHandle,
                    new Rectangle(0, 0, (int)(Window.Size.X), (int)(Window.Size.Y)), 
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
            VCInteropCameraSetFields(UnManagedHandle, m_far, m_aspect, m_near, m_far);
        }

        private void GetData()
        {
            VCInteropCameraGetFields(UnManagedHandle, out m_fov, out m_aspect, out m_near, out m_far);
        }

	}
}

