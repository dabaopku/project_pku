// EvolutionDoc.h : CEvolutionDoc ��Ľӿ�
//


#pragma once


class CEvolutionDoc : public CDocument
{
protected: // �������л�����
	CEvolutionDoc();
	DECLARE_DYNCREATE(CEvolutionDoc)

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
	virtual ~CEvolutionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


