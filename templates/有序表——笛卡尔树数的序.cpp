// ������
// ����һ������Ϊn������arr����ʾ���β������֣����γ�һ������������
// Ҳ��ͬ����һ�����У����β������ֺ�Ҳ���γ�ͬ����̬������������
// �뷵���ֵ�����С�Ľ��
// 1 <= n <= 10^5
// �������� : https://www.luogu.com.cn/problem/P1377
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];

void build() {
    for (int i = 1, top = 0, pos = 0; i <= n; i++) {
        pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            pos--;
        }
        if (pos > 0) {
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;
        top = pos;
    }
}

void pre() {
    int size = 1, i = 0, cur;
    while (size > 0) {
        cur = sta[size--];
        arr[++i] = cur;
        if (rs[cur] != 0) {
            sta[++size] = rs[cur];
        }
        if (ls[cur] != 0) {
            sta[++size] = ls[cur];
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        arr[k]=i;
    }
    build();
    pre();
    for(int i=1;i<=n;i++){
        cout<<arr[i]<<' ';
    }
    return 0;
}
