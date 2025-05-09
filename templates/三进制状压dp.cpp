// ��������Ҹ���
// �����ĸ�����m��n��in��ex����ʾm*n�������Լ�in��������ˣ�ex���������
// ��������������Ӧ����ס�����ˣ���Ϊÿ���˷���һ������Ԫ�������������˶�������������
// ÿ���˵��Ҹ��м������£�
// ������˿�ʼʱ��120�Ҹ��У���ÿ����һ���ھӣ�������ʧȥ30�Ҹ���
// ������˿�ʼʱ��40�Ҹ��У���ÿ����һ���ھӣ�������õ�20�Ҹ���
// �ھ�ֻ�����ϡ��¡������ĸ�����
// �����Ҹ�����ÿ�����Ҹ��е��ܺͣ����������ܵ������Ҹ���
// 1 <= m��n <= 5
// 1 <= in��ex <= 6
// �������� : https://leetcode.cn/problems/maximize-grid-happiness/
// ����Ȥ��ͬѧ�����Լ���һ�¿ռ�ѹ���İ汾
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN = 5;
const int MAXM = 5;
const int MAXP = 7;
const int MAXS = (int)pow(3, MAXM);

int n,m,in,ex;//�����к���  ������˺������������
int dp[MAXN][MAXM][MAXS][MAXP][MAXP];

// s��ʾ��ǰ״̬������3���������
// ��ǰ������j�Ÿ�3��j�η���bit
// ����s��j�Ÿ��ֵ
int get(int s, int bit) {
	return (s / bit) % 3;
}

// s��ʾ��ǰ״̬������3���������
// ��ǰ������j�Ÿ�3��j�η���bit
// ��s��j�Ÿ��ֵ���ó�v��������״̬
int set(int s, int bit, int v) {
	return s - get(s, bit) * bit + v * bit;
}

// ��ǰ����i��j�еĸ���
// s��ʾ�����ߵ�״̬�����Եõ������ӷ���ʲô�ˣ��ϲ���ӷ���ʲô��
// ������˻���a����������˻���b��
// ���������Ҹ���
// ע�� : bit����3��j�η���bit���ǹؼ��ɱ��������Ϊbit��ֵ��j��ֵ����  ֻ��Ϊ�˷�������ȡֵs
int f(int i, int j, int s, int a, int b, int bit) {
	if (i == n) {
		return 0;
	}
	if (j == m) {
		return f(i + 1, 0, s, a, b, 1);
	}
	if (dp[i][j][s][a][b] != -1) {
		return dp[i][j][s][a][b];
	}
	// ��ǰ���Ӳ�������
	int ans = f(i, j + 1, set(s, bit, 0), a, b, bit * 3);
	// �Ϸ��ھӵ�״̬
	int up = get(s, bit);
	// ���ھӵ�״̬
	int left = j == 0 ? 0 : get(s, bit / 3);
	// �ھ�����
	int neighbor = 0;
	// ��������ˣ�֮ǰ�õ����Ҹ���Ҫ��α仯
	int pre = 0;
	if (up != 0) {
		neighbor++;
		// ���ھ���������ˣ��Ҹ���Ҫ��30����������ˣ��Ҹ���Ҫ��20
		pre += up == 1 ? -30 : 20;
	}
	if (left != 0) {
		neighbor++;
		// ���ھ���������ˣ��Ҹ���Ҫ��30����������ˣ��Ҹ���Ҫ��20
		pre += left == 1 ? -30 : 20;
	}
	if (a > 0) {
		// ��ǰ���Ӿ������������
		ans = max(ans, pre + 120 - neighbor * 30 + f(i, j + 1, set(s, bit, 1), a - 1, b, bit * 3));
	}
	if (b > 0) {
		// ��ǰ���Ӿ������������
		ans = max(ans, pre + 40 + neighbor * 20 + f(i, j + 1, set(s, bit, 2), a, b - 1, bit * 3));
	}
	dp[i][j][s][a][b] = ans;
	return ans;
}

int main()
{
    cin>>n>>m>>in>>ex;
    int maxs=pow(3,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 0; s < maxs; s++) {
                for (int a = 0; a <= in; a++) {
                    for (int b = 0; b <= ex; b++) {
                        dp[i][j][s][a][b] = -1;
                    }
                }
            }
        }
    }
    cout<<f(0, 0, 0, in, ex, 1)<<endl;
    return 0;
}
