#include<bits/stdc++.h>
using namespace std;
int n;
int vis[1005][1005];
int h[4]={0,0,1,-1},s[4]={1,-1,0,0};
char a[1005][1005];
struct node{
	int x,y;
};
queue<node>q;

bool check(int x,int y){
	if(a[x][y]=='1')
	    return false;
	if(vis[x][y]>0)
	    return false;
	if(x>n||x<1)
	    return false;
	if(y>n||y<1)
	    return false;
	return true;
}

void bfs(int x,int y){
	vis[x][y]=1;
	q.push((node){x,y});
	while(q.size()!=0){
	    int xx=q.front().x;
	    int yy=q.front().y;
	    q.pop();
	    for(int i=0;i<4;i++){
		int xxx=xx+h[i];
		int yyy=yy+s[i];
		if(check(xxx,yyy)){
		    vis[xxx][yyy]=vis[xx][yy]+1;
		    q.push((node){xxx,yyy});
	        }
	    }
    }
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++){
		cin>>a[i][j];
	    }
	}
	int x1,x2,y1,y2;
	scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
	bfs(x1,x2);
	printf("%d",vis[y1][y2]-1);
	return 0;
}
