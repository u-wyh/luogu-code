// ��˹��Ԫ�����򷽳���ģ����
// ��һ������Ϊn������arr���������ظ�ֵ�����ֶ���long���͵�����
// ÿ����ӵ�е���������һ��������2000��ÿ���������ѡһ��
// ������Ҫѡһ����������£������������ѡ���ֳ�����
// �˵õĽ����Ҫ����ȫƽ�����������м�����ѡ���ֵķ���
// ���������ܴܺ󣬴𰸶� 1000000007 ȡģ
// 1 <= n <= 300
// 1 <= arr[i] <= 10^18
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=5833
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//������˼·�Ǻ������
//���һ����������ȫƽ���� ��ô���������������ӵĸ�������ż��
//��ô���ǿ��Խ��������ֵ���������չ�� ����Ϊ1  ż��Ϊ0
//���ͳ������Ԫ  ��ô���������� 2������Ԫ���� -1
//����Ϊ�������е�����Ԫ����ѡ �������е���ԪҲ����0  Ҳ��������Ԫ����0��
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MOD = 1000000007;
const int MAXV = 2000;
const int MAXN = 305;

long long arr[MAXN];
int mat[MAXN][MAXN];
int prime[MAXV + 1];//�õ�2000�������е�����
int cnt = 0;
bool visit[MAXV + 1];
int pow2[MAXN];
int n;

void prepare() {
    // �õ�2000���ڵ�����
    for (int i = 2; i * i <= MAXV; i++) {
        if (!visit[i]) {
            for (int j = i * i; j <= MAXV; j += i) {
                visit[j] = true;
            }
        }
    }
    for (int i = 2; i <= MAXV; i++) {
        if (!visit[i]) {
            prime[++cnt] = i;
        }
    }
    // 2��i�η�%MOD�Ľ��
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
}

void swap(int a, int b) {
    int tmp[MAXN + 1];
    for (int j = 0; j <= n+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

//��˹��Ԫ
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i && mat[j][j] == 1) {
                continue;
            }
            if (mat[j][i] == 1) {
                swap(i,j);
                break;
            }
        }
        if (mat[i][i] == 1) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] == 1) {
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

int compute() {
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= cnt + 1; j++) {
            mat[i][j] = 0;
        }
    }
    long long cur;
    for (int i = 1; i <= n; i++) {
        cur = arr[i];
        for (int j = 1; j <= cnt && cur != 0; j++) {
            while (cur % prime[j] == 0) {
                mat[j][i] ^= 1;
                cur /= prime[j];
            }
        }
    }
    //��ʵԪ������ʵ����n  ���������ĸ�����������303  ��Ϊ2000���ھ�����ô�������
    //��ôʵ��Ԫ���������ܱ��õ�������������  ���ǲ�������Ԫ  ��xi
    //����ͳ������Ԫ
    gauss(cnt);
    int main_count = 0; // ��Ԫ������
    for (int i = 1; i <= cnt; i++) {
        if (mat[i][i] == 1) {
            main_count++;
        }
    }
    // ����Ԫ������ n - main_count
    // 2��(n - main_count)�η��־��� - 1
    return pow2[n - main_count] - 1 ;
}

int main() {
    prepare();
    int test;
    cin >> test;
    for (int t = 1; t <= test; t++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        cout << "Case #" << t << ":" << endl;
        cout << compute() << endl;
    }
    return 0;
}
