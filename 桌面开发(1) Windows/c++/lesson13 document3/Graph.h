#pragma once

// �����л�����
class CGraph : public CObject
{
	DECLARE_SERIAL(CGraph)		// �������л�
public:
	CGraph(void);				// ����һ�����������Ĺ��캯��
	CGraph(int m_nDrwaType, CPoint m_ptOrigin, CPoint m_ptEnd);
	~CGraph(void);
	void Serialize(CArchive &ar);	// ��д��������л�����
	int		m_nDrawType;		// ͼ������
	CPoint	m_ptOrigin;
	CPoint	m_ptEnd;
	int Draw(CDC* pDC);			// ͼ�λ���
};

