// ��ƽ
// һ����n�����룬���1~n��ÿ�������������Ϊ1�ˣ�����2�ˣ�����3��
// ����������֮��Ĺ�ϵ��һ��n * n�Ķ�ά����s
// s[i][j] == '+'������i������j��        s[i][j] == '-'������i������j��
// s[i][j] == '='������i������j����һ��   s[i][j] == '?'������i������j��ϵδ֪
// ���ݱ�֤���ٴ���һ��������ϸþ���
// �������Ϊa��b�����룬����������һ���������ƽ����ߣ���Ҫ��ѡ�������������ƽ�ұ�
// �����ж����ַ�����һ������ƽ�����(ans1)��һ������ƽһ����(ans2)��һ������ƽ�ұ���(ans3)
// 1 <= n <= 50
// �������� : https://www.luogu.com.cn/problem/P2474
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 51;

int dmin[MAXN][MAXN];
int dmax[MAXN][MAXN];
char s[MAXN][MAXN];

int n, a, b;
int ans1, ans2, ans3;

void compute() {
    // ���ó�ʼ��ϵ
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == '=') {
                dmin[i][j] = 0;
                dmax[i][j] = 0;
            } else if (s[i][j] == '+') {
                dmin[i][j] = 1;
                dmax[i][j] = 2;
            } else if (s[i][j] == '-') {
                dmin[i][j] = -2;
                dmax[i][j] = -1;
            } else {
                dmin[i][j] = -2;
                dmax[i][j] = 2;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        dmin[i][i] = 0;
        dmax[i][i] = 0;
    }
    // ���Խ���065��Floyd�㷨
    for (int bridge = 1; bridge <= n; bridge++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dmin[i][j] = max(dmin[i][j], dmin[i][bridge] + dmin[bridge][j]);
                dmax[i][j] = min(dmax[i][j], dmax[i][bridge] + dmax[bridge][j]);
            }
        }
    }
    // ͳ�ƴ�
    ans1 = ans2 = ans3 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (i != a && i != b && j != a && j != b) {
                if (dmin[a][i] > dmax[j][b] || dmin[a][j] > dmax[i][b]) {
                    ans1++;
                }
                if (dmax[a][i] < dmin[j][b] || dmax[a][j] < dmin[i][b]) {
                    ans3++;
                }
                if (dmin[a][i] == dmax[a][i] && dmin[j][b] == dmax[j][b] && dmin[a][i] == dmin[j][b]) {
                    ans2++;
                } else if (dmin[b][i] == dmax[b][i] && dmin[j][a] == dmax[j][a] && dmin[b][i] == dmin[j][a]) {
                    ans2++;
                }
            }
        }
    }
}

int main()
{
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>s[i][j];
        }
    }
    compute();
    cout<<ans1<<' '<<ans2<<' '<<ans3;
    return 0;
}
