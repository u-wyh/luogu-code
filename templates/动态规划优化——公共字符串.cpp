// �������Ƶ����������������
// ���������ַ���s1��s2��s1����Ϊn��s2����Ϊm
// ����s1��s2������������г���
// ע�⣺
// �����ַ�����ֻ��Сд��ĸ���
// 1 <= n <= 10^6
// 1 <= m <= 10^3
// ״̬����Ż��ľ����⣬��������֤
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <iomanip>

using namespace std;

// Ϊ�˲���
void randomString(char* ans, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        ans[i] = 'a' + rand() % 26;
    }
    ans[n] = '\0'; // ȷ���ַ�����null��β
}

// ���䶯̬�滮�İ汾
int lcs1(const string& str1, const string& str2) {
    int n = str1.size();
    int m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// ���������������Ż��İ汾
const int MAXN = 1000005;
const int MAXM = 1005;
const int NA = INT_MAX;

char s1[MAXN];
char s2[MAXM];
int n, m;
int Right[26];
int Next[MAXN][26];
int dp[MAXM][MAXM];

void build() {
    fill_n(Right, 26, NA);
    for (int i = n ; i >= 0; i--) { // ע�������n-1��ʼ���Ұ���-1�����ڳ�ʼ����
        for (int j = 0; j < 26; j++) {
            Next[i][j] =  Right[j]; // -1��ʾ��Чλ��
        }
        if (i > 0) {
            Right[s1[i-1] - 'a'] = i;
        }
    }
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }
}

// ����Ϊi��s2ǰ׺�������s1�ַ����γɳ���Ϊj�Ĺ���������
// ����s1�����һ���ַ���λ�ã���0��ʼ�������������������NA
int f(int i, int j) {
    if (i < j) return NA;
    if (j == 0) return 0; // ����-1��ʾ������
    if (dp[i][j] != -1) return dp[i][j];
    int cha = s2[i - 1] - 'a';
    int ans = f(i - 1, j); // ��ѡ��ǰ�ַ�
    int pre = f(i - 1, j - 1) ; // ѡ��ǰ�ַ�����ע��i-1����Խ��
    if (pre != NA) { // ����Ƿ���Ч
        ans =min(Next[pre][cha] , ans);
    }
    dp[i][j] = ans; // ��¼�����-1��ʾ�޷��γɳ���Ϊj��������
    return ans;
}

int lcs2(const string& str1, const string& str2) {
    strncpy(s1, str1.c_str(), MAXN);
    strncpy(s2, str2.c_str(), MAXM);
    n = strlen(s1);
    m = strlen(s2);
    build();
    int ans = 0;
    for (int j = m; j >= 1; j--) {
        int len = f(m, j);
        if (len != NA) {
            ans = j;
            break;
        }
    }
    return ans;
}

// Ϊ�˲���
int main() {
    srand(time(0));
    int n = 100;
    int m = 100;
    int testTime = 1000; // ���ٲ��Դ����Լӿ�����ٶ�
    cout << "���ܲ��Կ�ʼ" << endl;
    for (int i = 0; i < testTime; i++) {
        int size1 = rand() % n + 1;
        int size2 = rand() % m + 1;
        char* str1 = new char[size1 + 1];
        char* str2 = new char[size2 + 1];
        randomString(str1, size1);
        randomString(str2, size2);
        int ans1 = lcs1(string(str1), string(str2));
        int ans2 = lcs2(string(str1), string(str2));
        if (ans1 != ans2) {
            cout << "������!" << endl;
            //break; // ���������ֹͣ����
        }
        else{
            cout<<"��"<<setw(6)<<i+1<<"�������ȷ"<<endl;
        }
        delete[] str1;
        delete[] str2;
    }
    cout << "���ܲ��Խ���" << endl << endl;

    cout << "���ܲ��Կ�ʼ" << endl;
    n = 1000000;
    m = 100;
    cout << "n = " << n << endl;
    cout << "m = " << m << endl;
    char* str1 = new char[n + 1];
    char* str2 = new char[m + 1];
    //cout<<666<<endl;
    randomString(str1, n);
    randomString(str2, m);
    //cout<<777<<endl;

    clock_t start1 = clock();
    //cout<<555<<endl;
    int k1=lcs1(string(str1), string(str2));
    //cout<<444<<endl;
    clock_t end1 = clock();
    double elapsed1 = double(end1 - start1) / CLOCKS_PER_SEC;
    cout << "lcs1��������ʱ�� : " << elapsed1<< " ��" << endl;

    clock_t start2 = clock();
    int result = lcs2(string(str1), string(str2));
    clock_t end2 = clock();
    double elapsed2 = double(end2 - start2) / CLOCKS_PER_SEC;
    cout << "lcs2��������ʱ�� : " << elapsed2<< " ��" << endl;
    cout << "���ܲ��Խ���" << endl;

    delete[] str1;
    delete[] str2;
    return 0;
}
