// ����ϵر�֤��

// ���Լ��������������������ӷ�������Ƶ���������й�����
// ��������������У���������ʲô���Ѷ�������ˣ���ô���ҽ��ڳ���ʵϰ������
// ��ϸ���о��������������⣬�Լ����˸��ҵ���ʾ��

// �ڴˣ��Ҹ�л XXX, ��, XXX���ҵ������Ͱ���������ı����У��һ��������ᵽ
// �����ڸ����������ҵİ�����

// �ҵĳ������з������õ�����������ĵ�֮����
// ����̲ġ����ñʼǡ����ϵ�Դ�����Լ������ο����ϵĴ����,
// �Ҷ��Ѿ��ڳ����ע����������ע�������õĳ�����

// �Ҵ�δ��Ϯ�����˵ĳ���Ҳû�е��ñ��˵ĳ���
// �������޸�ʽ�ĳ�Ϯ����ԭ�ⲻ���ĳ�Ϯ��

// �ұ�д������򣬴���û�����Ҫȥ�ƻ���������������ϵͳ��������ת��

// ����

// ��Ŀ����ACM2251
// ����ʱ�䣺2009��9��26


//�ļ����ƣ�2251.cpp
//��Ŀ���ƣ�2251.vcproj
//�����ߣ�	����
//����ʱ�䣺2009-9-26
//����޸�ʱ�䣺2009-9-26
//���ܣ�	���ACM2251
//�ļ��еĺ������ƺͼ򵥹���������������ע��
//�ļ��ж����ȫ�ֱ����ͼ򵥹���������������ע��
//�ļ����õ������������ȫ�ֱ��������������
//�������ļ���������ϵ����

//				���н��
//	Problem: 2251		User: 00846086
//	Memory: 456K		Time: 63MS
//	Language: C++		Result: Accepted


#include "iostream"
#include "queue"

using namespace std;

struct point				//��ʾһ����Ľṹ��
{
	int x,y,z;
	point(int x_=0,int y_=0,int z_=0):x(x_),y(y_),z(z_){};
};

int maze[35][35][35];		//��¼�Թ�
							//�洢Ϊ�ߵ�ÿһ�����������Ҫ����
int l,r,c;					//�Թ����
point ps,pe;				//������յ�λ��
const int dir[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
							//�洢�ߵ����ڸ���ʱ����ı仯���
const int inf=1000000;		//û�б����ʹ����

bool init()			//��ʼ������,�����ȡ����
{
	//�������ƣ�	init
	//����������������ʼ������,�����ȡ����
	//��������֮ǰ��Ԥ����������
	//���غ�Ĵ�����			��
	//����ֵ������еĻ�����	������� 0 0 0 ����false,���򷵻�true
	//���������������			��
	//���������������			��
	//�����ĳ����㷨��α�룩�� ��
	//���������������к����ĵ��úͱ����ù�ϵ����

	cin>>l>>r>>c;
	if(!(l || r || c)) return false;
	memset(maze,-1,sizeof(maze));	//������λ������Ϊ-1
	char ch;
	for(int i=1;i<=l;i++){
		for(int j=1;j<=r;j++){
			for(int k=1;k<=c;k++){
				cin>>ch;
				if(ch=='.'){
					maze[i][j][k]=inf;
				}
				else if(ch=='S'){
					maze[i][j][k]=0;	//��ʼ���ʼ��Ϊ0
					ps=point(i,j,k);
				}
				else if(ch=='E'){
					maze[i][j][k]=inf;
					pe=point(i,j,k);
				}
			}	//end for k
		}	//end for j
	} //end i

	return true;
}

int bfs()	//��������������ߵ��յ�����ٲ���
{
	//�������ƣ�	bfs
	//����������������������������ߵ��յ�����ٲ���
	//��������֮ǰ��Ԥ��������	��
	//���غ�Ĵ�����			��
	//����ֵ������еĻ�����	�ߵ��յ�����ٲ���,ʧ�ܷ���-1
	//���������������			��
	//���������������			��
	//�����ĳ����㷨��α�룩�� �����������
	//���������������к����ĵ��úͱ����ù�ϵ����

	queue<point> que;	//���Ѷ���,ʹ�� STL ģ���
		//���ǵ��������ݹ�ģ,Ϊ�˼��ٳ����ʵ���Ѷ�
		//û���� priority_queue�͹��ۺ���
	que.push(ps);		//��������
	point cur;			//��ǰλ��

	while(maze[pe.x][pe.y][pe.z]==inf && !que.empty()){	
			//����

		cur=que.front();
		que.pop();	//���е�����һ���ڵ�

		for(int i=0;i<6;i++){	//ö����������,���û�б����ʹ��͸��¸ýڵ㲢������
			if(maze[cur.x+dir[i][0]][cur.y+dir[i][1]][cur.z+dir[i][2]]==inf){
				maze[cur.x+dir[i][0]][cur.y+dir[i][1]][cur.z+dir[i][2]]=
					maze[cur.x][cur.y][cur.z]+1;	//�ߵ����Ĳ������ڵ�ǰ������1
				que.push(point(cur.x+dir[i][0],cur.y+dir[i][1],cur.z+dir[i][2]));
			} //end if
		} //end for
	} //end while
	if(maze[pe.x][pe.y][pe.z]==inf)	//����޽�
		return -1;
	else
		return maze[pe.x][pe.y][pe.z];
}

void solve()  //��������ܲ���ӡ���
{
	//�������ƣ�	solve
	//����������������������ܲ���ӡ���
	//��������֮ǰ��Ԥ����������
	//���غ�Ĵ�����			��
	//����ֵ������еĻ�����	��
	//���������������			��
	//���������������			��
	//�����ĳ����㷨��α�룩��  ��
	//���������������к����ĵ��úͱ����ù�ϵ����

	int ans=bfs();
	//������
	if(ans==-1)
		cout<<"Trapped!\n";
	else
		cout<<"Escaped in "<<ans<<" minute(s).\n";
}
int main()
{
	//freopen("data.txt","r",stdin);
	while(init()){ //�� case ����
		solve();
	}
	return 0;	//�������
}