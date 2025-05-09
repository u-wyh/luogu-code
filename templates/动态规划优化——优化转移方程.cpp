// ��õĲ���
// һ����n̨���������1 ~ n�����л����ų�һ��
// ��ֻ��һ̨һ̨�Ĳ������������Ծ��������˳���������л�����Ҫ����
// ������������no[]��one[]��both[]
// no[i] : ���i�Ż�������ʱ������û�л������𣬴�ʱ�ܻ�õ�����
// one[i] : ���i�Ż�������ʱ��������һ̨�������𣬴�ʱ�ܻ�õ�����
// both[i] : ���i�Ż�������ʱ����������̨�������𣬴�ʱ�ܻ�õ�����
// ��1�Ż�������n�Ż�����Ȼ��������̨���ڵĻ���
// ���ز�����������
// 1 <= n <= 10^5
// 0 <= no[i]��one[i]��both[i]
// ������ʵ�󳧱��ԣ���������֤
//�����Ҫ��������ж�Ҫ������ ֻ��˳��ͬ���������治ͬ
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1001;

int no[MAXN];
int one[MAXN];
int both[MAXN];
int n;
int dp[1001][1001];
int dp1[1001][2];

// ����l...r��Χ�ϵĻ���
// ����l-1��r+1�Ļ���һ����û�в���
// ���ز�����������
int f(int l, int r) {
    //cout<<111<<endl;
    if (l == r) {
        return no[l];
    }
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans = f(l + 1, r) + one[l];
    ans = max(ans, f(l, r - 1) + one[r]);
    for (int i = l + 1; i < r; i++) {
        ans = max(ans, f(l, i - 1) + f(i + 1, r) + both[i]);
    }
    dp[l][r] = ans;
    return ans;
}

// ����dp�ĳ���
// ʱ�临�Ӷ�O(n^3)
// ��ȷ���ǲ����Ƽ�
int best1() {
    //cout<<222<<endl;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            dp[l][r] = -1;
        }
    }
    //cout<<999<<endl;
    return f(1, n);
}

// ����dp�ĳ���
// ʱ�临�Ӷ�O(n)
// �Ƽ�
//dp1[i][j]��ʾ��n����i���λ��  ���״̬Ϊj����������Ž�
//j=0 ��ʾ��ߵĻ�û�в���
//j=1 ��ʾ��ߵ��Ѿ�������
int best2() {
    dp1[n][0] = no[n];
    dp1[n][1] = one[n];
    for (int i = n - 1; i >= 1; i--) {
        dp1[i][0] = max(no[i] + dp1[i + 1][1], one[i] + dp1[i + 1][0]);//��ߵ�û�в��� ��ô���ֿ���  
        //�Ȳ����Լ�����ȥ��������  ��ô����no[i]+�����ұ߶��� ��ߵ��Ѿ�������  �����Ȳ����ұߵ�  ���������Լ�
        dp1[i][1] = max(one[i] + dp1[i + 1][1], both[i] + dp1[i + 1][0]);//��ߵ��Ѿ������� ��ôҲ�����ֿ���
        //һ���Ȳ����Լ� һ���Ȳ����Լ��ұߵ�
    }
    return dp1[1][0];
}

// Ϊ�˲���
void random(int size, int v) {
    n = size;
    srand(time(0));
    for (int i = 1; i <= n; i++) {
        no[i] = rand() % v;
        one[i] = rand() % v;
        both[i] = rand() % v;
    }
}

// Ϊ�˲���
int main() {
    int maxn = 100;
    int maxv = 100;
    int testTime = 10000;
    cout << "���Կ�ʼ" << endl;
    for (int i = 0; i < testTime; i++) {
        int size = rand() % maxn + 1;
        random(size, maxv);
        int ans1 = best1();
        int ans2 = best2();
        if (ans1 != ans2) {
            cout << "������!" << endl;
        }
        else{
            cout<<"��"<<setw(6)<<i<<"�������ȷ"<<endl;
        }
    }
    cout << "���Խ���" << endl;
    return 0;
}
