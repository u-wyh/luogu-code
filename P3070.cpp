#include<bits/stdc++.h>
using namespace std;

int n,m;//�ֱ��ʾ�к���
int nums[50][50];//�������Ϊ����
int cnt=0;//��ʾ������
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int dp[50][50][1<<15];//����Ҫע��(1<<(i-1))
int d[20][20];//��ʾ�ӵ���i������j������Ҫ����ǳˮ��
deque<pair<int,int >>deq;
int in[50][50];

void setnum(int x,int y,int num){
    nums[x][y]=num;
    for(int i=0;i<4;i++){
        int ux=x+walk[i][0];
        int uy=y+walk[i][1];
        if(ux>0&&uy>0&&ux<n&&uy<n&&nums[ux][uy]==20){
            setnum(ux,uy,num);
        }
    }
}
//���õ�����

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char c;
            cin>>c;
            if(c=='X'){
                nums[i][j]=20;//��ʱ����Ϊ20
            }
            else if(c=='S'){
                nums[i][j]=0;//ǳˮ������Ϊ0
            }
            else
                nums[i][j]=-1;//��ˮ������Ϊ-1
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(nums[i][j]=20){
                setnum(i,j,++cnt);
                //��ˮ��� ���ñ��
                //����cnt��ʾһ���ж��ٸ�����
            }
        }
    }
    for(int k=1;k<=cnt;i++){
        d[k][k]=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                in[i][j]=false;
                if(nums[i][j]==k){
                    deq.push_front({i,j});
                    in[i][j]=true;
                }
            }
        }
        while(!deq.empty()){
            int x=deq.front().first;
            int y=deq.front().second;
            for(int i=0;i<4;i++){
                int xx=x+walk[i][0];
                int yy=y+walk[i][1];
                if(xx<0||xx>n||yy<0||yy>n||in[xx][yy]||nums[xx][yy]==-1){
                    continue;
                }
                in[xx][yy]=true;
                if(nums[xx][yy]==0){
                    deq.push_back({xx,yy});
                }
                else{
                    deq.push_front({xx,yy});
                    if(nums[xx][yy]!=k&&!d[k][nums[xx][yy]]){
                        d[k][nums[xx][yy]]=
                    }
                }
            }
        }
    }
    return 0;
}
