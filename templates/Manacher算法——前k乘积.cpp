// ����ǰk�����������Ȼ����Ӵ����ȳ˻�
// ����һ���ַ���s����ֵk��ֻ���������������ȵĻ����Ӵ�
// �������г���ǰk���Ļ����Ӵ��ĳ��ȳ˻��Ƕ���
// ����������ȵĻ����Ӵ���������k��������-1
// �������� : https://www.luogu.com.cn/problem/P1659
// �𰸶�19930726ȡģ
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MOD = 19930726;
const int MAXN = 10000005;

int n,m;
long k;
char ss[MAXN << 1];//��������м������#
char a[MAXN];//ԭʼ����
int p[MAXN << 1];//�뾶����
int cnt[MAXN];

void manacherss() {
    n = m * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

int manacher() {
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
    return maxans - 1;
}

long power(long x, long n) {
    long ans = 1;
    while (n > 0) {
        if ((n & 1) == 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ans;
}//������

int main()
{
    cin>>m>>k;
    scanf("%s",a);
    manacher();
    for(int i=1;i<n;i+=2){
        cnt[p[i]-1]++;
        //ͳ�Ƴ��ַ�������
    }
    long ans=1;
    long sum=0;
    for(int len=(m&1)==1?m:(m-1);len>=0&&k>=0;len-=2){
        sum+=cnt[len];
        ans=(ans*(long)power(len,min((long)k,sum)))%MOD;
        k-=sum;
    }
    if(k>=0){
        ans=-1;
    }
    cout<<ans;
    return 0;
}
