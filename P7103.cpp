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
        fa[to[i]] = x; //������������  ��ô�������Ҫ�͵�ǰ�ڵ�ϲ� ���Ҵ���ڵ����óɵ�ǰ�ڵ�  
        //tarjan�ľ������
    }
    ans[d[x]] = ans[d[x]] ? find(ans[d[x]]) : x; 
	//ans[d[x]]��ʾ��x�ڵ�֮ǰ����Ⱥ�d[x]һ���Ľڵ��lca  �����0  �ͱ�ʾ��ǰû����������ͬ��ȵ�  ��ô���ó��Լ�
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