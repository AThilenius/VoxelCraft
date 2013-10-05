//
//  VCGui.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 9/2/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCText.h"
#include "VCLexicalEngine.h"
#include "VCIRenderable.h"

#define VC_GUI_VERT_SIZE 12000

struct GuiRectVerticie
{
	GuiRectVerticie(){}
	~GuiRectVerticie(){}
	GuiRectVerticie(GLushort2 position, GLubyte4 color):
		Position(position),
		Color(color)
	{
	}

	GLushort2 Position;
	GLubyte4 Color;
};

struct GuiTextDrawReq
{
	unsigned short X;
	unsigned short Y;

	GuiTextDrawReq(){}
	~GuiTextDrawReq(){}
	GuiTextDrawReq(unsigned short x, unsigned short y):
		X(x),
		Y(y)
	{
	}

	bool operator==(const GuiTextDrawReq &other) const
	{ 
		return (X == other.X && Y == other.Y);
	}
};

struct _GuiTextDrawReqHasher
{
	std::size_t operator()(const GuiTextDrawReq& k) const
	{
		return ((k.X << 16) | (k.Y));
	}
};

class VCGui : public VCIRenderable
{
public:
	VCGui(void)
	{
		VCGui::Instance = this;
	}

	~VCGui(void){}

	static void DrawRectangle ( Rectangle frame, GLubyte4 color )
	{
		if (m_vertCount >= VC_GUI_VERT_SIZE)
		{
			VC_ERROR("You have 2000+ Gui rectangles... too much man.");
		}

		GuiRectVerticie ll (GLushort2(frame.X,					frame.Y					), color);
		GuiRectVerticie ul (GLushort2(frame.X,					frame.Y	+ frame.Height	), color);
		GuiRectVerticie lr (GLushort2(frame.X + frame.Width,	frame.Y					), color);
		GuiRectVerticie ur (GLushort2(frame.X + frame.Width,	frame.Y	+ frame.Height	), color);

		VCGui::m_verts[VCGui::m_vertCount++] = ul;
		VCGui::m_verts[VCGui::m_vertCount++] = ll;
		VCGui::m_verts[VCGui::m_vertCount++] = lr;

		VCGui::m_verts[VCGui::m_vertCount++] = ul;
		VCGui::m_verts[VCGui::m_vertCount++] = lr;
		VCGui::m_verts[VCGui::m_vertCount++] = ur;
	}

	static void DrawText( string text, Point llPoint, string font = "Cambria-32", GLubyte4 color = GLubyte4(255, 255, 255, 255) )
	{
		VCGui::m_textFields.push_back(VCLexicalEngine::Instance->MakeText(font, text, llPoint.X, llPoint.Y, color));
	}

	static void Reset()
	{
		VCGui::m_vertCount = 0;

		for ( int i = 0; i < VCGui::m_textFields.size(); i++ )
			delete VCGui::m_textFields[i];

		VCGui::m_textFields.clear();

		if (VCGui::m_VAO != 0)
		{
			glDeleteBuffers(1, &VCGui::m_VAO);
			glDeleteBuffers(1, &VCGui::m_VBO);
			VCGui::m_VAO = 0;
		}
	}

	void Initialize()
	{
		// Create a render state for text rendering
		RenderState = new VCRenderState();
		RenderState->StageCount = 1;
		RenderState->BatchingOrder = VC_BATCH_GUI_BASE;
		RenderState->Stages[0].Shader = VCGLRenderer::Instance->GuiShader;
		RenderState->Stages[0].DepthTest = false;
		VCGLRenderer::Instance->RegisterState(RenderState);
		VCGLRenderer::Instance->RegisterIRenderable(this);
	}

	virtual VCRenderState* GetState() { return RenderState; }

	virtual void Render()
	{
		if (VCGui::m_vertCount == 0)
			return;

		if (VCGui::m_VAO == 0)
		{
			// Create VAO
			glGenVertexArrays(1, &VCGui::m_VAO);
			glBindVertexArray(VCGui::m_VAO);
			glErrorCheck();

			// Create VBO
			glGenBuffers(1, &VCGui::m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VCGui::m_VBO);
			ZERO_CHECK(VCGui::m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(GuiRectVerticie) * VCGui::m_vertCount, VCGui::m_verts , GL_STREAM_DRAW);

			// Bind Attributes
			glEnableVertexAttribArray(VC_ATTRIBUTE_POSITION);
			glEnableVertexAttribArray(VC_ATTRIBUTE_COLOR);

			glVertexAttribPointer(VC_ATTRIBUTE_POSITION,	2,	GL_UNSIGNED_SHORT,	GL_FALSE,	sizeof(GuiRectVerticie),	(void*) offsetof(GuiRectVerticie, Position) );
			glVertexAttribPointer(VC_ATTRIBUTE_COLOR,		4,	GL_UNSIGNED_BYTE,	GL_TRUE,	sizeof(GuiRectVerticie),	(void*) offsetof(GuiRectVerticie, Color) );

			glDrawArrays(GL_TRIANGLES, 0, VCGui::m_vertCount);

			glBindVertexArray(0);
		}
		else
		{
			glBindVertexArray(VCGui::m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, VCGui::m_vertCount);
			glBindVertexArray(0);
		}
		
	}

public:
	static VCGui* Instance;

private:
	VCRenderState* RenderState;

	static GLuint m_VAO;
	static GLuint m_VBO;
	static int m_vertCount;
	static GuiRectVerticie m_verts[VC_GUI_VERT_SIZE];
	static vector<VCText*> m_textFields;

	// ================================      Interop      ============
public:
	static void RegisterMonoHandlers();
	// ===============================================================
};

// Interop
void VCInteropGuiClear();
void VCInteropGuiDrawRectangle(Rectangle rect, vcint4 color);
void VCInteropGuiDrawText(MonoString* font, MonoString* text, Point point, vcint4 color);

