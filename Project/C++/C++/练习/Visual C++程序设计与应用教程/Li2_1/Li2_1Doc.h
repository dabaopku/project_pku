// Li2_1Doc.h : CLi2_1Doc ��Ľӿ�
//


#pragma once


class CLi2_1Doc : public CDocument
{
protected: // �������л�����
	CLi2_1Doc();
	DECLARE_DYNCREATE(CLi2_1Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CLi2_1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


