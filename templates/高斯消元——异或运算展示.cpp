#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 101;

vector<vector<int>> mat(MAXN, vector<int>(MAXN + 1, 0));
//��ʵ��  ����һ���þ�̬��   �˶δ�����ai����

// ע�⣺����Ϊ�˼򻯣�����ֱ�ӽ���������������������������������
// ��Ҫ�ں����ⶨ��һ������������������������vector<int>
void swap(int a, int b) {
    cout<<"swap"<<endl;
    vector<int> tmp = mat[a];
    mat[a] = mat[b];
    mat[b] = tmp;
}

// ��˹��Ԫ�����򷽳���ģ��
// ��Ҫ��֤������n�������ʽҲ��n��
void gauss(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i && mat[j][j] == 1) {
                continue;
            }
            if (mat[j][i] == 1) {
                //�������  Ҫô��0Ҫô��1  �����ҵ�1�Ϳ��Խ�����
                swap(i, j);
                break;
            }
        }
        if (mat[i][i] == 1) {
            for (int j = 0; j < n; j++) {
                if (i != j && mat[j][i] == 1) {
                    for (int k = i; k <= n; k++) {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

void print(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "========================" << endl;
}

int main() {
    cout << "����ͼ������ӣ���Ψһ��" << endl;
    // x1 ^ x2 ^ x3 = 0
    // x1 ^ x3 ^ x4 = 1
    // x2 ^ x3 ^ x4 = 1
    // x3 ^ x4 = 0
    mat[0][0] = 1; mat[0][1] = 1; mat[0][2] = 1; mat[0][3] = 0; mat[0][4] = 0;
    mat[1][0] = 1; mat[1][1] = 0; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 1;
    mat[2][0] = 0; mat[2][1] = 1; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 1;
    mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 1; mat[3][3] = 1; mat[3][4] = 0;
    gauss(4);
    print(4);

    cout << "���ʽ����ì�ܵ�����" << endl;
    // x1 ^ x2 = 1
    // x1 ^ x3 = 1
    // x2 ^ x3 = 1
    mat[0][0] = 1; mat[0][1] = 1; mat[0][2] = 0; mat[0][3] = 1;
    mat[1][0] = 1; mat[1][1] = 0; mat[1][2] = 1; mat[1][3] = 1;
    mat[2][0] = 0; mat[2][1] = 1; mat[2][2] = 1; mat[2][3] = 1;
    gauss(3);
    print(3);

    cout << "���ʽ���ڶ�������" << endl;
    // x1 ^ x3 = 1
    // x2 ^ x3 = 1
    // x1 ^ x2 = 0
    mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 1; mat[0][3] = 1;
    mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1;
    mat[2][0] = 1; mat[2][1] = 1; mat[2][2] = 0; mat[2][3] = 0;
    // ע�⣺���������C++��Ӧ����Ȼʹ��3������������ȥ���������
    // mat[3][0] = 1; mat[3][1] = 1; mat[3][2] = 0; mat[3][3] = 0; // ���в�Ӧ�ô���
    gauss(3);
    print(3);

    cout << "ע�����������������" << endl;
    // x1 ^ x3 ^ x4 = 0
    // x2 ^ x3 ^ x4 = 0
    // x1 ^ x2 = 0
    // x3 ^ x4 = 1
    mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 1; mat[0][3] = 1; mat[0][4] = 0;
    mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 0;
    mat[2][0] = 1; mat[2][1] = 1; mat[2][2] = 0; mat[2][3] = 0; mat[2][4] = 0;
    mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 1; mat[3][3] = 1; mat[3][4] = 1;
    gauss(4);
    print(4);
    cout << "���һ��������" << endl;
    cout << "��Ԫx1��x2��������������ԪӰ�죬ֵ����ֱ��ȷ��" << endl;
    cout << "������Ԫx3���ܵ�����Ԫx4��Ӱ�죬x3 ^ x4 = 1" << endl;
    cout << "ֻ������Ԫx4ȷ����ֵ����Ԫx3��ֵ����ȷ��" << endl;
    cout << "��������˵����Ԫ��ɺ���������Ƕ�⣬��ô" << endl;
    cout << "��Щ��Ԫ��ֵ����ֱ��ȷ��" << endl;
    cout << "��Щ��Ԫ��ֵ��Ҫ��������Ԫȷ��֮�����ȷ��" << endl;
    cout << "������Ͻڿν�������ݣ�" << endl;
    cout << "��Ԫ������Ԫ֮���������ϵ" << endl;
    cout << "��ȷ���Ѿ�����" << endl;

    return 0;
}
