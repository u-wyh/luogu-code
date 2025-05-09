#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ���Ͻ�����˹��Ԫ���ͬ�෽���������

const int MOD = 7;
const int MAXN = 101;
vector<vector<int>> mat(MAXN, vector<int>(MAXN + 1));
vector<int> inv(MOD);
//��������Ԫ����ֱ��������Ԫ��  ��������һЩ���Ҫʹ�õ����������ֵ���Ԫ
//������Ҳ�ṩ�˷���С��������Ԫ�ĺ���  �����ڽ��ֻ��Ҫ�������ֵ���Ԫ
//��Ԫ���������Ϊ�˵õ����յĴ�

// �������㷨
long long power(long long num, long long pow, long long mod) {
    long long ans = 1;
    while (pow > 0) {
        if (pow % 2 == 1) {
            ans = (ans * num) % mod;
        }
        num = (num * num) % mod;
        pow /= 2;
    }
    return ans;
}

// ����С���������Ԫ
long long fermat(long long num, long long mod) {
    return power(num, mod - 2, mod);
}

// ��Ԫ���Ե��ƹ�ʽ����Ԫ������099 - ����ͬ��
void compute_inv() {
    inv[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = MOD - (long long)inv[MOD % i] * (MOD / i) % MOD;
    }
}

// ��a��b�����Լ������֤a��b��������0
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void swap(int a, int b) {
    int tmp[MAXN + 1];
    //cout<<"swap"<<endl;
    for (int j = 0; j <= MAXN; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

// ��˹��Ԫ���ͬ�෽����ģ�棬��֤��ʼϵ��û�и���
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // �Ѿ���Ϊ��Ԫ���в�����
            if (j < i && mat[j][j] != 0) {
                continue;
            }
            // �ҵ�ϵ��������0��������Ԫ����
            if (mat[j][i] != 0) {
                swap(i,j);
                break;
            }
        }
        if (mat[i][i] != 0) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] != 0) {
                    //���ĳһ�е����λ��ϵ������0  ��ôû��Ҫ��
                    int gcd_val = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / gcd_val;
                    int b = mat[j][i] / gcd_val;
                    if (j < i && mat[j][j] != 0) {
                        // ���j������Ԫ����ô��j�е�i-1�е�����ϵ�� * a
                        // ��ȷ������Ԫ������Ԫ֮��Ĺ�ϵ
                        for (int k = j; k < i; k++) {
                            mat[j][k] = (mat[j][k] * a) % MOD;
                        }
                    }
                    // ������Ԫ
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % MOD + MOD) % MOD;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] != 0) {
            // ��鵱ǰ��Ԫ�Ƿ���������ԪӰ��
            // �����ǰ��Ԫ��������ԪӰ�죬��ô����ȷ����ǰ��Ԫ��ֵ
            // ����������Ӱ�죬��ȷ��ʾ��Ԫ������Ԫ�Ĺ�ϵ
            bool flag = false;
            for (int j = i + 1; j <= n; j++) {
                if (mat[i][j] != 0) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                //�����ʾ��Ԫ��������ԪӰ��  ����ֱ���������ͬ��ֵ
                // ��ģ������Ӧ������Ԫ��(a / b) % MOD = (a * b����Ԫ) % MOD
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}

void print(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "========================" << endl;
}

int main() {
    // ��Ԫ������
    compute_inv();
    cout << "����ͼ������ӣ�Ψһ��" << endl;
    // 4*x1 + 2*x2 + 4*x3 ͬ�� 3
    // 2*x1 + 5*x2 + 2*x3 ͬ�� 2
    // 6*x1 + 3*x2 + 4*x3 ͬ�� 5
    mat[1][1] = 4; mat[1][2] = 2; mat[1][3] = 4; mat[1][4] = 3;
    mat[2][1] = 2; mat[2][2] = 5; mat[2][3] = 2; mat[2][4] = 2;
    mat[3][1] = 6; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 5;
    gauss(3);
    print(3);

    cout << "���ʽ����ì�ܵ�����" << endl;
    // 1*x1 + 2*x2 + 3*x3 ͬ�� 2
    // 2*x1 + 4*x2 + 6*x3 ͬ�� 5
    // 0*x1 + 3*x2 + 4*x3 ͬ�� 2
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = 3; mat[1][4] = 2;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = 6; mat[2][4] = 5;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 2;
    gauss(3);
    print(3);

    cout << "����ͼ������ӣ����" << endl;
    cout << "ֻ��ȷ��������Ԫ������ȷ����Ԫ��ֵ" << endl;
    cout << "����Ƕ����������ô����Ԫ������" << endl;
    cout << "��ά��������Ԫ������Ԫ�Ĺ�ϵ����ȷ��" << endl;
    cout << "����Ҳ��������֤" << endl;
    // 1*x1 + 2*x2 + 3*x3 ͬ�� 2
    // 2*x1 + 4*x2 + 6*x3 ͬ�� 4
    // 0*x1 + 3*x2 + 4*x3 ͬ�� 2
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = 3; mat[1][4] = 2;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = 6; mat[2][4] = 4;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 2;
    gauss(3);
    print(3);

    cout << "ע�����������������" << endl;
    // 1*x1 + 1*x2 + 1*x3 ͬ�� 3
    // 2*x1 + 1*x2 + 1*x3 ͬ�� 5
    // 0*x1 + 3*x2 + 3*x3 ͬ�� 3
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 3;
    mat[2][1] = 2; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 5;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 3; mat[3][4] = 3;
    gauss(3);
    print(3);
    cout << "���һ��������" << endl;
    cout << "��Ԫx1��������������ԪӰ�죬ֵ����ֱ��ȷ��" << endl;
    cout << "ֻ������Ԫx3ȷ����ֵ����Ԫx2��ֵ����ȷ����" << endl;
    cout << "���ڿ��ṩ��ģ�棬�������������Ԫ���Եõ���ȷ���" << endl;
    cout << "���ڲ����������Ԫ����ģ��Ҳ�ܸ�������Ԫ������Ԫ����ȷ��ϵ" << endl;
    cout << "��Щ��Ŀ��Ҫ���ֶ������£���Ԫ������Ԫ֮�����ȷ��ϵ" << endl;
    cout << "�������ģ��ͽ��ⶼû�п����������ֵ����������" << endl;
    cout << "�����Щ��Ŀ����Ҫ������ȷ��ϵ" << endl;
    cout << "��ô�߼����Ի����ó���ʱ����죬���籾�ڿε���Ŀ1" << endl;
    return 0;
}
