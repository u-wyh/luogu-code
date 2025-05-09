// ����ȫ���0�Ĳ�������
// ��һ��n*m�Ķ�ά���񣬸���ÿ������ĳ�ʼֵ��һ����0��1��2�е�һ��
// ���ĳ����������һЩ��ֵ�ӳɣ�Ҳ����%3�ķ�ʽ���0��1��2�е�һ��
// �����и�����һ��ʼֵ��1�����4�ļӳ�֮��ֵΪ(1+4)%3 = 2
// ��һ�������ˢ�ӣ�һ����ĳ������ˢһ�£����������2�ļӳ�
// ���Ҹ������ϡ��¡����ҵĸ��ӣ�������1�ļӳ�
// ����Ŀ�����������񶼱��0����Ŀ��֤һ���н⣬������֤Ψһ��
// �õ���һ�ַ��������ԣ���ӡһ����Ҫˢ���£����ҰѲ���������ӡ����
// 1 <= n��m <= 30
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=5755
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<iostream>
using namespace std;
const int MOD = 3;
const int MAXS = 1001;

int mat[MAXS][MAXS];
int dir[5] = { 0, -1, 0, 1, 0 };
int n, m, s;
int inv[MOD];

void compute_inv() {
    inv[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = (int) (MOD - (long) inv[MOD % i] * (MOD / i) % MOD);
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void swap(int a, int b) {
    int tmp[MAXS + 1];
    for (int j = 0; j <= n*m+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

void prepare() {
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= s + 1; j++) {
            mat[i][j] = 0;
        }
    }
    int cur, row, col;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cur = i * m + j + 1;
            mat[cur][cur] = 2;
            for (int d = 0; d <= 3; d++) {
                row = i + dir[d];
                col = j + dir[d + 1];
                if (row >= 0 && row < n && col >= 0 && col < m) {
                    mat[cur][row * m + col + 1] = 1;
                }
            }
        }
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
    // ���ڱ���������ԣ�����Ҫȥ���κ�����Ԫ��Ӱ��
    // �͵�����Ԫ��������ֱ������Ԫ�Ĳ�����������
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] != 0) {
            mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
        }
    }
}

int main()
{
    compute_inv();
    int test;
    cin>>test;
    while(test--){
        cin>>n>>m;
        s = n * m;
        prepare();
        for (int i = 1,k; i <= s; i++) {
            cin>>k;
            mat[i][s + 1] = (3 - k) % MOD;
        }
        gauss(s);
        int ans = 0;
        for (int i = 1; i <= s; i++) {
            ans += mat[i][s + 1];
        }
        cout<<ans<<endl;
        for (int i = 1, id = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++, id++) {
                while (mat[id][s + 1]-- > 0) {
                    cout<<i << " " << j<<endl;
                }
            }
        }
    }
    return 0;
}
