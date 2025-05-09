//P8085
//������ϣ��ȫ���ǹ����˵�����
//���ȴ����ÿ��λ���ϵ��ַ����������ͬ���ַ������Ƕ���
//ҲҪ��¼�Լ��ұ���ͬ�ַ���λ��
//Ȼ��Ե�һ��ά��һ������  ֻҪ����ߵ��ַ����� ��ô���Լ��ұߵ��Ǹ�����Ϊ-1
//Ȼ��Դ��ڹ�ϣ����
#include <bits/stdc++.h>
using namespace std;
const int INF = 2147483647;
const int MAXN = 1e6 + 3;
const int BASE = 13131;

int L1[MAXN], R1[MAXN];
int L2[MAXN], R2[MAXN];
int A[MAXN], B[MAXN], n, m;
long long H[MAXN], P[MAXN];
map<string, int> M;

int main() {
    string t;

    while (cin >> t && t != "$") {
        R1[M[t]] = ++n;//��ʾ��������ұ������ٴγ��ֵ�λ��
        L1[n] = M[t];//��ʾ���������������ٴγ��ֵ�λ��
        M[t] = n;
    }

    M.clear();

    while (cin >> t && t != "$") {
        R2[M[t]] = ++m;
        L2[m] = M[t];
        M[t] = m;
    }

    for (int i = 1; i <= n; ++i) if (!R1[i]) R1[i] = INF;
    for (int i = 1; i <= m; ++i) if (!R2[i]) R2[i] = INF;//����ұ�û�г��ֹ�

    for (int i = 1; i <= n; ++i) A[i] = (L1[i] ? i - L1[i] : -1);
    for (int i = 1; i <= m; ++i) B[i] = (L2[i] ? i - L2[i] : -1);//��λ�õĵ��ʾ����Լ���߳�������λ�õľ���

    long long h0 = 0, h = 0;
    P[0] = 1;
    for (int i = 1; i <= m; ++i) P[i] = P[i - 1] * BASE;

    for (int i = 1; i <= m; ++i) h0 = h0 * BASE + B[i];//h0��������Ҫ���
    for (int i = 1; i <= m; ++i) h = h * BASE + A[i];

    if (h == h0) {
        cout << 1 << endl;
        return 0;
    }

    for (int i = m + 1; i <= n; ++i) {
        h = h * BASE + A[i] - A[i - m] * P[m];//��û����ȫ����ǰ�Ĺ�ϣֵ

        if (R1[i - m] <= i) {//�������ı仯������ѯ�ķ�Χ��
            int overlapIndex = R1[i - m];
            h -= A[overlapIndex] * P[i - overlapIndex];//��ȥ����Ĺ�ϣֵ
            A[overlapIndex] = -1;
            h += A[overlapIndex] * P[i - overlapIndex];  // ����������Ĺ�ϣֵ
        } else if (R1[i - m] <= n) {
            A[R1[i - m]] = -1;
        }

        if (h == h0) {
            cout << i - m + 1 << endl;
            return 0;
        }
    }

    return 0;
}
