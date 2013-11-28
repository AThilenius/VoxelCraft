//
//  TerrainConstruction.geom
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 11/14/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#version 150

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices = 30) out;

// From Vertex Shader ( Must be arrays :( So ugly )
in Inputs
{
	vec3 colorIn;
	int flagsIn;
} In[];

// To Transform Feedback Buffer
out vec3 normalOut;
out vec3 colorOut;

void main()
{
	vec3 shadowVal = vec3(.1, .1, .1);


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

	float u1 = float(In[0].flagsIn & 1) * 1;
	float u2 = float(In[0].flagsIn & 2) * 0.5;
	float u3 = float(In[0].flagsIn & 4) * 0.25;
	float u4 = float(In[0].flagsIn & 8) * 0.125;

	float m5 = float(In[0].flagsIn & 16) * 0.0625;
	float m6 = float(In[0].flagsIn & 32) * 0.03125;
	float m7 = float(In[0].flagsIn & 64) * 0.015625;
	float m8 = float(In[0].flagsIn & 128) * 0.0078125;

	float l9 = float(In[0].flagsIn & 256) * 0.00390625;
	// Truncation problems start here...
	float l10 = float(In[0].flagsIn & 512) * 0.001953125;
	float l11 = float(In[0].flagsIn & 1024) * 0.0009765625;
	float l12 = float(In[0].flagsIn & 2048) * 0.00048828125;

	// -X
	if( (In[0].flagsIn & 4096) == 0 ) 
	{
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u1 - shadowVal * m5;
		normalOut = vec3(1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u1 - shadowVal * m6;
		normalOut = vec3(1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m5 - shadowVal * l9;
		normalOut = vec3(1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
		

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m5 - shadowVal * l9;
		normalOut = vec3(1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u1 - shadowVal * m6;
		normalOut = vec3(1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m6 - shadowVal * l9;
		normalOut = vec3(1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
	}

	// +X
	if( (In[0].flagsIn & 8192) == 0 ) 
	{
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u3 - shadowVal * m7;
		normalOut = vec3(-1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u3 - shadowVal * m8;
		normalOut = vec3(-1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m7 - shadowVal * l11;
		normalOut = vec3(-1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
		
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m7 - shadowVal * l11;
		normalOut = vec3(-1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u3 - shadowVal * m8;
		normalOut = vec3(-1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m8 - shadowVal * l11;
		normalOut = vec3(-1, 0, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
	}

	// -Y never drawn
	/*{
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn;
		normalOut = vec3(0, 1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn;
		normalOut = vec3(0, 1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn;
		normalOut = vec3(0, 1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
		
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn;
		normalOut = vec3(0, 1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn;
		normalOut = vec3(0, 1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn;
		normalOut = vec3(0, 1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
	}*/

	// +Y
	{
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u2 - shadowVal * u3;
		normalOut = vec3(0, -1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u1 - shadowVal * u2;
		normalOut = vec3(0, -1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u3 - shadowVal * u4;
		normalOut = vec3(0, -1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
		
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u3 - shadowVal * u4;
		normalOut = vec3(0, -1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u1 - shadowVal * u2;
		normalOut = vec3(0, -1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u1 - shadowVal * u4;
		normalOut = vec3(0, -1, 0);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
	}

	// -Z
	if( (In[0].flagsIn & 16384) == 0 ) 
	{
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m6 - shadowVal * l10;
		normalOut = vec3(0, 0, 1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u2 - shadowVal * m6;
		normalOut = vec3(0, 0, 1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m7 - shadowVal * l10;
		normalOut = vec3(0, 0, 1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m7 - shadowVal * l10;
		normalOut = vec3(0, 0, 1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u2 - shadowVal * m6;
		normalOut = vec3(0, 0, 1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 0.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u2 - shadowVal * m7;
		normalOut = vec3(0, 0, 1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
	}

	// +Z
	if( (In[0].flagsIn & 32768) == 0 ) 
	{
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m8 - shadowVal * l12;
		normalOut = vec3(0, 0, -1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();

		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u4 - shadowVal * m8;
		normalOut = vec3(0, 0, -1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m5 - shadowVal * l12;
		normalOut = vec3(0, 0, -1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();

		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 0.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * m5 - shadowVal * l12;
		normalOut = vec3(0, 0, -1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(1.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u4 - shadowVal * m8;
		normalOut = vec3(0, 0, -1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		
		gl_Position = (gl_in[0].gl_Position + vec4(0.0, 1.0, 1.0, 0.0));
		colorOut = In[0].colorIn - shadowVal * u4 - shadowVal * m5;
		normalOut = vec3(0, 0, -1);
		colorOut=vec3(8,8,8);normalOut=vec3(9,9,9);EmitVertex();
		EndPrimitive();
	}

}