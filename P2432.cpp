#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[305] ;
int n, m ;
string s ;
string d[605] ;
signed main() {
	cin >> n >> m ;
	cin >> s ;
	for(int i = 1 ; i <= n ; i++) cin >> d[i] ;
	memset(f, 0x3f, sizeof(f)) ; //Ҫ����Сֵ����ʼ����INF
	f[0] = 0 ; //�߽� f[0] = 0
	for(int i = 1 ; i <= m ; i++) {
		f[i] = f[i - 1] + 1 ;
		for(int j = 1 ; j <= n ; j++) {
			int r1 = i, r2 = d[j].size() ;//ָ���˼��
			int flag = 1 ;//��¼�Ƿ����ƥ��ɹ�
			while(r1 && r2) {
				if(d[j][r2 - 1] == s[r1 - 1]) r1--, r2-- ; //��ƥ��ɹ�������ǰ��һλ
				else r1-- ; // ��Ȼ ��ĸ��ָ��ǰ��һλ
				if(!r2) flag = 0 ; //ƥ��ɹ�
			}
			if(!flag) f[i] = min(f[r1] + i - r1 - (int)d[j].size(), f[i]) ; // ��ƥ��ɹ���ת��
		}
	}
	cout << f[m] ;
	return 0 ;
}
