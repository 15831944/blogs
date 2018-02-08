#pragma once
class CGraph
{
public:
	CGraph(void);
	CGraph(int m_nDrwaType, CPoint m_ptOrigin, CPoint m_ptEnd);
	~CGraph(void);
	int m_nDrawType;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
};

