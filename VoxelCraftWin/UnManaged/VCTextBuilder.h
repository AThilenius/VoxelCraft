//
//  VCTextBuilder.h
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 10/9/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#pragma once

#include "PCH.h"
#include "VCRenderState.h"
#include "VCLexicalEngine.h"

// 1.44 MB - 10,000 Characters
#define VC_TEXT_MAX_VERT_SIZE 60000

struct GuiTextDrawReq
{
	unsigned short X;
	unsigned short Y;

	GuiTextDrawReq(){}
	GuiTextDrawReq(unsigned short x, unsigned short y): X(x), Y(y){}
	~GuiTextDrawReq(){}

	bool operator<(const GuiTextDrawReq& other) const
	{
		return X < other.X && Y < other.Y;
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


class VCTextBuilder
{
public:
	VCTextBuilder(void){}
	~VCTextBuilder(void){}

	void Reset()
	{
		// Anything remaining in m_rebuilds is 'old' and needs to go.
		for ( auto iter = m_rebuilds.begin(); iter != m_rebuilds.end(); iter++ )
		{
			cout << "Freeing VCText" << endl;
			auto vctextIter = m_text.find(*iter);
			delete vctextIter->second;
			m_text.erase(vctextIter);
		}

		m_rebuilds.clear();

		// Insert them all back into m_rebuild
		for ( auto iter = m_text.begin(); iter != m_text.end(); iter++ )
			m_rebuilds.insert(ReqSet::value_type(iter->first));
	}

	void Initialize()
	{
		
	}

	void DrawText( string text, Point llPoint, string font = "Cambria-16", GLubyte4 color = GLubyte4(255, 255, 255, 255) )
	{
		GuiTextDrawReq v (llPoint.X, llPoint.Y);

		if (m_text.find(v) == m_text.end())
		{
			cout << "Allocating new VCText" << endl;
			m_text.insert(ReqToText::value_type(v, VCLexicalEngine::Instance->MakeText(font, text, llPoint.X, llPoint.Y, color)));
		}

		else
			m_rebuilds.erase(m_rebuilds.find(v));
	}

private:
	typedef unordered_map<GuiTextDrawReq, VCText*, _GuiTextDrawReqHasher> ReqToText;
	typedef unordered_set<GuiTextDrawReq, _GuiTextDrawReqHasher> ReqSet;

	ReqToText m_text;
	ReqSet m_rebuilds;
};

