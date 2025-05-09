//P3375
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

char s1[MAXN];
char s2[MAXN];
int Next[MAXN];

// ����next����
void nextArray(const char *s, int m) {
    if (m == 1) {
        Next[0] = -1;
        return ;
    }

    Next[0] = -1;
    Next[1] = 0;

    int i = 2, cn = 0;
    // i��ʾ��ǰҪ��nextֵ��λ��
    // cn��ʾ��ǰҪ��ǰһ���ַ��ȶԵ��±�
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            Next[i] = ++cn;
            if(s[Next[i]]==s[i]){
                Next[i]=Next[Next[i]];
            }
            i++;
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i] = 0;
            if(s[Next[i]]==s[i]){
                Next[i]=Next[Next[i]];
            }
            i++;
        }
        //��������Ż��������˼��  ���ƥ��ɹ���  ��ô�����ܲ��ܸ�ʡ�� ����һ��
        //���ʧ����  ��ôû���ʸ����
        //������Ż�����  ��˼�����λ���϶Բ���  ��ת��λ�ú�����һ��
        //����һ��Ҳ�ǲ��Ե�  ��ô���ٵ�һ��
//        if(s[Next[i]]==s[i]){
//            Next[i]=Next[Next[i]];
//        }
    }
}

// KMP�㷨�ĺ��ĺ���
int kmp(const char *s1, const char *s2) {
    int n = strlen(s1), m = strlen(s2), x = 0, y = 0;
    nextArray(s2, m);
    for(int i=0;i<m;i++){
        cout<<Next[i]<<' ';
    }
    cout<<endl;
    // s1�е�ǰ�ȶԵ�λ����x
    // s2�е�ǰ�ȶԵ�λ����y
    while (x < n && y < m) {
        if (s1[x] == s2[y]) {
            x++;
            y++;
        } else if (y == 0) {
            x++;
            //��ʾs2�Ѿ��ڵ�һ��λ����
        } else {
            y = Next[y];
            //��ʾs2��ǰ��
        }
    }

    return y == m ? x - y : -1;
}

int main()
{
    cin>>s1>>s2;
    int result = kmp(s1, s2);
    if (result != -1) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found\n");
    }
    return 0;
}
