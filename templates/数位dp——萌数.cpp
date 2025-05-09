// ����
// ���һ�����֣����ڳ�������Ϊ2�Ļ����Ӵ�����ô�������ֱ���Ϊ����
// ����101��110��111��1234321��45568
// ��[l,r]��Χ�ϣ��ж��ٸ�����
// ���ڴ𰸿��ܴܺ���������𰸶�1000000007����
// �������� : https://www.luogu.com.cn/problem/P3413
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

char l[1005],r[1005];
int dp[1005][11][11][2];

// ��num�ĸ�λ��ʼ����ǰ������iλ
// ǰһλ������p��ǰǰһλ������pp�����ֵ��10�����ʾ��һλû��ѡ�������
// ���֮ǰ��λ�Ѿ�ȷ����numС����ôfree == 1����ʾ���µ����ֿ�������ѡ��
// ���֮ǰ��λ��numһ������ôfree == 0����ʾ���µ����ֲ��ܴ���num��ǰλ������
// ����<=num�Ҳ��������������ж��ٸ�
int f(char* num, int i, int pp, int p, int free) {
	if (i == strlen(num)) {
		return 1;
	}
	if (dp[i][pp][p][free] != -1) {
		return dp[i][pp][p][free];
	}
	int ans = 0;
	if (free == 0) {
		if (p == 10) {
			// ��ǰ�����ľ���num�����λ
			ans = (ans + f(num, i + 1, 10, 10, 1)) % MOD; // ��ǰλ��ѡ����
			for (int cur = 1; cur < num[i] - '0'; cur++) {
				ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
				//��ʾʣ�µ�λ���ϵ����ֿ������ѡ��
			}
			ans = (ans + f(num, i + 1, p, num[i] - '0', 0)) % MOD;
			//��ʾʣ�µ�λ���ϵ����ֲ��������ѡ��
		} else {
			// free == 0��֮ǰ��numһ������ʱ��������ѡ������
			// ǰһλp��ѡ������֣�p -> 0 ~ 9
			for (int cur = 0; cur < num[i] - '0'; cur++) {
				if (pp != cur && p != cur) {
					ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
				}
			}
			if (pp != num[i] - '0' && p != num[i] - '0') {
				ans = (ans + f(num, i + 1, p, num[i] - '0', 0)) % MOD;
			}
		}
	} else {
		if (p == 10) {
			// free == 1��������ѡ������
			// ����ûѡ������
			ans = (ans + f(num, i + 1, 10, 10, 1)) % MOD; // ��Ȼ��ѡ����
			for (int cur = 1; cur <= 9; cur++) {
				ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
			}
		} else {
			// free == 1��������ѡ������
			// ֮ǰѡ�������
			for (int cur = 0; cur <= 9; cur++) {
				if (pp != cur && p != cur) {
					ans = (ans + f(num, i + 1, p, cur, 1)) % MOD;
				}
			}
		}
	}
	dp[i][pp][p][free] = ans;
	return ans;
}

bool check(char* num) {//����
	for (int pp = -2, p = -1, i = 0; i < strlen(num); pp++, p++, i++) {
		if (pp >= 0 && num[pp] == num[i]) {
			return true;
		}
		if (p >= 0 && num[p] == num[i]) {
			return true;
		}
	}
	return false;
}

void build(int n) {
    for (int a = 0; a < n; a++) {
        for (int b = 0; b <= 10; b++) {
            for (int c = 0; c <= 10; c++) {
                for (int d = 0; d <= 1; d++) {
                    dp[a][b][c][d] = -1;
                }
            }
        }
    }
}

// ����0~num��Χ�������ж��ٸ�
int cnt(char* num) {
	if (num[0] == '0') {
		return 0;
	}
	int n = strlen(num);
	long all = 0;
	long base = 1;
	for (int i = n - 1; i >= 0; i--) {
		// �����Ļ���һ�£�����041-ͬ��ԭ��
		all = (all + base * (num[i] - '0')) % MOD;
		base = (base * 10) % MOD;
	}
	build(n);
	return (int) ((all - f(num, 0, 10, 10, 0) + MOD) % MOD);
}

int main()
{
    cin>>l>>r;
    int ans = (cnt(r) - cnt(l) + MOD) % MOD;
    if (check(l)) {
        ans = (ans + 1) % MOD;
    }
    cout<<ans;
    return 0;
}
