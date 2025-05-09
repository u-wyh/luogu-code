// �ڵ���ྭ�����ε�tsp����
// ������n���ص㣬��m������������ӣ�ÿ������Ȩֵ
// �������ѡһ�������Ŀ���Ǿ������еĵ㣬���ղ��ػص�������
// ����ÿ���������Ե�������
// ������·����С�Ƕ���
// 1 <= n <= 10
// 1 <= m <= 100
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=3001
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<iostream>
#include<cmath>
#include<climits>
using namespace std;
const int MAXN = 10;
const int MAXS = pow(3, MAXN);

int n,m;
int graph[MAXN][MAXN];
int dp[MAXN][MAXS];
int complete[1 << MAXN];//��ʾ���п��ܵ�������Ч״̬
int size;

void dfs(int i, int bit, int s) {
    if (i == n) {
        complete[size++] = s;
    } else {
        dfs(i + 1, bit * 3, s + bit);//��ʾ���λ������һ��
        dfs(i + 1, bit * 3, s + 2 * bit);//��ʾ���λ����������
    }
}

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INT_MAX;
        }
    }
    int maxs = pow(3, n);
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < maxs; s++) {
            dp[i][s] = -1;
        }
    }
    size = 0;
    dfs(0, 1, 0);
}

int f(int i, int s) {
    //��ʾ���һ���������i  ������ε���i״̬��s
    if (s == 0) {
        return 0;
    }
    if (dp[i][s] != -1) {
        return dp[i][s];
    }
    int ans = INT_MAX;
    for (int j = 0, bit = 1, pre; j < n; j++, bit *= 3) {
        if ((s / bit) % 3 > 0) {//ö��
            pre = f(j, s - bit);
            if (pre != INT_MAX && graph[j][i] != INT_MAX) {
                ans = min(ans, pre + graph[j][i]);
            }
        }
    }
    dp[i][s] = ans;
    return ans;
}

int compute() {
    int ans = INT_MAX;
    for (int k = 0; k < size; k++) {
        for (int i = 0, bit = 1; i < n; i++, bit *= 3) {
            ans = min(ans, f(i, complete[k] - bit));
            //����ö�����һ������ĵ�
        }
    }
    return ans;
}

int main()
{
    while(true){
        cin>>n>>m;
        build();
        for (int i = 1, u, v, w; i <= m; i++) {
            cin>>u>>v>>w;
            u-=1;
            v-=1;
            if (w < graph[u][v]) {
                graph[u][v] = graph[v][u] = w;//ѡ���Ȩ��С�Ľ���
            }
        }
        int ans = compute();
        cout<<(ans == INT_MAX ? -1 : ans)<<endl;
    }
    return 0;
}
