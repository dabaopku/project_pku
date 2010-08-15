#include"stdio.h"
#include "iostream"
using namespace std;

#define nodenum 1000005
struct TreeNode
{
	int id;
	TreeNode *next[26];    
};
TreeNode *s,*t,root1,treepoint[nodenum];
int pos,n,m,w,sx,sy,foundnum;
char box[1002][1002];
char word[1002];
int dp[1002][3];//状态0是行，1是列，2是方向
int dx[8]={-1,-1,0,1,1,1,0,-1};
int dy[8]={0,1,1,1,0,-1,-1,-1};

void creat(TreeNode & head)
{
	int i;
	for(i=0;i<26;i++)
		head.next[i]=NULL;
	head.id=-1;
	pos=0; 
}

void insert1(TreeNode &head,char *word,int id)
{
	s=&head;
	int i,j,k,len=strlen(word);
	for(i=0;i<len;i++)
	{
		if(s->next[word[i]-'A']==NULL)
			break;
		s=s->next[word[i]-'A'];              
	}
	if(i==len)
	{
		s->id=id;
		return ;       
	}     
	for(j=i;j<len;j++)
	{
		t=&treepoint[pos++];
		for(k=0;k<26;k++)
		{
			t->next[k]=NULL;             
		}              
		t->id=-1;
		s->next[word[j]-'A']=t;
		s=t;    
	}
	s->id=id;       
}
bool isinbox(int x,int y)
{
	if( x>=1 && x<=n && y>=1 && y<=m ) return 1;
	return 0; 
}    
void search1(TreeNode *root11,int x,int y,int k)	//搜索单词
{
	if(root11==NULL) return ;
	if(root11->id>-1) 
	{
		dp[root11->id][0]=sx;
		dp[root11->id][1]=sy;
		dp[root11->id][2]=k;
		root11->id=-1; 
		foundnum++;         
	} 
	if(isinbox(x,y))
	{
		search1(root11->next[box[x][y]-'A'],x+dx[k],y+dy[k],k);           
	}   
}            
int main()
{
	int i,j,k;
	while(scanf("%d%d%d",&n,&m,&w)!=EOF)
	{
		for(i=1;i<=n;i++)
			scanf("%s",box[i]+1); 
		creat(root1);                        
		for(i=1;i<=w;i++)
		{
			scanf("%s",&word);
			insert1(root1,word,i);             
		}
		foundnum=0;
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				for(k=0;k<8;k++){
					sx=i;
					sy=j;
					search1(&root1,i,j,k);//从 i,j开始沿k是方向
					if(foundnum==w)goto exitpoint;            
				}             
			}             
		}
exitpoint:    
		for(i=1;i<=w;i++)
			printf("%d %d %c\n",dp[i][0]-1,dp[i][1]-1,dp[i][2]+'A'); 

	}
	return 0;
}


