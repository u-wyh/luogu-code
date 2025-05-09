// ����ʯͷ�İ�ʲ����
// ������ʯͷ�������ֱ�Ϊa��b
// �����������ã�ÿ�ο���ѡ������һ��ʯͷ����1~m��
// �õ����һ��ʯ�ӵ��˻�ʤ������a��b��m����˭Ӯ
// ������ʵ�󳧱��ԣ�û�����߲��ԣ���������֤
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAXN = 101;

string dp[MAXN][MAXN][MAXN];

// ��̬�滮�������׳���
// Ϊ����֤
string win1(int a, int b, int m) {
    if (m >= max(a, b)) {
        return a != b ? "����" : "����";
    }
    if (a == b) {
        return "����";
    }
    if (!dp[a][b][m].empty()) {
        return dp[a][b][m];
    }
    string ans = "����";
    for (int pick = 1; pick <= min(a, m); pick++) {
        if (win1(a - pick, b, m) == "����") {
            // �������̵�Ӯ���Ǻ������̵ĺ���
            // �Ǿͱ�ʾ��ʱ�����֣�ͨ������������̣���Ӯ
            ans = "����";
        }
        if (ans == "����") {
            // �������̵�Ӯ���Ǻ������̵ĺ���
            // �Ǿͱ�ʾ��ʱ�����֣�ͨ������������̣���Ӯ
            break;
        }
    }
    for (int pick = 1; pick <= min(b, m); pick++) {
        if (win1(a, b - pick, m) == "����") {
            // �������̵�Ӯ���Ǻ������̵ĺ���
            // �Ǿͱ�ʾ��ʱ�����֣�ͨ������������̣���Ӯ
            ans = "����";
        }
        if (ans == "����") {
            break;
        }
    }
    dp[a][b][m] = ans;
    return ans;
}

// sg����
string win2(int a, int b, int m) {
    int n = max(a, b);
    vector<int> sg(n + 1, 0);
    vector<bool> appear(m + 1, false);
    for (int i = 1; i <= n; i++) {
        fill(appear.begin(), appear.end(), false);
        for (int j = 1; j <= m && i - j >= 0; j++) {
            appear[sg[i - j]] = true;
        }
        for (int s = 0; s <= m; s++) {
            if (!appear[s]) {
                sg[i] = s;
                break;
            }
        }
    }
    return (sg[a] ^ sg[b]) != 0 ? "����" : "����";
}

// ʱ�临�Ӷ�O(1)�����Ž�
// ��ʵ�Ǹ��ݷ���2�е�sg��۲������
string win3(int a, int b, int m) {
    return a % (m + 1) != b % (m + 1) ? "����" : "����";
}

int main() {
    cout << "���Կ�ʼ" << endl;
    int cnt=0;
    for (int a = 0; a < MAXN; a++) {
        for (int b = 0; b < MAXN; b++) {
            for (int m = 1; m < MAXN; m++) {
                cnt++;
                string ans1 = win1(a, b, m);
                string ans2 = win2(a, b, m);
                string ans3 = win3(a, b, m);
                if (ans1 != ans2 || ans1 != ans3) {
                    cout << "�����ˣ�" << endl;
                }
                else{
                    cout<<"�� "<<setw(3)<<cnt<<" ����ͨ��"<<endl;
                }
            }
        }
    }
    cout << "���Խ���" << endl;
    return 0;
}
