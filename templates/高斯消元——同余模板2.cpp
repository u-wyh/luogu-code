// ���߹���
// һ����n�ֹ��ߣ����1~n��һ����m����¼������һ����¼��ʽ���£�
// 4 WED SUN 13 18 1 13
// ��ʾ�и�����һ���ӹ���4�����ߣ���ĳ����������ʼ��������ĳ���������������
// �ӹ��Ĺ�������Ϊ13�š�18�š�1�š�13��
// ÿ�������ڹ����ڼ䲻��Ϣ��ÿ�����߶��Ǵ��мӹ��ģ����һ����ſ�ʼ��һ��
// ÿ�ֹ������������ǹ̶��ģ������κι��ߵ�������������3�졢���9��
// �������ݶ�ʧ�ˣ�����������Ҫ���ݼ�¼���ƶϳ�ÿ�ֹ��ߵ���������
// �����¼֮�����ì�ܣ���ӡ"Inconsistent data."
// �����¼�޷�ȷ��ÿ�ֹ��ߵ�������������ӡ"Multiple solutions."
// �����¼�ܹ�ȷ��ÿ�ֹ��ߵ�������������ӡ���н��
// 1 <= n��m <= 300
// �������� : http://poj.org/problem?id=2947
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MOD = 7;
const int MAXN = 302;

int mat[MAXN][MAXN];
int inv[MOD];
string days[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };
int n, m, s;


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
    int tmp[MAXN + 1];
    for (int j = 0; j <= max(n,m)+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

int day(string str) {
    for (int i = 0; i < 7; i++) {
        if (str==days[i]) {
            return i;
        }
    }
    return -1;
}

void prepare() {
	for (int i = 1; i <= s; i++) {
		for (int j = 1; j <= s + 1; j++) {
			mat[i][j] = 0;
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
                // ��ģ������Ӧ������Ԫ��(a / b) % MOD = (a * b����Ԫ) % MOD
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}

int main()
{
    compute_inv();
    cin>>n>>m;
    while (n != 0 && m != 0) {
        s = max(n, m);
        prepare();
        for (int i = 1; i <= m; i++) {
            int k ;
            string st,et;
            cin>>k;
            cin>>st>>et;
            for (int j = 1; j <= k; j++) {
                int tool ;
                cin>>tool;
                mat[i][tool] = (mat[i][tool] + 1) % MOD;
            }
            mat[i][s + 1] = ((day(et) - day(st) + 1) % MOD + MOD) % MOD;
        }
        gauss(s);
        int sign = 1;
        for (int i = 1; i <= s; i++) {
            if (mat[i][i] == 0 && mat[i][s + 1] != 0) {
                sign = -1;
                break;
            }
            if (i <= n && mat[i][i] == 0) {
                sign = 0;
            }
        }
        if (sign == -1) {
            cout<<"Inconsistent data."<<endl<<endl;
        } else if (sign == 0) {
            cout<<"Multiple solutions."<<endl<<endl;
        } else {
            for (int i = 1; i <= n; i++) {
                if (mat[i][s + 1] < 3) {
                    mat[i][s + 1] += 7;
                }
            }
            for (int i = 1; i < n; i++) {
                cout<<mat[i][s + 1] << " ";
            }
            cout<<mat[n][s + 1]<<endl<<endl;
        }
        // ��һ��n��m
        cin>>n>>m;
    }
    return 0;
}
