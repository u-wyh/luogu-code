//P5829
//ʧ�����Ǹ���kmp�㷨��ɵ��������ݽṹ
//�������ȸ���kmp�㷨����nxt����  Ȼ�����nxt�����ֵ���� nxt[i]->i
//�������ǿ��Եõ�һ���������ݽṹ  ��������� ÿ���ڵ�����Ƚڵ��������ǰ׺ Ҳ�����ĺ�׺
//���Ķ�������0
//���ҽڵ���Ҳ������ַ����ĳ��� ��Ϊ����ַ����Ǵ�ͷ��������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int LIMIT = 20;

char s1[MAXN];
char s2[MAXN];
int Next[MAXN];
int n,m;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;
int power;
int deep[MAXN],stjump[MAXN][LIMIT];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

// ����next����
void nextArray(const char *s, int m) {
    if (m == 1) {
        Next[0] = -1;
        return ;
    }

    Next[0] = -1;
    Next[1] = 0;

    int i = 2, cn = 0;
    // i��ʾ��ǰҪ��nextֵ��λ��
    // cn��ʾ��ǰҪ��ǰһ���ַ��ȶԵ��±�
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            Next[i++] = ++cn;
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i++] = 0;
        }
    }
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = nxt[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
        }
        //���µݹ�
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return stjump[a][0];
        //�����ͬ˵���������ȹ�ϵ
        //��ô��Ҫ������һ��  ��ΪҪ�����border
        //ʵ����Ҳ������stjump[u][0],stjump[v][0]��lca  ����������  ֱ�Ӿ���lca
    }
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    return stjump[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}

int main()
{
    scanf("%s",s1+1);//��1��ʼ���������
    n=strlen(s1+1);
    nextArray(s1+1,n+1);
    power=log2(n+1);
//    for(int i=0;i<=n;i++){
//        cout<<Next[i]<<' ';
//    }
    for(int i=1;i<=n;i++){
        addedge(Next[i],i);
        //cout<<Next[i]<<' '<<i<<endl;
    }
    dfs(0,0);
    m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        cout<<lca(u,v)<<endl;
    }
    return 0;
}
/*
abbabaabbabb
*/
