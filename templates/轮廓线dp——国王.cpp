// �ڷŹ����ķ�����(������dp)
// ������������n��k����ʾn*n��������Ҫ�ڷ�k������
// �������Թ����ٽ���8���������԰ڷ�ʱ�������κ������������
// ���ذڷŵķ�����
// 1 <= n <= 9
// 1 <= k <= n*n
// �������� : https://www.luogu.com.cn/problem/P1896
// �ύ���µ�code���ύʱ��������ĳ�"Main"���п���ȫ��ͨ��
// �������Ƽ�д���ռ�ѹ���İ汾
#include<iostream>
using namespace std;

int n,kings;
int dp[9][9][1<<9][2][82];

int get(int s, int j) {
	return (s >> j) & 1;
}

int set(int s, int j, int v) {
	return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

// ��ǰ����i��j��
// i-1���У�[j..m-1]����û�аڷŹ�������s[j..m-1]�Ÿ��ӱ�ʾ
// i���У�[0..j-1]����û�аڷŹ�������s[0..j-1]�Ÿ��ӱ�ʾ
// s��ʾ�����ߵ�״��
// (i-1, j-1)λ�ã�Ҳ�������Ͻǣ���û�аڷŹ�������leftup��ʾ
// ������ʣ��k����Ҫȥ�ڷ�
// �����ж����ְڷŷ���
long f(int i, int j, int s, int leftup, int k) {
	if (i == n) {
		return k == 0 ? 1 : 0;
	}
	if (j == n) {
		return f(i + 1, 0, s, 0, k);
	}
	if (dp[i][j][s][leftup][k] != -1) {
		return dp[i][j][s][leftup][k];
	}
	int left = j == 0 ? 0 : get(s, j - 1);
	int up = get(s, j);
	int rightup = get(s, j + 1);
	long ans = f(i, j + 1, set(s, j, 0), up, k);
	if (k > 0 && left == 0 && leftup == 0 && up == 0 && rightup == 0) {
		ans += f(i, j + 1, set(s, j, 1), up, k - 1);
	}
	dp[i][j][s][leftup][k] = ans;
	return ans;
}

int main()
{
    cin>>n>>kings;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int s = 0; s < (1<<n); s++) {
                for (int leftup = 0; leftup <= 1; leftup++) {
                    for (int k = 0; k <= kings; k++) {
                        dp[i][j][s][leftup][k] = -1;//ȫ����ʼ��
                    }
                }
            }
        }
    }
    cout<<f(0, 0, 0, 0, kings);
    return 0;
}
