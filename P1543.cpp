#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
queue <int> q;
int to[MAXN], n, ans, in[MAXN];
bool choose[MAXN], vis[MAXN]; // choose�ǿ��Ƿ���ȥ��vis�ǿ��ڲ��ڻ���

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> to[i];
		in[to[i]] ++;
	}
	for (int i = 1; i <= n; i++)
		if (!in[i]) 
			q.push(i); // ���˼�ܣ���ֹΪ����Ϊ��������ȥ
	while (q.size()) {
		int u = q.front();
		vis[u] = 1;
		if (choose[u]) {
			in[to[u]] --; // ��ȥִ�����������ӵ������������ļ��
			if (in[to[u]] == 0) 
				q.push(to[u]);
		} else { // ���������ȥִ�����������ӵ��˾�Ҫȥִ������
			if (!choose[to[u]]) { // ��ֹ������ӺͶ���ͳ�ƴ�
				ans++;
				q.push(to[u]);
			}
			choose[to[u]] = 1;
		}
		q.pop();
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i] && in[i]) { // �ڻ��У��϶�ѡһ�������ȥִ������
			int cnt = 0;
			for (int j = i; !vis[j]; j = to[j]) {
				cnt++;
				vis[j] = 1;
			}
			ans += cnt / 2; // ����ȡ��
		}
	}
	cout << ans;
}
