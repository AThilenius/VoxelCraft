using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class RigidBody : GameObject
    {

        public PxRigidActor Actor;

        public RigidBody(Vector3 pos, Quaternion rot, Boolean isStatic, PxShape shape)
        {
            if (isStatic)
                Actor = new PxRigidStatic(pos, rot);

            else
                Actor = new PxRigidDynamic(pos, rot);

            Actor.AttachShape(shape);
            //VCEngineCore.PhysicsScene.AddActor(Actor);
        }

        ~RigidBody()
        {
            // Remove Actor from Scene
        }

        public override void Update()
        {
            base.Update();

            // HACK:
            Transform.Position = Actor.GetPosition();
            Transform.Rotation = Actor.GetRotation();
        }

    }
}
