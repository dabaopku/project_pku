// Li3_2Doc.h : CLi3_2Doc ��Ľӿ�
//


#pragma once


class CLi3_2Doc : public CDocument
{
protected: // �������л�����
	CLi3_2Doc();
	DECLARE_DYNCREATE(CLi3_2Doc)

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
	virtual ~CLi3_2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


