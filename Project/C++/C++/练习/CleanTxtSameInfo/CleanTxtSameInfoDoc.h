// CleanTxtSameInfoDoc.h : CCleanTxtSameInfoDoc ��Ľӿ�
//


#pragma once


class CCleanTxtSameInfoDoc : public CDocument
{
protected: // �������л�����
	CCleanTxtSameInfoDoc();
	DECLARE_DYNCREATE(CCleanTxtSameInfoDoc)

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
	virtual ~CCleanTxtSameInfoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


