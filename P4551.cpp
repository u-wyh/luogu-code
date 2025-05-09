#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int nums[MAXN];
int cnt=1;
int tree[3000005][2];
int tot=1;

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void insert(int num) {
    int cur = 1;
    for (int i = 30, path; i >= 0; i--) {
        path = (num >> i) & 1;
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++tot;
        }
        cur = tree[cur][path];
    }
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            nums[v]=nums[f]^w;
            insert(nums[v]);
            //cout<<v<<' '<<num<<endl;
            dfs(v,u);
        }
    }
}

int maxXor(int num) {
    // �������Ľ��(������)
    int ans = 0;
    // ǰ׺��Ŀǰ�����Ľڵ���
    int cur = 1;
    for (int i = 30, status, want; i >= 0; i--) {
        // status : num��iλ��״̬
        status = (num >> i) & 1;
        // want : num��iλϣ��������״̬
        want = status ^ 1;
        if (tree[cur][want] == 0) { // ѯ��ǰ׺�����ܲ��ܴ��
            // ���ܴ��
            want ^= 1;
        }
        // want�����������ߵ�·
        ans |= (status ^ want) << i;
        cur = tree[cur][want];
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    //getchar();
    insert(0);
    nums[1]=0;
    dfs(1,0);
    int ans=0;
    for(int i=1;i<n;i++){
        ans=max(ans,maxXor(nums[i]));
    }
    printf("%d\n",ans);
    return 0;
}
