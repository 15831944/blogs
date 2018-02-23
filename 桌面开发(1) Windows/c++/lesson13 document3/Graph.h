#pragma once

// 可序列化的类
class CGraph : public CObject
{
	DECLARE_SERIAL(CGraph)		// 声明序列化
public:
	CGraph(void);				// 具有一个不带参数的构造函数
	CGraph(int m_nDrwaType, CPoint m_ptOrigin, CPoint m_ptEnd);
	~CGraph(void);
	void Serialize(CArchive &ar);	// 重写基类的序列化函数
	int		m_nDrawType;		// 图形数据
	CPoint	m_ptOrigin;
	CPoint	m_ptEnd;
	int Draw(CDC* pDC);			// 图形绘制
};

