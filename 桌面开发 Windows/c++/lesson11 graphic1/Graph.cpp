#include "StdAfx.h"
#include "Graph.h"


CGraph::CGraph(void)
	: m_nDrawType(0)
{
}

CGraph::CGraph(int m_nDrwaType, CPoint m_ptOrigin, CPoint m_ptEnd)
{
	this->m_nDrawType = m_nDrwaType;
	this->m_ptOrigin = m_ptOrigin;
	this->m_ptEnd = m_ptEnd;
}

CGraph::~CGraph(void)
{
}
