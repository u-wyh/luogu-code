// �ѿ�����ģ��(C++��)
// ����һ������Ϊn������arr���±��1��ʼ
// ����һ�ö��������±갴��������������֯��ֵ����С������֯
// �����Ĺ���Ҫ��ʱ�临�Ӷ�O(n)
// ����֮��Ϊ����֤
// ��ӡ��i * (left[i] + 1)��������Ϣ���������ֵ
// ��ӡ��i * (right[i] + 1)��������Ϣ���������ֵ
// 1 <= n <= 10^7
// �������� : https://www.luogu.com.cn/problem/P5854
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

#define LL long long

using namespace std;

const int MAXN = 10000001;

int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int n;

//���û�б�С������  ��ô��������һֱ���ұ߽ڵ㽨��
//Ҳ�����нڵ��ջ�е���
void build() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            //����ջ  ���������ϵ�Ԫ��
            pos--;
        }
        if (pos > 0) {
            //��ô����û�е��ɾ�   ��ô��ǰ�ڵ�ͻ��Ϊջ���ڵ���Һ���
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            //��ʾ��Ԫ�ص��� ��ôһ���ǵ�ǰ�ڵ�����ӽڵ�
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;//����ջ��
        top = pos;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build();
    long long ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        ans1 ^= 1LL * i * (ls[i] + 1);
        ans2 ^= 1LL * i * (rs[i] + 1);
    }
    cout << ans1 << " " << ans2 << endl;
    return 0;
}
