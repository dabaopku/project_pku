// Li3_6Doc.h : CLi3_6Doc ��Ľӿ�
//


#pragma once


class CLi3_6Doc : public CDocument
{
protected: // �������л�����
	CLi3_6Doc();
	DECLARE_DYNCREATE(CLi3_6Doc)

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
	virtual ~CLi3_6Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


