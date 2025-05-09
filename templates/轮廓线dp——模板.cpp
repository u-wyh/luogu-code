// �ֲݵķ�����(������dp)
// ����һ��n*m�Ķ�ά����grid
// ������ֻ��0��1����ֵ��0��ʾ����ز����ֲݣ�1��ʾ����ؿ����ֲ�
// �ֲݵ�ʱ���κ��������˲ݵ���ز������ڣ����ڰ����ϡ��¡������ĸ�����
// �������������ֶ��ٲݣ�ֻҪ���ƻ�����Ĺ��򼴿�
// �����ֲݵķ��������𰸶�100000000ȡģ
// 1 <= n, m <= 12
// �������� : https://www.luogu.com.cn/problem/P1879
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 12;
const int MAXM = 12;
const int MOD = 100000000;
const int MAXS = 1 << MAXM;

int grid[MAXN][MAXM];
int dp[MAXN][MAXM][MAXS];
int n, m;

// ������������ȡ״̬s�е�jλ��״̬
int get(int s, int j) {
    return (s >> j) & 1;
}

// ��������������״̬s�е�jλ��״̬Ϊv���������µ�״̬
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

// ��ǰ����i��j��
// i-1���У�[j..m-1]�е��ֲ�״����s[j..m-1]��ʾ
// i���У�[0..j-1]�е��ֲ�״����s[0..j-1]��ʾ
// s��ʾ�����ߵ�״��
// ���غ����м����ֲݷ���
int f(int i, int j, int s) {
	if (i == n) {
        //��ʾ�Ѿ�������
		return 1;
	}
	if (j == m) {
	    //��ʾ����
		return f(i + 1, 0, s);
	}
	if (dp[i][j][s] != -1) {
		return dp[i][j][s];
	}
	int ans = f(i, j + 1, set(s, j, 0));//���λ��ѡ��0�����ұ���Ҫ����һ��  ���������һ�е��������
	if (grid[i][j] == 1 && (j == 0 || get(s, j - 1) == 0) && get(s, j) == 0) {
        //������  ���λ���ϱ�����1  ������ǰ�����λ������0  �Լ����λ�����Ҳ��0����Ϊ����Ѿ�����ˣ�
		ans = (ans + f(i, j + 1, set(s, j, 1))) % MOD;//��ʾ���λ��ѡ��1
	}
	dp[i][j][s] = ans;
	return ans;
}

int main()
{
    cin>>n>>m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 0; s < (1<<m); s++) {
                dp[i][j][s] = -1;
            }
        }
    }
    cout<<f(0, 0, 0);//��ʾ�������ʼ��λ��  �Ѿ���õ�״̬��0
    return 0;
}
