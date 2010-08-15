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

// ��Ŀ����ACM3038
// ����ʱ�䣺2009��9��26


//�ļ����ƣ�3083.cpp
//��Ŀ���ƣ�3083.vcproj
//�����ߣ�	����
//����ʱ�䣺2009-9-26
//����޸�ʱ�䣺2009-9-26
//���ܣ�	���ACM3038
//�ļ��еĺ������ƺͼ򵥹���������������ע��
//�ļ��ж����ȫ�ֱ����ͼ򵥹���������������ע��
//�ļ����õ������������ȫ�ֱ��������������
//�������ļ���������ϵ����

#include "iostream"
#include "queue"

using namespace std;

char maze[50][50];		//��¼�Թ�
int step[50][50];		//��¼�ߵ�ÿһ�����������Ҫ����
int w,h;				//�Թ����
int sx,sy,ex,ey;		//������յ�λ��
const int dirlf[2][4][2]={	{0,-1,1,0,0,1,-1,0},
							{0,1,1,0,0,-1,-1,0}};
//�洢�ߵ����ڸ���ʱ����ı仯���
//��һά 0��������,1��������
//�ڶ�ά ��ʾ ����һ������(0~3)ʱ ������/�� �� �������������Ĳ���
//  Ҳ����˵ 4������������תһȦ��Ҫ4��,������ָ����תȦ����ʼ��
//  �����ǰ��մ�С�����˳��,��תȦ�ǰ��մӴ�С��˳��
//  ����תȦʱ������ dir=(dir+3)%4 ���б仯��

struct point			//��ʾһ����Ľṹ��
{
	int x,y;
	point(int x_=0,int y_=0):x(x_),y(y_){};
};

void init()			//��ʼ������,�����ȡ����
{
	//�������ƣ�	init
	//����������������ʼ������,�����ȡ����
	//��������֮ǰ��Ԥ����������
	//���غ�Ĵ�����			��
	//����ֵ������еĻ�����	��
	//���������������			��
	//���������������			��
	//�����ĳ����㷨��α�룩�� ��
	//���������������к����ĵ��úͱ����ù�ϵ����

	memset(maze,'#',sizeof(maze));
	cin>>w>>h;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++){
			cin>>maze[i][j];
			if(maze[i][j]=='S'){	//��������
				sx=i;
				sy=j;
			} //end if
			else if(maze[i][j]=='E'){	//������յ�
				ex=i;
				ey=j;
			} //end else
		} //end i
}

int movelf(int type,int dir)	//ִ������/���ߵĹ���,�����ߵ�Ŀ��Ĳ���
// type��ת������,0Ϊ����,1Ϊ����
// dir �ǵ�ǰ��Է���,���嶨���� solve������
{
	//�������ƣ�	moveit
	//��������������ִ������/���ߵĹ���,�����ߵ�Ŀ��Ĳ���
	//��������֮ǰ��Ԥ��������solve�������dir
	//���غ�Ĵ�����			��
	//����ֵ������еĻ�����	�ߵ��յ�Ĳ���
	//���������������			type ת������  dir ��Է���
	//���������������			��
	//�����ĳ����㷨��α�룩�� ģ��
	//���������������к����ĵ��úͱ����ù�ϵ����

	int x=sx,y=sy;		//��õ�ǰλ������
	int ans=1;			//����ֵ,��Ϊ��ǰλ��ҲҪ��1��,���Գ�ʼ��Ϊ1
	while(x!=ex || y!=ey){	//ģ����·,ѭ��ֱ���ߵ��յ�
		for(int i=0;i<4;i++){	//�����ĸ�����,type=1���ȳ�������,�����ȳ�������

			if(maze[x+dirlf[type][dir][0]][y+dirlf[type][dir][1]]!='#'){
				//��ο�dirlf�Ķ���
				//����ٱ߸��ӿ����߾��߹�ȥ
				ans++;
				x+=dirlf[type][dir][0];	//��������λ��
				y+=dirlf[type][dir][1];
				dir=(dir+1)%4;		//������һ��ѭ���ķ���仯,��Ϊ��·��������Է������90��
				break;	//�ҵ�·�Ͳ���ѭ����
			} //end if
			dir=(dir+3)%4;	//ת��
		} //end for

		//��Ϊ��Ŀ��֤��·�Ĵ���,����û�н�����·���ߵ��ж�
	} //end while
	return ans;	//���ؽ��
}

