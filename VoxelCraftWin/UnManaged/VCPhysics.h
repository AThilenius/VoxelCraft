//
//  VCPhysics.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/28/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once
#include "PCH.h"
#include "VCWorld.h"
#include "VCBlock.h"

typedef struct
{
	vec3 Origin;
	vec3 Direction;
	float MaxDistance;

} Ray;

typedef struct
{
	float Distance;
	byte Type;
	vec3 Normal;
	int X, Y, Z;

} RaycastHit;

inline float IntBound ( float s, float ds )
{
	if (ds < 0)
	{
		s = -s;
		ds = -ds;
	}

	if (s < 0)
		s = 1 + (s - (long)s);
	
	else
		s = s - (long)s;

	return (1 - s) / ds;
}

class VCPhysics
{
public:
	VCPhysics(void);
	~VCPhysics(void);

	static bool RaycastWorld(Ray ray, RaycastHit* hit)
	{
		VCWorld* world = VCWorld::Instance;

		vec3 wLoBound, wHiBound;
		world->GetWorldBounds(&wLoBound, &wHiBound);

		// Normalize Direction
		ray.Direction = normalize(ray.Direction);

		// Cube containing origin point.
		int x = FAST_FLOOR(ray.Origin.x);
		int y = FAST_FLOOR(ray.Origin.y);
		int z = FAST_FLOOR(ray.Origin.z);

		// Break out direction vector.
		float dx = ray.Direction.x;
		float dy = ray.Direction.y;
		float dz = ray.Direction.z;

		// Direction to increment x,y,z when stepping.
		float stepX = (0.0f < dx) - (dx < 0.0f);
		float stepY = (0.0f < dy) - (dy < 0.0f);
		float stepZ = (0.0f < dz) - (dz < 0.0f);

		// See description above. The initial values depend on the fractional
		// part of the origin.
		float tMaxX = IntBound(ray.Origin.x, dx);
		float tMaxY = IntBound(ray.Origin.y, dy);
		float tMaxZ = IntBound(ray.Origin.z, dz);

		// The change in t when taking a step (always positive).
		float tDeltaX = stepX/dx;
		float tDeltaY = stepY/dy;
		float tDeltaZ = stepZ/dz;

		// Buffer for reporting faces to the callback.
		vec3 face;

		// Avoids an infinite loop.
		if (dx == 0 && dy == 0 && dz == 0)
		{
			cout << "Attempted to ray-cast with a zero direction vector." << endl;
			return false;
		}

		while (/* ray has not gone past bounds of world */
				(stepX > 0 ? x < wHiBound.x : x >= wLoBound.x) &&
				(stepY > 0 ? y < wHiBound.y : y >= wLoBound.y) &&
				(stepZ > 0 ? z < wHiBound.z : z >= wLoBound.z)) 
		{

			// Already in world and hit a block?
			if (!(x < wLoBound.x || y < wLoBound.y || z < wLoBound.z || x >= wHiBound.x || y >= wHiBound.y || z >= wHiBound.z) && 
				world->GetBlock(x, y, z) > 1 )
			{
				// Hit!
				hit->Normal = face;
				hit->Type = world->GetBlock(x, y, z);
				hit->X = x;
				hit->Y = y;
				hit->Z = z;

				if (tMaxX < tMaxY) 
					if (tMaxX < tMaxZ) 
						hit->Distance = tMaxX;
					else
						hit->Distance = tMaxZ;
			
				else 
					if (tMaxY < tMaxZ) 
						hit->Distance = tMaxY;
					else 
						hit->Distance = tMaxZ;

				return true;
			}

			// tMaxX stores the t-value at which we cross a cube boundary along the
			// X axis, and similarly for Y and Z. Therefore, choosing the least tMax
			// chooses the closest cube boundary. Only the first case of the four
			// has been commented in detail.
			if (tMaxX < tMaxY) 
			{
				if (tMaxX < tMaxZ) 
				{
					if (tMaxX > ray.MaxDistance) 
						break;

					// Update which cube we are now in.
					x += stepX;
					// Adjust tMaxX to the next X-oriented boundary crossing.
					tMaxX += tDeltaX;
					// Record the normal vector of the cube face we entered.
					face = vec3(-stepX, 0, 0);
				} 
				
				else 
				{
					if (tMaxZ > ray.MaxDistance) 
						break;

					z += stepZ;
					tMaxZ += tDeltaZ;
					face = vec3(0, 0, -stepZ);
				}
			} 
			
			else 
			{
				if (tMaxY < tMaxZ) 
				{
				
					if (tMaxY > ray.MaxDistance) 
						break;

					y += stepY;
					tMaxY += tDeltaY;
					face = vec3(0, -stepY, 0);
				} 
				
				else 
				{
				// Identical to the second case, repeated for simplicity in
				// the conditionals.
					if (tMaxZ > ray.MaxDistance) 
						break;

					z += stepZ;
					tMaxZ += tDeltaZ;
					face = vec3(0, 0, -stepZ);
				}
			}
		}

		return false;
	}

    // ================================      Interop      ============
public:
    static void RegisterMonoHandlers();
    // ===============================================================
};

// Interop
bool VCInteropPhysicsRaycastWorld(Ray ray, RaycastHit* hitOut);