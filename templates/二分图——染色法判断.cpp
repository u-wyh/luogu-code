#include<bits/stdc++.h>
using namespace std;

int n,m;//��ʾ��n���㣬m����

int head[10];
int Next[50];
int to[50];
int cnt=1;//��ʽǰ���ǽ�ͼ

int color[10];//��ʾ���������ɫ��1Ϊ��ɫ��2Ϊ��ɫ

bool dfs(int now,int col){
    color[now]=col;//��Ⱦɫ
    for(int i=head[now];i>0;i=Next[i]){
        int v=to[i];
        if(color[v]==col){
            //��������Ⱦ���� ���Ҳ��Ϸ�
            return false;
        }
        else if(!dfs(v,3-col)){//�ݹ鵽��һ���㣬��ɫ�任
            return false;
        }
    }
    return true;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
    }
    for(int i=1;i<=n;i++){
        if(color[i]==0){
            if(!dfs(i,1)){
                cout<<"NO"<<endl;
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<color[i]<<' ';
    }
    cout<<endl;
    cout<<"YES"<<endl;
    return 0;
}

/*
�������ݣ�
6 6
1 2 1 3 2 6 2 5 2 4 6 3

6 8
1 2 1 3 2 6 2 5 2 4 6 3 4 5 1 6

6 7
1 2 1 3 2 6 2 5 2 4 6 3 4 5
*/
