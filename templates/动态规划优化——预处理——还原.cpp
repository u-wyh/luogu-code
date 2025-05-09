// ��ԭ����ķ�����(�Ż�ö��)
// ԭ����һ������Ϊn������arr���±��1��ʼ�������ж���<=200������
// ��������iλ�õ����ֶ����� : arr[i] <= max(arr[i-1], arr[i+1])
// �ر�ģ�arr[1] <= arr[2]��arr[n] <= arr[n-1]
// ���������arr����Щ���ֶ�ʧ�ˣ���ʧ��������0��ʾ
// ���ػ�ԭ�ɲ�Υ���arr�ж����ַ������𰸶� 998244353 ȡģ
// 3 <= n <= 10^4
// �������� : https://www.nowcoder.com/practice/49c5284278974cbda474ec13d8bd86a9
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//����Ԥ����ʽ�Ǽ���ö�ٹ���  ����  ���Ҫ�����������һ���״̬ ��ô������ǰ׺��  �Ӷ����ñ����ķ�ʽ  ʵ�ּ���
//������dp[i][j][k]��˼�� ǰi��������Ҫ��ԭ(������ķ�Χ��1~i) �Ҳ��Ѿ�ȫ��ȷ��  i+1λ�õ�������j  
//k��0 ���ʾ s[i+1]>[i+2]  �������С�ڵ���
//��ô���մ𰸾���dp[n][0][1]  ��Ҫ�������ǰn��λ��  ���һ��λ��n�϶�Ҫ��n+1��   ��ô��n+1����Ϊ0
//���ǽ�n+2>n+1  ��ʾ�������ﲻ��Ҫʹ��ǰn���������n+1λ�õ���
//�����һ��λ���ϵ�������v  ��ô���λ�ò�����һ��s��ʲô һ��������v+1~m   
//��Ϊ���s��0  ��ʾi+1>i+2  ����i+1<max(i+2,i)  ����v+1~m����   ���s��1  ��ô˵��i+1λ���Ѿ���������  ��ô���λ�ÿ��������
//������λ��������v  Ҳ��ͬ����  ��������Ҫע�����v������0  ��Ϊһ��ʼ���ǵ��õ���dp[n][0][1]
//��������볢��С��v������ ��ôs����Ҫ��1  ����  i+1>i&&i+1>i+2
//��ôdp[i][j][0/1] = dp[i-1][j+1~m][0]  ��˼��i-1���λ���ϴ���i�ķ���
//���j!=0  dp[i][j][0/1] += dp[i-1][v][1]
//���s��1  ��ô +dp[i-1][1~j-1][1]
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
const int MOD = 998244353;
const int MAXN = 10000;
const int M = 200;

int arr[MAXN + 1];
int n;
int memo[M + 1][2];
int dp[M + 1][2];
int suf0[M + 1];//0�к�׺��
int pre1[M + 1];//1��ǰ׺��

void prepare() {
    suf0[M] = memo[M][0];
    for (int v = M - 1; v >= 0; --v) {
        suf0[v] = (suf0[v + 1] + memo[v][0]) % MOD;
    }
    pre1[1] = memo[1][1];
    for (int v = 2; v <= M; ++v) {
        pre1[v] = (pre1[v - 1] + memo[v][1]) % MOD;
    }
}

int compute() {
    for (int v = 0; v <= M; ++v) {
        memo[v][0] = 0;
        memo[v][1] = 1;//��������  ״̬ѹ��
    }
    for (int i = 1; i <= n; ++i) {
        prepare();
        for (int v = 0; v <= M; ++v) {
            for (int s = 0; s <= 1; ++s) {
                int ans = 0;
                if (arr[i] != 0) {
                    //������ֵ�ǹ̶�ֵ ��ôûʲô��˵��  ֱ�Ӿ�����
                    if (arr[i] >= v || s == 1) {
                        ans = memo[arr[i]][arr[i] > v ? 0 : 1];
                    }
                } else {
                    if (v + 1 <= M) {
                        ans = (ans + suf0[v + 1]) % MOD;
                    }
                    if (v != 0) {
                        ans = (ans + memo[v][1]) % MOD;
                    }
                    if (s == 1) {
                        if (v - 1 >= 0) {
                            ans = (ans + pre1[v - 1]) % MOD;
                        }
                    }
                }
                dp[v][s] = ans;
            }
        }
        for (int v = 0; v <= M; ++v) {
            for (int s = 0; s <= 1; ++s) {
                swap(memo[v][s], dp[v][s]);
            }
        }
    }
    return memo[0][1];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}
