#include <iostream>
#include <cstdio>
using namespace std;

const int N = 27;

int n, m, ans(N * N), s;
int e[N], cnt1[(1 << (N / 2)) + 10];

int Count1(int x) {
	return cnt1[x >> (N/2)] + cnt1[x - ((x >> N/2) << N/2)];
}

void dfs(int pos, int k, int sum, int s1, int s2) {
    //k�ǵ�һ�������еĵ�ĸ���
    //sum��������Ҫ��Ĵ𰸼��ж��ٸ�����λ���������ϵ��߶�
    //s1 s2�ֱ��ʾ�������ϵĶ˵����
    //pos��ʾ���ڵ��˵ڼ�����  �����Ƿ�Ҫ�����ŵ���s1��
	if(k == n / 2) {
		if(sum < ans)
            s = s1, ans = sum;
		return ;
	}
	for(int i=pos+1, ns2; i<=n; i++) {
		ns2 = s2 ^ (1 << i-1);
		dfs(i, k+1, sum - Count1(e[i] & s1) + Count1(e[i] & ns2), s1 | (1 << i-1), ns2);
		// sum - Count1(e[i] & s1) + Count1(e[i] & ns2):ÿ��ѡһ����i����S1ʱ����ȥԭS1��i���ı���������i����S2���ı���.
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i=0; i<1<<(N/2); i++)
		cnt1[i] = cnt1[i>>1] + (i & 1);
    //Ԥ�����ÿһ�����ֵĶ������м���1
	for(int i=1, u, v; i<=m; i++) {
		scanf("%d%d", &u, &v);
		e[u] |= (1 << v-1);
		e[v] |= (1 << u-1);
		//�Զ����Ƶķ�ʽ���������ıߵ���Ϣ
	}
	dfs(0, 0, 0, 0, (1<<n)-1);

	for(int i=1; i<=n; i++)
		if(s >> i-1 & 1)
            printf("%d ", i);
	printf("\n");
	return 0;
}
