using System;
using System.Runtime.InteropServices;

namespace VCEngine
{
	public class Transform : Component
	{
        public virtual Vector3 Position
        {
            get 
            { 
                if (InvertPosition)
                    return -m_position; 
                else
                    return m_position;
            }
            set 
            {
                if (InvertPosition)
                    m_position = -value; 
                else
                    m_position = value;

                m_rebuildNeeded = true;
            }
        }
        public virtual Quaternion Rotation
        {
            get { return m_rotation; }
            set 
            { 
                m_rotation = value;
                m_rebuildNeeded = true;
            }
        }
        public virtual Vector3 Scale
        {
            get { return m_scale; }
            set
            {
                m_scale = value;
                m_rebuildNeeded = true;
            }
        }

        public virtual Matrix4 TransformMatrix
        {
            get
            {
                if (m_rebuildNeeded)
                {
                    // M = S * R * T
                    m_transformMatrix = Matrix4.Scale(m_scale) * Matrix4.Rotate(m_rotation) * Matrix4.CreateTranslation(m_position);
                    //m_transformMatrix = Matrix4.CreateTranslation(m_position) * Matrix4.Rotate(m_rotation) * Matrix4.Scale(m_scale);
                    
                    // Will crawl up the tree and rebuild needed parents, and return
                    // when it finds the first built node.
                    if (GameObject.Parent != null)
                        m_transformMatrix = m_transformMatrix * GameObject.Parent.Transform.TransformMatrix;

                    m_rebuildNeeded = false;
                }

                return m_transformMatrix;
            }
        }

        internal Boolean InvertPosition;

        private Vector3 m_position = Vector3.Zero;
        private Quaternion m_rotation = Quaternion.Identity;
        private Vector3 m_scale = Vector3.One;

        private Boolean m_rebuildNeeded = true;
        private Matrix4 m_transformMatrix;
                
	}
}

