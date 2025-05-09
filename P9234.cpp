#include <iostream>
#include <algorithm>
#include <unordered_map>

#define i64 long long
#define reg register
#define qwq puts("fzy qwq ~");

using namespace std;

const int inf = 0x7fffffff;

int n, mid, ans = inf; int m;
int a[31]; bool spt[31];
unordered_map<int, int> tb;

inline void dfs1(int p, int w, int k)
{
	if (w > m || k > ans || (tb.count(w) && tb[w] < k)) return; // ��֦
	if (w == m) { ans = min(ans, k); return; } // ��������
	if (p == mid + 1)
	{
		if (w <= m)
		{
			if (tb.count(w))
				tb[w] = min(tb[w], k);
			else 
				tb[w] = k;
			// ��¼Ŀǰ�ܵõ������� w ������Ҫ�ĵ���
		}
		return;
	}
	dfs1(p + 1, w, k);				 // ���ϵ��ӣ���Ҫ��
	dfs1(p + 1, w + a[p], k + 1);	 // ��һ������
	dfs1(p + 1, w + (a[p] << 1), k); // һ�۱��죬��������
}
inline void dfs2(int p, int w, int k) // ��ͬ��
{
	if (w > m || k > ans) return;
	if (w == m) { ans = min(ans, k); return; }
	if (p == n + 1)
	{
		if (w <= m && tb.count(m - w))
			ans = min(ans, tb[m - w] + k); // ���ܹ��õ��պ����� m �Ĺϣ����´�
		return;
 	}
	dfs2(p + 1, w, k);
	dfs2(p + 1, w + a[p], k + 1);
	dfs2(p + 1, w + (a[p] << 1), k);
}


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	m <<= 1; mid = n >> 1;
	// Ԥ�Ȱѹϵ�������������ֹ����С��
	for (reg int i = 1; i <= n; ++i)
		cin >> a[i];
		
	sort(a + 1, a + n + 1);
	dfs1(1, 0, 0);
	dfs2(mid + 1, 0, 0);
	
	cout << (ans == inf ? -1 : ans) << endl;
	return 0;
}
