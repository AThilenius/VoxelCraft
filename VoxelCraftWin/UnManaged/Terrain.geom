//
//  Terrain.geom
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

//points
//line_strip
//triangle_strip
layout(points) in;
layout(triangle_strip, max_vertices = 20) out;

// input
in VSOutput
{
	vec3 color;
	int flags;
} vs_out[];

// output
out GSOutput
{
	vec3 color;
	vec3 normal;
} gs_out;

uniform mat4 MVP;

void main()
{
	vec4 centerPos = gl_in[0].gl_Position;
	vec3 shadowVal = vec3(.1, .1, .1);

	// throw away off-screen cubes to save some performance
	vec4 centerNDCPos = MVP * centerPos;
	/*if (centerNDCPos.x < -centerNDCPos.w
		|| centerNDCPos.x > centerNDCPos.w
		|| centerNDCPos.y < -centerNDCPos.w
		|| centerNDCPos.y > centerNDCPos.w
		|| centerNDCPos.z < -centerNDCPos.w
		|| centerNDCPos.z > centerNDCPos.w)
		return;*/

	// =====   Reference:

	// Upper
	//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y + 1, m_blockZ + z).IsSolid() ) flags = flags & 1;
	//if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z - 1).IsSolid() ) flags = flags & 2;
	//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y + 1, m_blockZ + z).IsSolid() ) flags = flags & 4;
	//if ( m_world->GetBlock(m_blockX + x, m_blockY + y + 1, m_blockZ + z + 1).IsSolid() ) flags = flags & 8;

	// Middle
	//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags & 16;
	//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags & 32;
	//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags & 64;
	//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags & 128;

	// Lower
	//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y - 1, m_blockZ + z).IsSolid() ) flags = flags & 256;
	//if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z - 1).IsSolid() ) flags = flags & 512;
	//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY - y + 1, m_blockZ + z).IsSolid() ) flags = flags & 1024;
	//if ( m_world->GetBlock(m_blockX + x, m_blockY + y - 1, m_blockZ + z + 1).IsSolid() ) flags = flags & 2048;

	// Occludes
	//if ( m_world->GetBlock(m_blockX + x - 1, m_blockY + y, m_blockZ + z).IsSolid() ) flags = flags | 4096;
	//if ( m_world->GetBlock(m_blockX + x + 1, m_blockY + y, m_blockZ + z).IsSolid() ) flags = flags | 8192;
	//if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z - 1).IsSolid() ) flags = flags | 16384;
	//if ( m_world->GetBlock(m_blockX + x, m_blockY + y, m_blockZ + z + 1).IsSolid() ) flags = flags | 32768;

	float u1 = float(vs_out[0].flags & 1) * 1;
	float u2 = float(vs_out[0].flags & 2) * 0.5;
	float u3 = float(vs_out[0].flags & 4) * 0.25;
	float u4 = float(vs_out[0].flags & 8) * 0.125;

	float m5 = float(vs_out[0].flags & 16) * 0.0625;
	float m6 = float(vs_out[0].flags & 32) * 0.03125;
	float m7 = float(vs_out[0].flags & 64) * 0.015625;
	float m8 = float(vs_out[0].flags & 128) * 0.0078125;

	float l9 = float(vs_out[0].flags & 256) * 0.00390625;
	// Truncation problems start here...
	float l10 = float(vs_out[0].flags & 512) * 0.001953125;
	float l11 = float(vs_out[0].flags & 1024) * 0.0009765625;
	float l12 = float(vs_out[0].flags & 2048) * 0.00048828125;

	// -X
	if( (vs_out[0].flags & 4096) == 0 ) 
	{
		gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * m5;
		gs_out.normal = vec3(1, 0, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * m6;
		gs_out.normal = vec3(1, 0, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m5 - shadowVal * l9;
		gs_out.normal = vec3(1, 0, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m6 - shadowVal * l9;
		gs_out.normal = vec3(1, 0, 0);
		EmitVertex();
	}
	EndPrimitive();

	// +X
	if( (vs_out[0].flags & 8192) == 0 ) 
	{
		gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u3 - shadowVal * m7;
		gs_out.normal = vec3(-1, 0, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u3 - shadowVal * m8;
		gs_out.normal = vec3(-1, 0, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m7 - shadowVal * l11;
		gs_out.normal = vec3(-1, 0, 0);
		EmitVertex();
			
		gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m8 - shadowVal * l11;
		gs_out.normal = vec3(-1, 0, 0);
		EmitVertex();
	}
	EndPrimitive();

	// -Y never drawn
	/*{
		gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color;
		gs_out.normal = vec3(0, 1, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color;
		gs_out.normal = vec3(0, 1, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color;
		gs_out.normal = vec3(0, 1, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color;
		gs_out.normal = vec3(0, 1, 0);
		EmitVertex();
	}
	EndPrimitive();*/

	// +Y
	{
		gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u2 - shadowVal * u3;
		gs_out.normal = vec3(0, -1, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * u2;
		gs_out.normal = vec3(0, -1, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u3 - shadowVal * u4;
		gs_out.normal = vec3(0, -1, 0);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u1 - shadowVal * u4;
		gs_out.normal = vec3(0, -1, 0);
		EmitVertex();
	}
	EndPrimitive();
	// -Z
	if( (vs_out[0].flags & 16384) == 0 ) 
	{
		gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m6 - shadowVal * l10;
		gs_out.normal = vec3(0, 0, 1);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u2 - shadowVal * m6;
		gs_out.normal = vec3(0, 0, 1);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m7 - shadowVal * l10;
		gs_out.normal = vec3(0, 0, 1);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 0.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u2 - shadowVal * m7;
		gs_out.normal = vec3(0, 0, 1);
		EmitVertex();
	}
	EndPrimitive();
	// +Z
	if( (vs_out[0].flags & 32768) == 0 ) 
	{
		gl_Position = MVP * (centerPos + vec4(1.0, 0.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m8 - shadowVal * l12;
		gs_out.normal = vec3(0, 0, -1);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(1.0, 1.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u4 - shadowVal * m8;
		gs_out.normal = vec3(0, 0, -1);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 0.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * m5 - shadowVal * l12;
		gs_out.normal = vec3(0, 0, -1);
		EmitVertex();

		gl_Position = MVP * (centerPos + vec4(0.0, 1.0, 1.0, 0.0));
		gs_out.color = vs_out[0].color - shadowVal * u4 - shadowVal * m5;
		gs_out.normal = vec3(0, 0, -1);
		EmitVertex();
	}
	EndPrimitive();
}