//P3375
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

char s1[MAXN];
char s2[MAXN];
int Next[MAXN];
int n,m;

// ����next����
void nextArray() {
    if (m == 1) {
        Next[0] = -1;
        return ;
    }

    Next[0] = -1;
    Next[1] = 0;

    int i = 2, cn = 0;
    while (i <= m) {
        if (s2[i - 1] == s2[cn]) {
            Next[i++] = ++cn;
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i++] = 0;
        }
    }
}

// KMP�㷨�ĺ��ĺ���
void kmp() {
    n = strlen(s1), m = strlen(s2);
    int x = 0, y = 0;
    nextArray();
    // s1�е�ǰ�ȶԵ�λ����x
    // s2�е�ǰ�ȶԵ�λ����y
    while (x < n) {
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
        if(y==m){
            cout<<x-y+1<<endl;
            y=Next[y];
        }
        if((n-x)<(m-y))
            break;
    }
}

int main()
{
    cin>>s1>>s2;
    kmp();
    for(int i=1;i<=m;i++){
        printf("%d ",Next[i]);
    }
    cout<<endl;
    return 0;
}

