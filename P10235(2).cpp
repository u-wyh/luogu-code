#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#define lowbit(x) x & -x
using namespace std;

const int N = 100010;

int T, n, k;
int a[N], c[N];
int nums[N];
int tt;
int fnd[N];

int find(int x) {
	return lower_bound(nums + 1, nums + tt + 1, x) - nums;
}

int ask(int x) {
	int res = 0;
	for(; x; x -= lowbit(x)) res += c[x];
	return res;
}

void add(int x, int y) {
	for(; x <= n; x += lowbit(x)) c[x] += y;
}

bool check(long long limit) {
	int cnt = 1; //����
	long long f = 0; //Ŀǰ����Ķε��������
	int L = 1; //Ŀǰ����Ķε���˵�
	for(int i = 1; i <= n; i++) {
		int tmp = ask(tt) - ask(fnd[i]); //�����������������
		if(f + tmp > limit) {
			cnt++; //���� + 1
			f = 0; //�����������
			for(int j = L; j <= i - 1; j++)
				add(fnd[j], -1); //�����һ����Ĺ���
			L = i; //������˵�
		}
		else f += tmp;
		add(fnd[i], 1); //������״����
	}
	for(int i = L; i <= n; i++) add(fnd[i], -1); //��Ҫ�������һ��ҲҪĨȥ
	return cnt > k;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			nums[++tt] = a[i];
		}
		sort(nums + 1, nums + tt + 1);
		tt = unique(nums + 1, nums + tt + 1) - nums - 1;
		for(int i = 1; i <= n; i++) fnd[i] = find(a[i]);
		long long l = 0, r = 1e10;
		while(l < r) {
			long long mid = l + r >> 1;
			if(check(mid)) l = mid + 1;
			else r = mid;
		}
		printf("%lld\n", l);
		for(int i = 1; i <= tt; i++) nums[i] = 0;
		tt = 0;
	}
	return 0;
}
