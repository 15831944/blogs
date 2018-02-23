#include "StdAfx.h"
#include "Graph.h"

IMPLEMENT_SERIAL(CGraph, CObject, 1)	// 实现序列化, 版本号为1(保存和读取的版本号应一致)

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

void CGraph::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// 保存数据
		ar << m_nDrawType << m_ptOrigin << m_ptEnd;
	}
	else
	{
		// 加载数据
		ar >> m_nDrawType >> m_ptOrigin >> m_ptEnd;
	}
}

int CGraph::Draw(CDC* pDC)
{
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush = pDC->SelectObject(pBrush);
	switch (m_nDrawType)
	{
	case 1:
		pDC->SetPixel(m_ptEnd, RGB(0, 0, 0));
		break;
	case 2:
		pDC->MoveTo(m_ptOrigin);
		pDC->LineTo(m_ptEnd);
		break;
	case 3:
		pDC->Rectangle(CRect(m_ptOrigin, m_ptEnd));
		break;
	case 4:
		pDC->Ellipse(CRect(m_ptOrigin, m_ptEnd));
		break;
	default:
		break;
	}
	pDC->SelectObject(pOldBrush);
	return 0;
}
