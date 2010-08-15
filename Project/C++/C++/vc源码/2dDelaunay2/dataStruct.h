#ifndef DATASTRUCT_H_H
#define DATASTRUCT_H_H

class EdgeNode: public CObject
{
public:
	int index;
	short nCount;
	
	EdgeNode(){
		nCount = 0;
		index = 0;
	}

	EdgeNode(int ind, int nCo){
		index = ind;
		nCount = nCo;
	}

//	~EdgeNode(){
//	}
};

class PointCls : public CObject
{
public:
	int index;
	int x;
	int y;
	bool vertex;//��õ���صı�ʹ�ô����Ƿ�Ϊ2
	bool intri;//���Ƿ�����������
	CObList* edgeList;

public:
	void iniEdgeList(CObList* temp){
		edgeList = temp;
	}

	int getIndex() { 
		return index;
	}

	double getX(){
		return x;
	}

	double getY(){
		return y;
	}
	
	CObList* getEdgeList(){
		return edgeList;
	}

	PointCls(int i, int j, int k){
		x = i;
		y = j;
		index = k;
		vertex = false;
		intri = false;
		edgeList = new CObList(100);
	}
	
	PointCls(){
		index = 0;
		y = 0;
		x = 0;
		vertex = false;
		intri = false;
		edgeList = 0;
	}

	~PointCls(){
		POSITION pos1;
		pos1 = edgeList->GetHeadPosition();
		while(pos1 != NULL)
		{
			EdgeNode* pEdge = (EdgeNode*)edgeList->GetNext(pos1);
			delete pEdge;
			pEdge = NULL;
		}
		if(!edgeList->IsEmpty())
		{
			edgeList->RemoveAll();
			edgeList = NULL;
		}
	}
};

class TriAngle: public CObject
{
public:
	bool enlarge;//���������Ƿ��Ѿ���չ
	int index[3];
public:
	TriAngle(int i, int j, int k){
		index[ 0 ] = i;
		index[ 1 ] = j;
		index[ 2 ] = k;

		enlarge = false;
	}

	int* getAngle(){
		return index;
	}
};

#endif