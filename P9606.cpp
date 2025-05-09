#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;

int n,m;
char ss[MAXN << 1];//��������м������#
char a[MAXN];//ԭʼ����
int p[MAXN << 1];//�뾶����

void manacherss() {
    n = strlen(a) * 2 + 1;
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
int main()
{
    cin>>n;
    m=n;
    scanf("%s",a);
    manacher();
    int ans;
    for(int i=0;i<n;i++){
        //cout<<i/2<<' '<<p[i]/2<<' '<<i<<' '<<p[i]<<endl;
        if((i+p[i])==n){
            ans=m-(p[i]-1);
            break;
        }
    }
    cout<<ans;
    return 0;
}
