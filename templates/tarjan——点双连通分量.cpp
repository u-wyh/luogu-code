//P8435
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 2e6+5;

// ��ʽǰ���Ǵ�ͼ
int head[MAXN];     // head[u] ��ʾ�ڵ�u�ĵ�һ���ߵı��
int Next[MAXM<<1];  // Next[i] ��ʾ��i���ߵ���һ����
int to[MAXM<<1];    // to[i] ��ʾ��i����ָ��Ľڵ�
int cnt=1;          // �ߵļ���������1��ʼ�����㴦����ߣ�

// Tarjan�㷨��ر���
int dfn[MAXN];      // dfn[u] ��ʾ�ڵ�u��DFS��ʱ�����
int low[MAXN];      // low[u] ��ʾu����������׷�ݵ����������ȵ�dfn
int st[MAXN], top;  // ջ�����ڴ洢��ǰDFS·���ϵĽڵ�
int color, Time;    // color��¼��˫��������Time��ʱ���������
int n, m;           // �ڵ����ͱ���
vector<int> ans[MAXN]; // �洢ÿ����˫�Ľڵ�

// ���ٶ��뺯���������ڴ���������
inline int read(){
    int x=0, f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0', ch=getchar();
    return x*f;
}

// ��ӱߣ�����ͼ��
void addedge(int u, int v){
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// Tarjan�㷨���˫��ͨ����
void tarjan(int u, int f){
    dfn[u] = low[u] = ++Time; // ��ʼ��dfn��low
    st[++top] = u;            // �ڵ�u��ջ
    int child = 0;            // ��¼u��DFS���е��ӽڵ�����

    // ����u�������ڽӽڵ�
    for(int i = head[u]; i; i=Next[i]){
        int v = to[i];
        if(!dfn[v]){          // ���vδ������
            child++;
            tarjan(v, u);     // �ݹ����v
            low[u] = min(low[u], low[v]); // ����low[u]

            // ���low[v] >= dfn[u]��˵��u�Ǹ�㣬��ʼ������˫
            if(low[v] >= dfn[u]){
                color++;      // �µĵ�˫���
                // ����ջ�нڵ㣬ֱ��v������������v��
                while(st[top+1] != v){ // ע�⣺st[top+1]���ڱ�
                    //���� v������ʽ���� u
                    ans[color].push_back(st[top--]);
                }
                ans[color].push_back(u); // ���u���ڵ�ǰ��˫
            }
        }
        else if(v != f){      // ���v�ѱ������Ҳ��Ǹ��ڵ㣨����رߣ�
            low[u] = min(low[u], dfn[v]);
        }
    }

    // ���У�u�ǹ����㣨DFS���ĸ���û���ӽڵ㣩
    if(f == 0 && child == 0){
        ans[++color].push_back(u);
    }
}

int main(){
    n = read(), m = read();
    // ����߲���ͼ
    for(int i=1; i<=m; i++){
        int u = read(), v = read();
        addedge(u, v);
        addedge(v, u); // ����ͼ����˫���
    }

    // ������δ���ʵĽڵ�����Tarjan
    for(int i=1; i<=n; i++){
        if(!dfn[i]){
            tarjan(i, 0); // 0��ʾû�и��ڵ㣨���ڵ㣩
        }
    }

    // �����˫������ÿ����˫�Ľڵ�
    cout << color << endl;
    for(int i=1; i<=color; i++){
        cout << ans[i].size() << ' ';
        for(int j=0; j<ans[i].size(); j++){
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}