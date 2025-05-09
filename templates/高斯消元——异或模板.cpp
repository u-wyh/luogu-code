// ȫ���1�����ٲ�������
// һ����n���㣬m������ߣ�ÿ����ĳ�ʼ״̬����0
// ���Բ�������һ���㣬������õ��Լ����ڵ��״̬����ı�
// ������ϣ�����е㶼���1״̬����ô���ܻ����ɷ�������������
// ��ô���д�����Ҫ���ٲ��������ķ�������ӡ������ٲ�������
// ��Ŀ��֤һ�����������е㶼���1״̬������û���رߺ��Ի�
// 1 <= n <= 35
// 1 <= m <= 595
// �������� : https://www.luogu.com.cn/problem/P2962
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 37;

int mat[MAXN][MAXN];
int op[MAXN];
int n,m,ans;

void prepare() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mat[i][j] = 0;
        }
        mat[i][i] = 1;
        mat[i][n + 1] = 1;
        op[i] = 0;
    }
}

// ��˹��Ԫ�����򷽳���ģ��
// ��Ҫ��֤������n�������ʽҲ��n��
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i && mat[j][j] == 1) {
                continue;
            }
            if (mat[j][i] == 1) {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] == 1) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] == 1) {
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

void dfs(int i, int num) {
    if (num >= ans) { // ��֦
        return;
    }
    if (i == 0) {
        ans = num;
    } else {
        if (mat[i][i] == 0) {
            // ��ǰ������Ԫ
            // ����Ԫһ����������Ԫ
            // ����ԪҲһ����������������Ԫ
            // ���Ե�ǰ����Ԫһ���������о���Ҫ��Ҫ����
            op[i] = 0;
            dfs(i - 1, num);
            op[i] = 1;
            dfs(i - 1, num + 1);
        } else {
            // ��ǰ����Ԫ
            // ��Ԫ���ܱ���������ԪӰ��
            // ����һ���У���ǰ��Ԫ�ı�� < Ӱ����������Ԫ���
            // ���Ի�Ӱ�쵱ǰ��Ԫ������Ԫ�ǣ�һ���Ѿ�ȷ����Ҫ��Ҫ����
            // ��ô��ǰ��ԪҪ��Ҫ������Ҳ��ȷ����
            //ȷ���������Ԫ֮��  ��ʹǰ�����ɴ�������Ԫ   ���Ǿ�����Ӱ�������Ԫ��ѡ��
            //�ܹ�Ӱ�쵱ǰ��Ԫ��һ���Ѿ���������
            int cur = mat[i][n + 1];
            for (int j = i + 1; j <= n; j++) {
                if (mat[i][j] == 1) {
                    cur ^= op[j];
                }
            }
            dfs(i - 1, num + cur);
        }
    }
}

int main()
{
    cin>>n>>m;
    prepare();
    for (int i = 1, u, v; i <= m; i++) {
        cin>>u>>v;
        mat[u][v] = 1;
        mat[v][u] = 1;
    }
    gauss(n);
    int sign = 1;
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] == 0) {
            sign = 0;//��ʾ��������Ԫ
            break;
        }
    }
    if (sign == 1) {
        // Ψһ��  ˵��û������Ԫ
        // ��ô��Ҫ�����ľ�ֻ��ֵΪ1�ĵ�
        ans = 0;
        for (int i = 1; i <= n; i++) {
            if (mat[i][n + 1] == 1) {
                ans++;
            }
        }
    } else {
        // ���
        ans = n;//���ֻ��n��
        dfs(n, 0);
    }
    cout<<ans<<endl;
    return 0;
}
