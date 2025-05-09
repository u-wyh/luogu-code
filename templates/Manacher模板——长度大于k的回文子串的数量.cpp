// ���ص������Ӵ��������Ŀ
// ����һ���ַ���str��һ������k
// ����������str�зֳɶ���Ӵ�
// Ŀ�����ҵ�ĳһ�ֻ��ַ������о����ܶ�Ļ����Ӵ�
// ����ÿ�������Ӵ���Ҫ�󳤶�>=k���ұ˴�û���غϵĲ���
// ��������ܻ��ֳ����������Ļ����Ӵ�
// �������� : https://leetcode.cn/problems/maximum-number-of-non-overlapping-palindrome-substrings/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

char ss[MAXN << 1];//��������м������#
char a[MAXN];//ԭʼ����
int p[MAXN << 1];//�뾶����
int n,k;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

// ��չ��ss��lλ�ÿ�ʼ����Ѱ�һ��ģ���ss[l]һ����'#'
// һ����ĳ�����ĵĻ��İ뾶>k�����Ϸ��������±�
// ��ʾ�ҵ��˾���l����ҳ���>=k�Ļ��Ĵ�
// ���ص���������±�һ��Ҫ����'#'
// ���û�����з���(�����±�+1)������һ������'#'
// ��������ھ���l����ҳ���>=k�Ļ��Ĵ�������-1
int find(int l, int k) {
    for (int i = l, c = l, r = l, len; i < n; i++) {
        len = r > i ? min(p[2 * c - i], r - i) : 1;
        while (i + len < n && i - len >= l && ss[i + len] == ss[i - len]) {
            if (++len > k) {
                return i + k + (ss[i + k] != '#' ? 1 : 0);//���뵽��#�ſ��Է���  �����������ճ��
            }
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        p[i] = len;
    }
    return -1;
}

int main()
{
    scanf("%s",a);
    cin>>k;
    manacherss();
    int Next=0;
    int ans=0;
    while((Next=find(Next,k))!=-1){
        ans++;
    }
    cout<<ans;
    return 0;
}
