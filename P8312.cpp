#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 75;
const int MAXM = 1000005;

int n,m,k,q;
int cur[MAXN],Next[MAXN];
int edge[MAXM][3];

void bellman(int st,int en){
    for(int i=1;i<=n;i++){
        cur[i]=INT_MAX;
    }
    cur[st]=0;
    for(int i=0;i<=k-1;i++){
        for(int j=1;j<=n;j++){
            Next[j]=cur[j];
        }
        //����Ҫ����Next����  ��Ϊ����һ�ֿ�����  ������һ���Ż���  ͬʱʵ����������  ��������������ͳ��k
        for(int j=1;j<=m;j++){
            if (cur[edge[j][0]] != INT_MAX) {
                //�������������  ˵�����Ե���edge[j][0]  ��ô���Լ��������Ż���һ��edge[j][1]
                Next[edge[j][1]] = min(Next[edge[j][1]], cur[edge[j][0]] + edge[j][2]);
                //��һ�ֵ���edge[j][1] �ľ�����ԭ����ֵ  ��  ����edge[j][0]��ֵ���ϴ�edge[j][0]��edge[j][1]
            }
        }
        //����޸�ֵ�Ļ�����cur������������
        for(int j=1;j<=n;j++){
            cur[j]=Next[j];
        }
        //��cur����ΪNext����
    }
    if(cur[en]==INT_MAX){
        cur[en]=-1;
    }
    cout<<cur[en]<<endl;
}

signed main()
{
    cin>>n>>m;
    //cur�����¼����ÿ���㵽st�ľ���  ��ʼ��Ϊ������
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
    }
    cin>>k>>q;
    for(int i=1,st,en;i<=q;i++){
        cin>>st>>en;
        bellman(st,en);
    }
    return 0;
}


