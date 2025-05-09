// ·���������(�ݹ��)
// һ����n���㣬���1~n����m�����������
// ÿ������Ȩֵ�����뱣֤ͼ����ͨ�ģ������л�
// �ҵ�1��n��һ��·����·�������ظ�����ĳЩ����
// ��һ������·���г����˶��ʱ������ʱ��ҲҪ����
// ϣ���ҵ�һ����1��n��·�������б�Ȩ���;����󣬷�������������
// 1 <= n <= 50000
// 1 <= m <= 100000
// 0 <= ��Ȩ <= 10^18
// �������� : https://www.luogu.com.cn/problem/P4151
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code04_MaximumXorOfPath2�ļ�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int MAXM = 200002;
const int BIT = 60;

// ��ʽǰ����
int head[MAXN];
int Next[MAXM];
int to[MAXM];
long weight[MAXM];
int cnt=1;

// ���л������͹��������Ի�
long basis[BIT + 1];
// ĳ���ڵ���dfs�������Ƿ񱻷��ʹ�
bool visited[MAXN];
// ��ͷ��㵽��ǰ�ڵ������
long path[MAXN];

void addEdge(int u, int v, long w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool insert(long num) {
    for (int i = BIT; i >= 0; i--)
        if (num >> i == 1) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    return false;
}

void dfs(int u, int f, long p) {
	path[u] = p;
	visited[u] = true;
	for (int e = head[u]; e != 0; e = Next[e]) {
		int v = to[e];
		if (v != f) {
			long eor = p ^ weight[e];
			if (visited[v]) {
                //�������ʹ���  ˵�������һ����
				insert(eor ^ path[v]);
			} else {
				dfs(v, u, eor);
			}
		}
	}
}

long query(long init) {
    for (int i = BIT; i >= 0; i--) {
        init = max(init, init ^ basis[i]);
    }
    return init;
}

int main()
{
    int n ;
    int m ;
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        int u ;
        int v ;
        long w ;
        cin>>u>>v>>w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs(1, 0, 0);
    cout<<query(path[n])<<endl;
    return 0;
}
