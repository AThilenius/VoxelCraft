#region --- License ---
/*
Copyright (c) 2006 - 2008 The Open Toolkit library.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#endregion

using System;
using System.Runtime.InteropServices;
using System.ComponentModel;

namespace VCEngine
{
	/// <summary>
	/// Represents a Quaternion.
	/// </summary>
	[Serializable]
	[StructLayout(LayoutKind.Sequential)]
	public struct Quaternion : IEquatable<Quaternion>
	{
		#region Fields

		Vector3 xyz;
		float w;

		#endregion

		#region Constructors

		/// <summary>
		/// Construct a new Quaternion from vector and w components
		/// </summary>
		/// <param name="v">The vector part</param>
		/// <param name="w">The w part</param>
		public Quaternion(Vector3 v, float w)
		{
			this.xyz = v;
			this.w = w;
		}

		/// <summary>
		/// Construct a new Quaternion
		/// </summary>
		/// <param name="x">The x component</param>
		/// <param name="y">The y component</param>
		/// <param name="z">The z component</param>
		/// <param name="w">The w component</param>
		public Quaternion(float x, float y, float z, float w)
		: this(new Vector3(x, y, z), w)
		{ }

        public static Quaternion FromEuler(Vector3 angels)
        {
            return FromEuler(angels.X, angels.Y, angels.Z);
        }

        public static Quaternion FromEuler(float x, float y, float z)
        {
            Quaternion newQ = Quaternion.Identity;
            newQ = Quaternion.Multiply(newQ, Quaternion.FromAxisAngle(Vector3.UnitX, x));
            newQ = Quaternion.Multiply(newQ, Quaternion.FromAxisAngle(Vector3.UnitY, y));
            newQ = Quaternion.Multiply(newQ, Quaternion.FromAxisAngle(Vector3.UnitZ, z));

            return newQ;
        }

		#endregion

		#region Public Members

		#region Properties

		/// <summary>
		/// Gets or sets an OpenTK.Vector3 with the X, Y and Z components of this instance.
		/// </summary>
		[Obsolete("Use Xyz property instead.")]
		[EditorBrowsable(EditorBrowsableState.Never)]
		public Vector3 XYZ { get { return Xyz; } set { Xyz = value; } }

		/// <summary>
		/// Gets or sets an OpenTK.Vector3 with the X, Y and Z components of this instance.
		/// </summary>
		public Vector3 Xyz { get { return xyz; } set { xyz = value; } }

		/// <summary>
		/// Gets or sets the X component of this instance.
		/// </summary>
		public float X { get { return xyz.X; } set { xyz.X = value; } }

		/// <summary>
		/// Gets or sets the Y component of this instance.
		/// </summary>
		public float Y { get { return xyz.Y; } set { xyz.Y = value; } }

		/// <summary>
		/// Gets or sets the Z component of this instance.
		/// </summary>
		public float Z { get { return xyz.Z; } set { xyz.Z = value; } }

		/// <summary>
		/// Gets or sets the W component of this instance.
		/// </summary>
		public float W { get { return w; } set { w = value; } }

		#endregion

		#region Instance

        public Vector3 Forward
        {
            get
            {
                return this * Vector3.UnitZ;
            }
        }

        public Vector3 Up
        {
            get
            {
                return this * Vector3.UnitY;
            }
        }

        public Vector3 Right
        {
            get
            {
                return this * Vector3.UnitX;
            }
        }

		/// <summary>
		/// Convert the current quaternion to axis angle representation
		/// </summary>
		/// <param name="axis">The resultant axis</param>
		/// <param name="angle">The resultant angle</param>
		public void ToAxisAngle(out Vector3 axis, out float angle)
		{
			Vector4 result = ToAxisAngle();
			axis = result.Xyz;
			angle = result.W;
		}

		/// <summary>
		/// Convert this instance to an axis-angle representation.
		/// </summary>
		/// <returns>A Vector4 that is the axis-angle representation of this quaternion.</returns>
		public Vector4 ToAxisAngle()
		{
			Quaternion q = this;
			if (Math.Abs(q.W) > 1.0f)
				q.Normalize();

			Vector4 result = new Vector4();

			result.W = 2.0f * (float)System.Math.Acos(q.W); // angle
			float den = (float)System.Math.Sqrt(1.0 - q.W * q.W);
			if (den > 0.0001f)
			{
				result.Xyz = q.Xyz / den;
			}
			else
			{
				// This occurs when the angle is zero. 
				// Not a problem: just set an arbitrary normalized axis.
				result.Xyz = Vector3.UnitX;
			}

			return result;
		}

		/// <summary>
		/// Gets the length (magnitude) of the quaternion.
		/// </summary>
		/// <seealso cref="LengthSquared"/>
		public float Length
		{
			get
			{
				return (float)System.Math.Sqrt(W * W + Xyz.LengthSquared);
			}
		}

		/// <summary>
		/// Gets the square of the quaternion length (magnitude).
		/// </summary>
		public float LengthSquared
		{
			get
			{
				return W * W + Xyz.LengthSquared;
			}
		}

		/// <summary>
		/// Scales the Quaternion to unit length.
		/// </summary>
		public void Normalize()
		{
			float scale = 1.0f / this.Length;
			Xyz *= scale;
			W *= scale;
		}

		/// <summary>
		/// Convert this quaternion to its conjugate
		/// </summary>
		public void Conjugate()
		{
			Xyz = -Xyz;
		}

		#endregion

		#region Static

		/// <summary>
		/// Defines the identity quaternion.
		/// </summary>
		public static Quaternion Identity = new Quaternion(0, 0, 0, 1);

		#region Invert

		/// <summary>
		/// Get the inverse of the given quaternion
		/// </summary>
		/// <param name="q">The quaternion to invert</param>
		/// <returns>The inverse of the given quaternion</returns>
		public static Quaternion Invert(Quaternion q)
		{
			Quaternion result;
			Invert(ref q, out result);
			return result;
		}

		/// <summary>
		/// Get the inverse of the given quaternion
		/// </summary>
		/// <param name="q">The quaternion to invert</param>
		/// <param name="result">The inverse of the given quaternion</param>
		public static void Invert(ref Quaternion q, out Quaternion result)
		{
			float lengthSq = q.LengthSquared;
			if (lengthSq != 0.0)
			{
				float i = 1.0f / lengthSq;
				result = new Quaternion(q.Xyz * -i, q.W * i);
			}
			else
			{
				result = q;
			}
		}

		#endregion

		#region Normalize

		/// <summary>
		/// Scale the given quaternion to unit length
		/// </summary>
		/// <param name="q">The quaternion to normalize</param>
		/// <returns>The normalized quaternion</returns>
		public static Quaternion Normalize(Quaternion q)
		{
			Quaternion result;
			Normalize(ref q, out result);
			return result;
		}

		/// <summary>
		/// Scale the given quaternion to unit length
		/// </summary>
		/// <param name="q">The quaternion to normalize</param>
		/// <param name="result">The normalized quaternion</param>
		public static void Normalize(ref Quaternion q, out Quaternion result)
		{
			float scale = 1.0f / q.Length;
			result = new Quaternion(q.Xyz * scale, q.W * scale);
		}

		#endregion

		#region FromAxisAngle

		/// <summary>
		/// Build a quaternion from the given axis and angle
		/// </summary>
		/// <param name="axis">The axis to rotate about</param>
		/// <param name="angle">The rotation angle in radians</param>
		/// <returns></returns>
		public static Quaternion FromAxisAngle(Vector3 axis, float angle)
		{
			if (axis.LengthSquared == 0.0f)
				return Identity;

			Quaternion result = Identity;

			angle *= 0.5f;
			axis.Normalize();
			result.Xyz = axis * (float)System.Math.Sin(angle);
			result.W = (float)System.Math.Cos(angle);

			return Normalize(result);
		}

		#endregion

		#region Slerp

		/// <summary>
		/// Do Spherical linear interpolation between two quaternions 
		/// </summary>
		/// <param name="q1">The first quaternion</param>
		/// <param name="q2">The second quaternion</param>
		/// <param name="blend">The blend factor</param>
		/// <returns>A smooth blend between the given quaternions</returns>
		public static Quaternion Slerp(Quaternion q1, Quaternion q2, float blend)
		{
			// if either input is zero, return the other.
			if (q1.LengthSquared == 0.0f)
			{
				if (q2.LengthSquared == 0.0f)
				{
					return Identity;
				}
				return q2;
			}
			else if (q2.LengthSquared == 0.0f)
			{
				return q1;
			}


			float cosHalfAngle = q1.W * q2.W + Vector3.Dot(q1.Xyz, q2.Xyz);

			if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
			{
				// angle = 0.0f, so just return one input.
				return q1;
			}
			else if (cosHalfAngle < 0.0f)
			{
				q2.Xyz = -q2.Xyz;
				q2.W = -q2.W;
				cosHalfAngle = -cosHalfAngle;
			}

			float blendA;
			float blendB;
			if (cosHalfAngle < 0.99f)
			{
				// do proper slerp for big angles
				float halfAngle = (float)System.Math.Acos(cosHalfAngle);
				float sinHalfAngle = (float)System.Math.Sin(halfAngle);
				float oneOverSinHalfAngle = 1.0f / sinHalfAngle;
				blendA = (float)System.Math.Sin(halfAngle * (1.0f - blend)) * oneOverSinHalfAngle;
				blendB = (float)System.Math.Sin(halfAngle * blend) * oneOverSinHalfAngle;
			}
			else
			{
				// do lerp if angle is really small.
				blendA = 1.0f - blend;
				blendB = blend;
			}

			Quaternion result = new Quaternion(blendA * q1.Xyz + blendB * q2.Xyz, blendA * q1.W + blendB * q2.W);
			if (result.LengthSquared > 0.0f)
				return Normalize(result);
			else
				return Identity;
		}

		#endregion

		#endregion

		#region Operators

		/// <summary>
		/// Adds two instances.
		/// </summary>
		/// <param name="left">The first instance.</param>
		/// <param name="right">The second instance.</param>
		/// <returns>The result of the calculation.</returns>
		public static Quaternion operator +(Quaternion left, Quaternion right)
		{
			left.Xyz += right.Xyz;
			left.W += right.W;
			return left;
		}

		/// <summary>
		/// Subtracts two instances.
		/// </summary>
		/// <param name="left">The first instance.</param>
		/// <param name="right">The second instance.</param>
		/// <returns>The result of the calculation.</returns>
		public static Quaternion operator -(Quaternion left, Quaternion right)
		{
			left.Xyz -= right.Xyz;
			left.W -= right.W;
			return left;
		}

		/// <summary>
		/// Multiplies two instances.
		/// </summary>
		/// <param name="left">The first instance.</param>
		/// <param name="right">The second instance.</param>
		/// <returns>The result of the calculation.</returns>
		public static Quaternion operator *(Quaternion left, Quaternion right)
		{
			Multiply(ref left, ref right, out left);
			return left;
		}

		/// <summary>
		/// Multiplies an instance by a scalar.
		/// </summary>
		/// <param name="quaternion">The instance.</param>
		/// <param name="scale">The scalar.</param>
		/// <returns>A new instance containing the result of the calculation.</returns>
		public static Quaternion operator *(Quaternion quaternion, float scale)
		{
			Multiply(ref quaternion, scale, out quaternion);
			return quaternion;
		}

		/// <summary>
		/// Multiplies an instance by a scalar.
		/// </summary>
		/// <param name="quaternion">The instance.</param>
		/// <param name="scale">The scalar.</param>
		/// <returns>A new instance containing the result of the calculation.</returns>
		public static Quaternion operator *(float scale, Quaternion quaternion)
		{
			return new Quaternion(quaternion.X * scale, quaternion.Y * scale, quaternion.Z * scale, quaternion.W * scale);
		}

		/// <summary>
		/// Compares two instances for equality.
		/// </summary>
		/// <param name="left">The first instance.</param>
		/// <param name="right">The second instance.</param>
		/// <returns>True, if left equals right; false otherwise.</returns>
		public static bool operator ==(Quaternion left, Quaternion right)
		{
			return left.Equals(right);
		}

		/// <summary>
		/// Compares two instances for inequality.
		/// </summary>
		/// <param name="left">The first instance.</param>
		/// <param name="right">The second instance.</param>
		/// <returns>True, if left does not equal right; false otherwise.</returns>
		public static bool operator !=(Quaternion left, Quaternion right)
		{
			return !left.Equals(right);
		}

        public static Vector3 operator *(Quaternion quat, Vector3 vector)
        {
            Quaternion v = new Quaternion() { X = vector.X, Y = vector.Y, Z = vector.Z, W = 0 };
            Quaternion i = Quaternion.Invert(quat);
            Quaternion t = i * v;
            v = t * quat;

            return new Vector3(v.X, v.Y, v.Z);
        }

		#endregion

		#region Overrides

		#region public override string ToString()

		/// <summary>
		/// Returns a System.String that represents the current Quaternion.
		/// </summary>
		/// <returns></returns>
		public override string ToString()
		{
			return String.Format("V: {0}, W: {1}", Xyz, W);
		}

		#endregion

		#region public override bool Equals (object o)

		/// <summary>
		/// Compares this object instance to another object for equality. 
		/// </summary>
		/// <param name="other">The other object to be used in the comparison.</param>
		/// <returns>True if both objects are Quaternions of equal value. Otherwise it returns false.</returns>
		public override bool Equals(object other)
		{
			if (other is Quaternion == false) return false;
			return this == (Quaternion)other;
		}

		#endregion

		#region public override int GetHashCode ()

		/// <summary>
		/// Provides the hash code for this object. 
		/// </summary>
		/// <returns>A hash code formed from the bitwise XOR of this objects members.</returns>
		public override int GetHashCode()
		{
			return Xyz.GetHashCode() ^ W.GetHashCode();
		}

		#endregion

		#endregion

		#endregion

		#region IEquatable<Quaternion> Members

		/// <summary>
		/// Compares this Quaternion instance to another Quaternion for equality. 
		/// </summary>
		/// <param name="other">The other Quaternion to be used in the comparison.</param>
		/// <returns>True if both instances are equal; false otherwise.</returns>
		public bool Equals(Quaternion other)
		{
			return Xyz == other.Xyz && W == other.W;
		}

		#endregion
	}
}