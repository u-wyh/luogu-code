// ����(����AC�Զ����������)
// ���ǳ�һ��������xΪ�������ֵ�����Ϊ
// x��ʮ�����в��������ִ�����s������һ��Ԫ����Ϊ�Ӵ�
// ����s = { 22, 333, 0233 }
// 233���������֣�2333��20233��3223������������
// ����n��s�����㲻����n���������ֵĸ���
// �𰸶�1000000007ȡģ
// �������� : https://www.luogu.com.cn/problem/P3311
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
// Ŀ���ַ���������
const int MAXN = 1301;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 2001;

// ���������
string num;

// �������ֵĳ���
int n,m;

// AC�Զ���
int tree[MAXS][10];
int fail[MAXS];
int cnt = 0;

// ������Ŀ��أ�����Ϊ�����κ�Ŀ�괮��ֱ�ӱ���
// ����ÿ���ڵ��¼�Ƿ񴥷�����
bool alert[MAXS];
int Queue[MAXS];

// ��̬�滮��
int dp[MAXN][MAXS][2][2];

void clear() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= cnt; j++) {
            dp[i][j][0][0] = -1;
            dp[i][j][0][1] = -1;
            dp[i][j][1][0] = -1;
            dp[i][j][1][1] = -1;
        }
    }
}

// AC�Զ�������Ŀ���ַ���
void insert(string word) {
    int u = 0;
    for (char s:word) {
        int c = s - '0';
        if (tree[u][c] == 0) {
            tree[u][c] = ++cnt;
        }
        u = tree[u][c];
    }
    alert[u] = true;
}

// ��������Ŀ���ַ���֮��
// ����failָ�� �Լ� ����ֱ����ת֧·
// ����AC�Զ����̶����Ż�
// �������б��ǰ�Ʒ�ֹ��Ȧ���Ż�
void setFail() {
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 9; i++) {
        if (tree[0][i] > 0) {
            Queue[r++] = tree[0][i];
        }
    }
    while (l < r) {
        int u = Queue[l++];
        for (int i = 0; i <= 9; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];
                Queue[r++] = tree[u][i];
            }
        }
        // ���б��ǰ��
        alert[u] |= alert[fail[u]];
    }
}

// �߼���֧����ϸ�г����İ汾
// i������λ��
// j : AC�Զ����������Ľڵ���
// free : �ǲ��ǿ�������ѡ����
// free = 0����������ѡ�����֣�Ҫ���ǵ�ǰ���ֵĴ�С
// free = 1��������ѡ������
// has : ֮ǰ��û��ѡ�������
// has = 0��֮ǰûѡ�������
// has = 1��֮ǰѡ�������
// ����i....�������ֵĸ���
int f1(int i, int j, int free, int has) {
    if (alert[j]) {
        return 0;
    }
    if (i == n) {
        return has;
    }
    if (dp[i][j][free][has] != -1) {
        return dp[i][j][free][has];
    }
    int ans = 0;
    int cur = num[i] - '0';
    if (has == 0) {
        if (free == 0) {
            // ��֧1 : ֮ǰû��ѡ������� �� ֮ǰ�ľ��ߵ���num��ǰ׺
            // ����������˵��iһ����0λ��, ��ôcur��Ȼ����0
            // ��ǰѡ��Ҫ����
            ans = (ans + f1(i + 1, 0, 1, 0)) % MOD;
            // ��ǰѡ������ֱ�curС
            for (int pick = 1; pick < cur; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
            // ��ǰѡ�������Ϊcur
            ans = (ans + f1(i + 1, tree[j][cur], 0, 1)) % MOD;
        } else {
            // ��֧2 : ֮ǰû��ѡ������� �� ֮ǰ�ľ���С��num��ǰ׺
            // ��ǰѡ��Ҫ����
            ans = (ans + f1(i + 1, 0, 1, 0)) % MOD;
            // ��ǰ����ѡ��1~9
            for (int pick = 1; pick <= 9; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
        }
    } else {
        if (free == 0) {
            // ��֧3 : ֮ǰ�Ѿ�ѡ������� �� ֮ǰ�ľ��ߵ���num��ǰ׺
            // ��ǰѡ������ֱ�curС
            for (int pick = 0; pick < cur; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
            // ��ǰѡ�������Ϊcur
            ans = (ans + f1(i + 1, tree[j][cur], 0, 1)) % MOD;
        } else {
            // ��֧4 : ֮ǰ�Ѿ�ѡ������� �� ֮ǰ�ľ���С��num��ǰ׺
            // ��ǰ����ѡ��0~9
            for (int pick = 0; pick <= 9; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
        }
    }
    dp[i][j][free][has] = ans;
    return ans;
}

int main()
{
    //string num;
    cin>>num;
    n=num.length();
    //cout<<n<<endl;
    cin>>m;
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        insert(s);
    }
    setFail();
    // ��ն�̬�滮��
    clear();
    // ִ�м��仯����
    cout<<f1(0,0,0,0);
    return 0;
}
