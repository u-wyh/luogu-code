#include<bits/stdc++.h>
#define R register int
using namespace std;
const int N = 5e6 + 5;

int n, d[N], to[N], nx[N], h[N], fa[N], q, in, ans[N];

inline int read(){
    int s = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) s = (s << 3) + (s << 1) + (c ^ 48), c = getchar();
    return s;
}

int find(int p){
    return fa[p] == p ? p : fa[p] = find(fa[p]);
}

void dfs(int x, int f){
    d[x] = d[f] + 1;
    for(R i = h[x]; i; i = nx[i]) {
        dfs(to[i], x);
        fa[to[i]] = x; //遍历完子树后  那么这颗子树要和当前节点合并 并且代表节点设置成当前节点  
        //tarjan的经典操作
    }
    ans[d[x]] = ans[d[x]] ? find(ans[d[x]]) : x; 
	//ans[d[x]]表示在x节点之前的深度和d[x]一样的节点的lca  如果是0  就表示以前没有遇到过相同深度的  那么设置成自己
}

int main()
{
    n = read();
    q = read();
    for(R i = 1; i <= n; i++) {
        fa[i] = i;
        in = read();
        to[i] = i;
        nx[i] = h[in];
        h[in] = i; // Input + edge addition + Union-Find init
    }
    
    dfs(1, 0);
    
    while(q--) {
        printf("%d\n", ans[read()]); // O(1) answer queries
    }
    
    return 0;
}