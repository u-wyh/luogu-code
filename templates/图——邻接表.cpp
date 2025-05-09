#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11;
const int MAXM = 21;

int t;

//�ڽӾ����Լ��ڽӱ����
int n,m;
int nums[MAXN][MAXN];
int edge[MAXM][3];
vector<vector<pair<int ,int>>>graph;

//��ʽǰ���Ǳ���
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

void build(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[i][j]=0;
        }
    }
    //�ڽӾ�������

    graph.resize(n+1);
    graph.clear();
    //�ڽӱ�����

    cnt=1;
    memset(head,0,sizeof(head));
    //��ʽǰ����ֻ��Ҫ���head�Ϳ���  ���������ݻ��ᱻ����
}

void directgraph(){
    //�ڽӾ���ͼ
    for(int i=1;i<=m;i++){
        nums[edge[i][0]][edge[i][1]]=edge[i][2];
    }

    //�ڽӱ�ͼ
    for(int i=1;i<=m;i++){
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
    }

    //��ʽǰ���ǽ�ͼ
    for(int i=1;i<=m;i++){
        Next[cnt]=head[edge[i][0]];
        to[cnt]=edge[i][1];
        weight[cnt]=edge[i][2];
        head[edge[i][0]]=cnt++;
    }
}

void showgraph(){
    cout<<endl;
    //�ڽӾ���
    cout<<"�ڽӾ�������� \n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%3d",nums[i][j]);
        }
        printf("\n");
    }
    cout<<endl;

    //�ڽӱ�
    cout<<"�ڽӱ������\n";
    for(int i=1;i<=n;i++){
        cout<<i<<"(�ھӣ���Ȩ): ";
        for(int j=0;j<graph[i].size();j++){
            cout<<"("<<graph[i][j].first<<" ,"<<graph[i][j].second<<" )";
        }
        cout<<endl;
    }
    cout<<endl;

    //��ʽǰ����
    cout<<"��ʽǰ���������\n";
    for(int i=1;i<=n;i++){
        cout<<i<<"(�ھӣ���Ȩ): ";
        for(int j=head[i];j>0;j=Next[j]){
            cout<<"("<<to[j]<<" ,"<<weight[j]<<" )";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    cin>>t;
        while(t--){
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        }
        //�����Ȩͼ
        build();
        directgraph();
        showgraph();
        system("pause");
    }
    return 0;
}
