// EvolutionDoc.h : EvolutionDoc ��Ľӿ�
//


#pragma once


class EvolutionDoc : public CDocument
{
protected: // �������л�����
	EvolutionDoc();
	DECLARE_DYNCREATE(EvolutionDoc)

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
	virtual ~EvolutionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


