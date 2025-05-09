#include<iostream>
#include<queue>
using namespace std;
const int N=350;

struct point{
    int x;
    int y;
    int t;
};

queue<point> que;

char a[N][N];
bool vis[N][N];
int n,m;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int sx;
int sy;

void goto_another(int &nx,int &ny,int k)//goto_another��������Ѱ����һ�������ţ�nx��ny����ǰ������꣬�ǵ�Ҫ����ȡ��ַ��'&'����Ϊÿ������̤��һ�������ţ����ͻ���������������һ�������ţ�������ԭ��ͣ��
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==a[nx][ny]&&(i!=nx||j!=ny))//���a[i][j]��������һ����a[nx][ny]��ͬ�Ĵ����ţ�����a[i][j]��a[nx][ny]����ͬһ����
            {
                nx=i;//�ı䵱ǰ���꣬������ǿ���ƶ�����һ�������Ŵ�
                ny=j;
                return ;//���
            }
        }
    }
}
int main()
{

    cin>>n>>m;
    string s;
    for(int i=1;i<=n;i++)
    {
        cin>>s;//������������ֵֹ�û�пո����Ǻ��ѱ�ʹ���ַ�������
        for(int j=1;j<=m;j++)
        {
            a[i][j]=s[j-1];
            if(a[i][j]=='@')//��ȡ�������
            {
                sx=i;
                sy=j;
            }
        }
    }
    que.push((point){sx,sy,0});

    while(!que.empty())
    {
        point f=que.front();
        que.pop();
        if(a[f.x][f.y]=='=')
        {
            cout<<f.t;
            return 0;
        }
        if(a[f.x][f.y]>='A'&&a[f.x][f.y]<='Z')//���в��֣������ǰ����һ�������ţ���ô�ʹ�������һ��������
        {
            goto_another(f.x,f.y,f.t);
        }
        for(int i=0;i<=3;i++)
        {
            int nx=f.x+dx[i];
            int ny=f.y+dy[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]!='#'&&!vis[nx][ny])
            {
                vis[nx][ny]=true;
                que.push((point){nx,ny,f.t+1});
            }
        }
    }
    return 0;
}
