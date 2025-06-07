#include<bits/stdc++.h>
using namespace std;
const int MAXN = 510005;

int n;
int ans=0;
int cnt=1;
int tree[MAXN][26];
bool tag[MAXN];
int last[MAXN];
vector<int>edge[MAXN];
int sz[MAXN];

void insert(string s){
    int cur=1;
    for(char ch:s){
        int path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    tag[cur]=true;
}

bool cmp(int x,int y){
    return sz[x]<sz[y];
}

void rebuild(int u){
    if(tag[u]&&u!=1){
		edge[last[u]].push_back(u);
		last[u]=u;
	}
	for(int i=0;i<26;i++) {
        if(tree[u][i]){
            last[tree[u][i]]=last[u];
            rebuild(tree[u][i]);
        }
    }
}

void dfs(int u){
    sz[u]=1;
    for(int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        dfs(v);
        sz[u]+=sz[v];
    }
    sort(edge[u].begin(),edge[u].end(),cmp);
}

void compute(int u){
    int dfn=cnt++;
    for(int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        ans+=cnt-dfn;
        compute(v);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        reverse(str.begin(), str.end());
        insert(str);
    }
    last[1]=1;
    tag[1]=1;
    dfs(1);
    cnt=1;
    compute(1);
    cout<<ans<<endl;
    return 0;
}