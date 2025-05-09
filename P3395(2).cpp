#include<bits/stdc++.h>
using namespace std;

int n;
int death[1005][1005];
int t[1005][1005];
int T;
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    cin>>T;
    while(T--){
        memset(death,0,sizeof(death)); // ��ʼ��Ϊ0����ʾ��δ����·��
        memset(t,-1,sizeof(t)); // ��ʼ��Ϊ-1����ʾ��δ����
        cin>>n;
        int x,y;
        for(int i=1;i<=2*n-2;i++){
            cin>>x>>y;
            death[x][y]=i; // ��¼·�ϵķ���ʱ��
        }
        t[1][1]=0;
        Q.push({1,1});
        while(!Q.empty()){
            coord u=Q.front();
            Q.pop();
            int ux=u.x,uy=u.y,utime=t[ux][uy];
            if(ux == n && uy == n) { // �����յ�
                printf("Yes\n");
                goto next_test; // ������һ���������
            }
            for(int k=0;k<4;k++){
                int x=ux+walk[k][0],y=uy+walk[k][1];
                if(x>0 && x<=n && y>0 && y<=n && t[x][y] == -1 && (utime+1 < death[x][y] || death[x][y] == 0)) {
                    // ����Ƿ�Խ�磬�Ƿ�δ���ʹ����Լ��ڸ�λ�÷���·��֮ǰ�ܷ񵽴�
                    t[x][y]=utime+1;
                    Q.push({x,y});
                }
            }
        }
        printf("No\n");
    next_test:
        continue; // ʵ���������continue�Ƕ���ģ���Ϊwhileѭ�����Զ�����
    }
    return 0;
}
