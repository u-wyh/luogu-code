// ��·
// һ����n���ڵ㣬���1~n��һ����m������ߣ�ÿ����1����
// ��һ���ռ���·����ÿ���㶼����ֱ���ƶ�2^k���ÿ���ӿ����������k��ֵ
// ��Ŀ��֤1��n֮��һ�����Ե������1��n�����ü���
// 2 <= n <= 50
// m <= 10^4
// k <= 64
// �������� : https://www.luogu.com.cn/problem/P1613
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<iostream>
#include<climits>
#include<cmath>
using namespace std;
const int MAXN = 61;
const int MAXP = 64;
const int NA = INT_MAX;

// st[i][j][p] : i��j�ľ����ǲ���2^p
bool st[MAXN][MAXN][MAXP + 1];
// time[i][j] : i��j�����ʱ��
int t[MAXN][MAXN];
int n, m;

int compute() {
    // ��ö�ٴη�
    // ��ö������
    // ���ö��ÿһ��(i,j)
    for (int p = 1; p <= MAXP; p++) {
        for (int jump = 1; jump <= n; jump++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (st[i][jump][p - 1] && st[jump][j][p - 1]) {
                        st[i][j][p] = true;
                        t[i][j] = 1;
                    }
                }
            }
        }
    }
    if (t[1][n] != 1) {
        // ��ö������
        // ���ö��ÿһ��(i,j)
        for (int jump = 1; jump <= n; jump++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (t[i][jump] != NA && t[jump][j] != NA) {
                        t[i][j] = min(t[i][j], t[i][jump] + t[jump][j]);
                    }
                }
            }
        }
    }
    return t[1][n];
}

int main()
{
    cin>>n>>m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            t[i][j] = NA;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        st[u][v][0]=true;
        t[u][v]=1;
    }
    cout<<compute()<<endl;
    return 0;
}
