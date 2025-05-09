//P3501
//����������Manacher�㷨��˼��
//�����������
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

char ss[MAXN << 1];//��������м������#
char a[MAXN];//ԭʼ����
int p[MAXN << 1];//�뾶����
char change[300];
int n;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

void manacher(){
    for (int i = 0, c = 0, r = 0, len; i < n; i+=2) {//i�Ǵ�ʱ����������λ��
        //�����ǱȽ������һ�� ��Ϊ���һ����ż������  ������������  ����ÿ�μ�2
        len = r > i ? min(p[2 * c - i], r - i) : 1;//���ֵ�ǻ���ֵ  �����ס��  ��ô����ֵ��������ֵ  ��������ټ�
        while (i + len < n && i - len >= 0 && ss[i + len] == change[ss[i - len]]) {
            len++;
            //�������ס��  ��ôֱ����������
        }
        //��ʱ�Ѿ��������iΪ���ĵĻ��İ뾶��С
        if (i + len > r) {
            r = i + len;
            c = i;//c��ʾ��������r�����Ǹ���Ϊ���ĵ��ұ߽�
            //����������ұ߽�  ��ôc����i  r����i+len
        }
        p[i] = len;
        //�õ����İ뾶
    }
}

signed main()
{
    change['0']='1';
    change['1']='0';
    change['#']='#';
    cin>>n;
    scanf("%s",a);
    manacherss();
    manacher();
    int ans=0;
    for(int i=0;i<n;i++){
        ans+=(p[i]/2);
    }
    cout<<ans<<endl;
    return 0;
}
