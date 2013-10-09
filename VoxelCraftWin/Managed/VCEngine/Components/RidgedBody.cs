using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class RidgedBody : Component
    {
        private Vector3 m_force;

        public override void Update()
        {
            //m_force += -Vector3.UnitY * 1.5f * Time.DeltaTime;
            //Transform.Position += m_force;

            //if (World.GetBlock(Transform.Position - Vector3.UnitY * 1.5f ))
            //{
            //    Transform.Position.Y = (float) Math.Ceiling(Transform.Position.Y) - 0.5f;
            //    m_force.Y = 0.0f;
            //}

            //if (Input.IsKeyDown(' '))
            //    m_force += Vector3.UnitY * 2f * Time.DeltaTime;
        }

        public void AddForce(Vector3 force)
        {
            m_force += force;
        }
    }
}
