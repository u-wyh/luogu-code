#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

#define re register
const int maxn = 1000005;
char st[maxn * 2];
int len[maxn * 2], cnt;
int vis[maxn * 2];
int T;
int mx, po;

inline void input ()
{
	char ch = getchar ();
	st[0] = '~', st[cnt = 1] = '#';
	while (ch < 'a' or ch > 'z') ch = getchar ();
	while (ch >= 'a' and ch <= 'z') st[++cnt] = ch, st[++cnt] = '#', ch = getchar ();
    st[cnt + 1] = '%';
}

int main ()
{
	scanf ("%d", &T);
	while (T--)
	{
		cnt = mx = po = 0;
		memset (vis, 0, sizeof vis);
		memset (len, 0, sizeof len);
		input ();
		for (re int i (1); i <= cnt; ++i)//Manacher ģ��
		{
			if (i <= mx) len[i] = min (mx - i, len[po * 2 - i]);
			while (st[i + len[i]] == st[i - len[i]]) len[i]++;
			if (i + len[i] > mx) mx = i + len[i] - 1, po = i;
		}
		for (re int i (cnt); i >= 1; --i)
		{
			if (i + len[i] - 1 == cnt) vis[i] = 1;//�����һ�η�ת��
			else if (vis[i + len[i] - 2] and i == len[i]) vis[i] = 1;//������ܷ�ת��ĳ�����ת�Ӵ����� qwqwq �� qwqw �� qw ���Ҳ���Խ��
		}
		for (re int i (1); i <= cnt; ++i) if (st[i] >= 'a' and st[i] <= 'z' and vis[i]) printf ("%d ", i / 2);
			//Manacher �������ַ���ת����ԭ�ַ���������ֱ�ӳ��� 2 �Ϳ��Եõ�ԭ�ַ����ĳ���
		printf ("\n");
	}
	return 0;
}
