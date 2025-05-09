// �˫���Ĵ�����
// �����ַ���s����s���˫�����Ӵ�t�ĳ���
// ˫�����Ӵ����ǿ��Էֳ��������Ĵ����ַ���
// ����"aabb"�����Էֳ�"aa"��"bb"
// �������� : https://www.luogu.com.cn/problem/P4555
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

char ss[MAXN << 1];//��������м������#
char a[MAXN];//ԭʼ����
int p[MAXN << 1];//�뾶����
int l[MAXN<<1];
int r[MAXN<<1];//��������
int n;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

void manacher() {
    manacherss();
    int maxans = 0;
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {//i�Ǵ�ʱ����������λ��
        len = r > i ? min(p[2 * c - i], r - i) : 1;//���ֵ�ǻ���ֵ  �����ס��  ��ô����ֵ��������ֵ  ��������ټ�
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //�������ס��  ��ôֱ����������
        }
        //��ʱ�Ѿ��������iΪ���ĵĻ��İ뾶��С
        if (i + len > r) {
            r = i + len;
            c = i;
            //����������ұ߽�  ��ôc����i  r����i+len
        }
        maxans = max(maxans, len);
        p[i] = len;
        //�õ����İ뾶
    }
    //return maxans - 1;
}

int main()
{
    scanf("%s",a);
    manacher();
    for (int i = 0, j = 0; i < n; i++) {
        while (i + p[i] > j) {
            l[j] = j - i;
            j += 2;//ֻ������#
        }
    }
    for (int i = n - 1, j = n - 1; i >= 0; i--) {
        while (i - p[i] < j) {
            r[j] = i - j;
            j -= 2;//ֻ������#
        }
    }
    int ans = 0;
    for (int i = 2; i <= n - 3; i += 2) {
        ans = max(ans, l[i] + r[i]);
    }
    cout<<ans;
    return 0;
}
