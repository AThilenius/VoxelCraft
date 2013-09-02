using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VCEngine;

namespace TestGame
{
    public class SimpleFPSController : Component
    {

        public override void Update()
        {

            Vector3 forward = Transform.Rotation.Forward;

            Transform.Position += new Vector3(forward.X * Input.Strafe.X, 0.0f, forward.Y * Input.Strafe.Y);
            Transform.Rotation += new Quaternion(new Vector3(Input.Look));
        }

    }
}
