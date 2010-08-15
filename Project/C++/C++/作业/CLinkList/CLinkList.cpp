#include <iostream>
using namespace std;
template <class D>
class Node {
public:	
	D data;
	Node * next;
};
template<class D>
class CLinkList 
{
private:
	Node<D> * pHead;
public:
	CLinkList();
	void AppendNode( D data);
	void PrintList();
};
template<class D>
CLinkList<D>::CLinkList() {
	pHead = new Node<D>;
	pHead->next = NULL;
};
template<class D>
void CLinkList<D>::AppendNode( D data)
{
	Node<D> * pTemp=pHead;
	while(pTemp->next!=NULL)
		pTemp=pTemp->next;
	Node<D>* pLast = new Node<D>;
	pTemp->next = pLast;
	pLast->next = NULL;
	pLast->data = data;
}
template<class D>
void CLinkList<D>::PrintList()
{
	Node<D> * pTemp=pHead->next;
	while(pTemp!=NULL){
		cout<<pTemp->data<<",";
		pTemp=pTemp->next;
	}
}
int main()
{
	CLinkList<int> l;
	for( int i = 0;i < 4;i ++)
		l.AppendNode(i);
	l.PrintList();
	cout << endl;
	for( int i = 9;i < 12;i ++)
		l.AppendNode(i);
	l.PrintList();
}

