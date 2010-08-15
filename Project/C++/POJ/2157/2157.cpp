#include "iostream"
#include "stdio.h"
using namespace std;
int c,r;
int key[5],door[5];
int sx,sy,gx,gy;
int dir[4][2]={-1,0,0,-1,1,0,0,1};
char maze[23][23];
char mazet[23][23];

int same(char move,char stay)
{
	if(stay=='X') return 0;
	if(stay=='.') return 1;
	if(move!='G' && stay=='G') return 0;
	if(stay<='E' && stay>='A' && move<='E' && move>='A') return 0;
	//if(move-stay=='A'-'a') return 0;
	return 1;
}
int find( char des ,int x,int y)
{
	int z=0;
	for(int i=0;i<4;i++){
		if(same(des,mazet[x+dir[i][0]][y+dir[i][1]])==0 ) {
			continue;
		}
		if(des=='G' && mazet[x+dir[i][0]][y+dir[i][1]]=='G' ) z++;

		if(des-mazet[x+dir[i][0]][y+dir[i][1]]=='A'-'a' ) z++;
		mazet[x+dir[i][0]][y+dir[i][1]]='X';
		mazet[x+dir[i][0]][y+dir[i][1]]='X';
		z+=find(des,x+dir[i][0],y+dir[i][1]);
	}
	return z;
}
int main()
{
	int i,j;
	while(cin>>r>>c,c){
		memset(maze,'X',sizeof(maze));
		memset(key,0,sizeof(key));
		memset(door,0,sizeof(door));
		for(i=1;i<=r;i++){
			for(j=1;j<=c;j++){
				cin>>maze[i][j];
				if(maze[i][j]<='e' && maze[i][j]>='a')
					key[maze[i][j]-'a']++;
				else if(maze[i][j]<='E' && maze[i][j]>='A')
					door[maze[i][j]-'A']=1;
				else if(maze[i][j]=='S'){
					sx=i;sy=j;
				}
				else if(maze[i][j]=='G'){
					gx=i;gy=j;
				}
			}
		}
		memcpy(mazet,maze,sizeof(maze));
		if( find('G',sx,sy)==0 ){
			cout<<"NO\n";
			continue;
		}
		for(i=0;i<5;i++){
			if(door[i]==0) continue;
			memcpy(mazet,maze,sizeof(maze));
			if( find(i+'A',sx,sy) != key[i]){
				cout<<"NO\n";
				break;
			}
		}
		if(i>=5)
			cout<<"YES\n";
			
	}
}