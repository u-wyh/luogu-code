// ��������(�ݹ��)
// һ����n���㣬���1~n����n-1��������һ������ÿ������������
// һ����q����ѯ��ÿ�η���a��b��·���ϣ���������ѡ�����֣��ܵõ����������
// 1 <= n <= 2 * 10^4
// 1 <= q <= 2 * 10^5
// 0 <= ���ϵ����� <= 2^60
// �������� : https://www.luogu.com.cn/problem/P3292
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code03_LuckyNumber2�ļ�
#include<bits/stdc++.h>
using namespace std;
// �ڵ��������
const int MAXN = 20002;
// ���ϱ����Ĵη�����
const int LIMIT = 16;
// �ڵ�ֵ����λ��
const int BIT = 60;

// ÿ���ڵ�ֵ������
long arr[MAXN];

// ��ʽǰ����
int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int cnt=1;

// ���ϱ�����Ҫ����ȱ�
int deep[MAXN];
// ���ϱ�����Ҫ�ı�����
int stjump[MAXN][LIMIT];
// ���ϱ�������ʵ�ʽڵ����ȷ���Ĵη�
int power;

// bases[i][j]��ʾ��
// ͷ�ڵ㵽i�ڵ�·���ϵ����֣��������ռ����Ի�������jλ�����Ի����ĸ�����
long bases[MAXN][BIT + 1];
// levels[i][j]��ʾ��
// ͷ�ڵ㵽i�ڵ�·���ϵ����֣��������ռ����Ի�������jλ�����Ի�������һ��
int levels[MAXN][BIT + 1];
long basis[BIT + 1];

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void addEdge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// ������滻���Ի�����������Ҫ�ĺ���
bool insertReplace(long curv, int curl, long* basis, int* level) {
    //Ҫ������е�����curv  ���Ĳ㼶curl
    //����basis  �ȼ���level
    for (int i = BIT; i >= 0; i--) {
        if (curv >> i == 1) {
            //��ʾ���������λ����1
            if (basis[i] == 0) {
                //���ԭ��û������  ��ôֱ�Ӽ��뼴��
                basis[i] = curv;
                level[i] = curl;
                return true;
            }
            if (curl > level[i]) {
                //��������� �����Լ��Ĳ㼶����  ��ôԭ�������ֱ��滻��
                //����ԭ�������ּ���������û���Լ����Բ����λ��
                long tmp1 = curv;
                curv = basis[i];
                basis[i] = tmp1;
                int tmp2 = level[i];
                level[i] = curl;
                curl = tmp2;
            }
            curv ^= basis[i];
        }
    }
    return false;
}

int lca(int x, int y) {
    //�ҵ�xy��LCA
	if (deep[x] < deep[y]) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	for (int p = power; p >= 0; p--) {
		if (deep[stjump[x][p]] >= deep[y]) {
			x = stjump[x][p];
		}
	}
	if (x == y) {
		return x;
	}
	for (int p = power; p >= 0; p--) {
		if (stjump[x][p] != stjump[y][p]) {
			x = stjump[x][p];
			y = stjump[y][p];
		}
	}
	return stjump[x][0];
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int i = 0; i <= BIT; i++) {
        //���ȼ̳����Ը��׽ڵ������
        bases[u][i] = bases[f][i];
        levels[u][i] = levels[f][i];
    }
    insertReplace(arr[u], deep[u], bases[u], levels[u]);
    //���Լ�λ���ϵ����ּ������ű���
    for (int e = head[u]; e != 0; e = Next[e]) {
        //���ӽڵ����
        if (to[e] != f) {
            dfs(to[e], u);
        }
    }
}

long query(int x, int y) {
    int Lca = lca(x, y);
    long basisx[BIT+1];
    long levelx[BIT+1];
    //��ɴ�x��y��·���ϵ����Ի�
    for(int i=0;i<=BIT;i++){
        basisx[i]=bases[x][i];
        levelx[i]=levels[x][i];
    }
    long basisy[BIT+1];
    long levely[BIT+1];
    for(int i=0;i<=BIT;i++){
        basisy[i]=bases[y][i];
        levely[i]=levels[y][i];
    }
    for(int i=0;i<=BIT;i++){
        basis[i]=0;
    }
    for (int i = BIT; i >= 0; i--) {
        long num = basisx[i];
        if (levelx[i] >= deep[Lca] && num != 0) {
            basis[i] = num;
        }
        //���Ƚ����Ϊx�ı�  ȥ���ȼ�����lca������
    }
    for (int i = BIT; i >= 0; i--) {
        long num = basisy[i];
        if (levely[i] >= deep[Lca] && num != 0) {
            //��y�ı���뵽����������Ч��
            for (int j = i; j >= 0; j--) {
                if (num >> j == 1) {
                    if (basis[j] == 0) {
                        basis[j] = num;
                        break;
                    }
                    num ^= basis[j];
                }
            }
        }
    }
    //��ѯ���ֵ
    long ans = 0;
    for (int i = BIT; i >= 0; i--) {
        ans = max(ans, ans ^ basis[i]);
    }
    return ans;
}

int main()
{
    int n ;
    int q ;
    cin>>n>>q;
    power=log2(n);
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin>>u>>v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    for (int i = 1, x, y; i <= q; i++) {
        cin>>x>>y;
        cout<<query(x, y)<<endl;
    }
    return 0;
}
