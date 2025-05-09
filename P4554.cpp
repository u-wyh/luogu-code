//P4554
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<deque>
#include<vector>
#define N 503
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;

struct node{
    int x,y;
    node(int x=0,int y=0):x(x),y(y){}
};

char a[N][N];
bool vis[N][N];
int d[N][N];
const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};
int n,m,x1,y1,x2,y2;

inline void read(int &x);
void print(int x);
void bfs();

int main(){
    while(1){
        read(n),read(m);
        if(n==0&&m==0) break;
        for(int i=1;i<=n;++i){
            int j = 0;
            char c = getchar();
            while(c!='#'&&c!='@') c = getchar();
            while(c=='#'||c=='@'){
                a[i][++j] = c;
                c = getchar();
            }
        }
        read(x1),read(y1),read(x2),read(y2);
        ++x1,++y1,++x2,++y2;
        bfs();
        print(d[x2][y2]);
        putchar('\n');
    }
    return 0;
}

void bfs(){
    int x,y,nx,ny,w;
    memset(d,inf,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[x1][y1] = 0;
    deque<node> q; //�½�һֻ˫�˶���
    q.push_back(node(x1,y1));
    while(!q.empty()){
        x = q.front().x;
        y = q.front().y;
        q.pop_front();
        if(vis[x][y]) continue; //������bfs,����Ҫ�ж���û������,�����˾Ͳ���������
        vis[x][y] = true;
        for(int i=0;i<4;++i){ //������Χ����
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx>n||nx<1||ny>m||ny<1) continue; //�ж��Ƿ�Խ��
            w = a[nx][ny]!=a[x][y]; //ȷ����Ȩ,һ��Ϊ1,��һ��Ϊ0
            if(d[x][y]+w>=d[nx][ny]) continue; //�ɳڲ���
            d[nx][ny] = d[x][y]+w;
            if(w==0) q.push_front(node(nx,ny)); //0Ȩ��ǰ��
            else q.push_back(node(nx,ny)); //1Ȩ�ź���
        }
    }
}

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
    //cout<<endl;
}
