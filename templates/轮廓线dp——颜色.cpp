// ���ڲ�ͬɫ��Ⱦɫ������(������dp)
// ������������n��m����ʾn��m�еĿհ�����һ��ʼ���и��Ӷ�û����ɫ
// ��������k����ʾ��k����ɫ����ɫ���0~k-1
// ����Ҫ��ÿ������Ⱦɫ���������ڵĸ�����ɫ������ͬ
// ���ڰ����ϡ��¡������ĸ�����
// ���Ҹ����˵�0�к͵�n-1�е���ɫ״�������뱣֤һ����Ч
// ��ô��ֻ����1~n-2����Ⱦɫ������Ⱦɫ�ķ��������𰸶�376544743ȡģ
// 2 <= k <= 4
// k = 2ʱ��1 <= n <= 10^7��1 <= m <= 10^5
// 3 <= k <= 4ʱ��1 <= n <= 100��1 <= m <= 8
// �������� : https://www.luogu.com.cn/problem/P2435
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// �ռ�᲻��꣬���߲����޷�ȫ��ͨ�������߼���ȷ
// �����������п��ܵ�������������ȷ��
#include<iostream>
using namespace std;
const int MOD = 376544743;

int n,m,k;
int start[10],en[10];
int dp[101][8][1<<16];
int startStatus, endStatus;

// ����ɫ״��s�ȡ��j�Ÿ����ɫ
int get(int s, int j) {
	return (s >> (j << 1)) & 3;
}

// ��ɫ״��s�У���j�Ÿ����ɫ���ó�v��Ȼ����µ�s����
int set(int s, int j, int v) {
	return s & (~(3 << (j << 1))) | (v << (j << 1));
}

int special() {
    if ((n & 1) == 0) {
        for (int i = 0; i < m; i++) {
            if (start[i] == en[i]) {
                return 0;
            }
        }
    } else {
        for (int i = 0; i < m; i++) {
            if (start[i] != en[i]) {
                return 0;
            }
        }
    }
    return 1;
}

// ��ɫ״��a����ɫ״��b���Ƿ�ÿһ�񶼲�ͬ
bool different(int a, int b) {
    for (int j = 0; j < m; j++) {
		if (get(a, j) == get(b, j)) {
			return false;
		}
	}
	return true;
}

// ��ǰ����i��j��
// i-1���У�[j..m-1]�е���ɫ״������s[j..m-1]�Ÿ��ӱ�ʾ
// i���У�[0..j-1]�е���ɫ״������s[0..j-1]�Ÿ��ӱ�ʾ
// s��ʾ�����ߵ�״��
// �����м���Ⱦɫ����
int f(int i, int j, int s) {
	if (i == n - 1) {
        //��Ϊ���һ���Ѿ����ù��� ��ôn-1�������һ��
        //�жϺ�n���Ƿ��ͻ
		return different(s, endStatus) ? 1 : 0;
	}
	if (j == m) {
		return f(i + 1, 0, s);
	}
	if (dp[i][j][s] != -1) {
		return dp[i][j][s];
	}
	int ans = 0;
	for (int color = 0; color < k; color++) {
		if ((j == 0 || get(s, j - 1) != color) && get(s, j) != color) {
			ans = (ans + f(i, j + 1, set(s, j, color))) % MOD;
		}
	}
	dp[i][j][s] = ans;
	return ans;
}

int compute() {
    startStatus = endStatus = 0;
    for (int j = 0; j < m; j++) {
        startStatus = set(startStatus, j, start[j]);
        endStatus = set(endStatus, j, en[j]);
        //���úõ�һ�к����һ�е�״̬
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 0; s < (1<<(m*2)); s++) {
                dp[i][j][s] = -1;
                //ȫ����ʼ��
            }
        }
    }
    return f(1, 0, startStatus);
}

int main()
{
    cin>>n>>m>>k;
    for(int i=0;i<m;i++){
        cin>>start[i];
    }
    for(int i=0;i<m;i++){
        cin>>en[i];
    }
    if (k == 2) {
        cout<<special();
    } else {
        cout<<compute();
    }
    return 0;
}
