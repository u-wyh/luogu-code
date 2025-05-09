//P2746
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

vector<int>vec[MAXN];
//dfn��ʾ�ľ���dfn��  ��low�����ʾ��������ڵ����ű߿����ߵ�����С��dfn��
//dfnһ��ȷ���� �Ͳ���ı���  ��low������ܻᷢ���仯
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int in[MAXN],out[MAXN];
bool instack[MAXN];
int n,m;

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if(!dfn[v]){
            //��ʾ����ڵ�û�б����ʹ�
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //��ʾ��������ǻ����� һ����ͬһ�����ϵ�
            //����֮���Բ���low[v]  ����Ϊ����ĺ������dfn���  ��ʵ����ĳ�lowҲ��Ӱ��
            //�����������д������ ��Ϊ������Ҫ����ܻᵼ��д��low����
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //�����нڵ㰴����ɫ����  �������
        while(st[top]!=x){
            //����ͬһ��ǿ��ͨ����
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        while(v!=0){
            vec[i].push_back(v);
            cin>>v;
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    //cout<<color<<endl;
    for(int i=1;i<=n;i++){
        for(int j=0;j<vec[i].size();j++){
            int v=vec[i][j];
            if(col[i]!=col[v]){
                in[col[v]]++;
                out[col[i]]++;
            }
        }
    }
    int ans1=0,ans2=0;
    for(int i=1;i<=color;i++){
        if(!in[i])
            ans1++;
        if(!out[i])
            ans2++;
    }
    cout<<ans1<<endl;
    if(color==1){
        cout<<0<<endl;
    }
    else{
        cout<<max(ans1,ans2)<<endl;
    }
    return 0;
}