int bfs()	//��������������ߵ��յ�����ٲ���
{
	//�������ƣ�	bfs
	//����������������������������ߵ��յ�����ٲ���
	//��������֮ǰ��Ԥ��������	��
	//���غ�Ĵ�����			��
	//����ֵ������еĻ�����	�ߵ��յ�����ٲ���
	//���������������			��
	//���������������			��
	//�����ĳ����㷨��α�룩�� �����������
	//���������������к����ĵ��úͱ����ù�ϵ����

	int i,j;
	const int inf=1000000;		//û�б����ʹ����
	for(i=0;i<=h+1;i++){		//��ʼ�� ���߸���
		for(j=0;j<=w+1;j++){
			if(maze[i][j]=='.') step[i][j]=inf;
		} //end for j
	} // end for i
	step[sx][sy]=1;		//��Ϊ��ǰλ��ҲҪ��1��,���Գ�ʼ��Ϊ1
	step[ex][ey]=inf;	//Ϊ�˼���ѭ���жϵ������յ��ʼ��
	queue<point> que;	//���Ѷ���,ʹ�� STL ģ���
						//���ǵ��������ݹ�ģ,Ϊ�˼��ٳ����ʵ���Ѷ�
						//û���� priority_queue�͹��ۺ���
	que.push(point(sx,sy));//��������
	point cur;				//��ǰλ��
	while(step[ex][ey]==inf && !que.empty()){	
				//��ʵ��һ���ж�û����,��Ϊ��Ŀ��֤�˽�Ĵ���
		cur=que.front();
		que.pop();	//���е�����һ���ڵ�
		for(i=0;i<4;i++){	//ö���ĸ�����,���û�б����ʹ��͸��¸ýڵ㲢������
							//������������ֱ��ʹ��������յķ���,��Ϊö��û��˳��Ҫ��
			if(step[cur.x+dirlf[0][i][0]][cur.y+dirlf[0][i][1]]==inf){
				step[cur.x+dirlf[0][i][0]][cur.y+dirlf[0][i][1]]=
					step[cur.x][cur.y]+1;	//�ߵ����Ĳ������ڵ�ǰ������1
				que.push(point(cur.x+dirlf[0][i][0],cur.y+dirlf[0][i][1]));
			} //end if
		} //end for
	} //end while
	return step[ex][ey];
}
void solve()  //��������ܲ���ӡ���
	//�������ƣ�	solve
	//����������������������ܲ���ӡ���
	//��������֮ǰ��Ԥ����������
	//���غ�Ĵ�����			��
	//����ֵ������еĻ�����	��
	//���������������			��
	//���������������			��
	//�����ĳ����㷨��α�룩��  ��
	//���������������к����ĵ��úͱ����ù�ϵ����
{
	int dir;
	// ������ dir=0
	// ������ dir=1
	// ������ dir=2
	// ������ dir=3

	if(sx==1) dir=2;
	else if(sx==h) dir=0;
	else if(sy==1) dir=1;
	else dir=3;
	//���ø��Ӻ���������
	cout<<movelf(0,dir)<<" "<<movelf(1,dir)<<" "<<bfs()<<endl;

}
int main()
{
	int cs;
	cin>>cs;
//	freopen("data.txt","r",stdin);
	while(cs--){ //�� case ����
		init();
		solve();
	}
	return 0;	//�������
}