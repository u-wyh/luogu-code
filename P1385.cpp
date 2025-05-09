#include <iostream>
#define MOD 1000000007
using namespace std;

int testCases;
string inputString;
long long dp[110][5000]; // dp[i][j] ��ʾǰ i ���ַ�����Ϊ j ��������

int main() {
    cin >> testCases;
    // ��ʼ���������ַ�ʱ���� ASCII ֵ��ȥ 'a' �Ľ����Ϊ��Ӧ�ĺ�
    for (int i = 0; i < 26; i++) {
        dp[1][i] = 1;
    }

    // ��̬�滮��� dp ����
    for (int length = 2; length <= 100; length++) {
        dp[length][0] = 1; // �κγ��ȵ��ַ�������Ϊ 0 �����ֻ��һ�֣����������κ��ַ���
        for (int sum = 1; sum <= 2700; sum++) {
            for (int charValue = 0; charValue < 26; charValue++) { // 'a' �� 'z' �� ASCII ��ֵ
                if (sum - charValue >= 0) {
                    dp[length][sum] = (dp[length][sum] % MOD + dp[length - 1][sum - charValue] % MOD) % MOD;
                }
            }
        }
    }

    // ����ÿ����������
    while (testCases--) {
        cin >> inputString;
        int stringSum = 0;
        for (char c : inputString) {
            stringSum += c - 'a'; // �����ַ����������ַ���Ӧ�ĺ�
        }
        // ����������ȥ 1 ����Ϊ����Ҫ�ų����ַ������������Ϊ 0 ������Ѿ��� dp �п��ǣ�
        cout << (dp[inputString.size()][stringSum] % MOD - 1 + MOD) % MOD << endl; // ʹ�� (x + MOD) % MOD ��ֹ����
    }

    return 0;
}
