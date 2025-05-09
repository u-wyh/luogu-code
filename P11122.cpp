#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 20;

int n, m;
LL s;
int a[N][N];
LL l[N];

unordered_map<LL, int> Map;

int main() {
	scanf("%d%d", &n, &m);

	LL sum = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			sum += a[i][j];
		}
	}
	scanf("%lld", &s);

	if(sum == s) {
		puts("YES");
		printf("0");
		return 0;
	}
	
	int t1 = 0, t2 = 0, t3 = 0, res = 0;
	for(int i = 0; i < (1 << n); i++) { // 行的删除情况
		int re = n;
		for(int j = 1; j <= n; j++) {
			if((i >> j - 1) & 1) {
				re--;
			}
		}
		for(int j = 1; j <= m; j++) {
			l[j] = 0;
			for(int k = 1; k <= n; k++) {
				if((i >> k - 1) & 1) {
					l[j] += a[k][j];
				}
			}
		}
		Map.clear();
		for(int j = 0; j < (1 << (m >> 1)); j++) { // 前一半列的删除情况
			LL t = 0;
			for(register int k = 1; k <= (m >> 1); k++) {
				if((j >> k - 1) & 1) {
					t += l[k];
				}
			}
			Map[t] = j;
		}
		for(int j = 0; j < (1 << m - (m >> 1)); j++) { // 后一半列的删除情况
			LL t = 0;
			for(int k = 1; k <= m - (m >> 1); k++) {
				if((j >> k - 1) & 1) {
					t += l[m / 2 + k];
				}
			}
			if(Map.count(s - t)) {
				t1 = Map[s - t];
				t2 = j;
				t3 = i;
				goto end; // 不用找最优解啦，随便一个就可以
			}
		}
	}

	puts("NO");
	return 0;
	
	end:;
	puts("YES");
	int cnt = 0; // 删除的数量
	for(int i = 1; i <= n; i++) {
		if(!((t3 >> i - 1) & 1)) {
			cnt++;
		}
	}
	for(int i = 1; i <= (m >> 1); i++) {
		if(!((t1 >> i - 1) & 1)) {
			cnt++;
		}
	}
	for(int i = 1; i <= m - (m >> 1); i++) {
		if(!((t2 >> i - 1) & 1)) {
			cnt++;
		}
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++) {
		if(!((t3 >> i - 1) & 1)) {
			printf("1 %d\n", i);
		}
	}
	for(int i = 1; i <= (m >> 1); i++) {
		if(!((t1 >> i - 1) & 1)) {
			printf("2 %d\n", i);
		}
	}
	for(int i = 1; i <= m - (m >> 1); i++) {
		if(!((t2 >> i - 1) & 1)) {
			printf("2 %d\n", m / 2 + i);
		}
	}
	
	return 0;
}