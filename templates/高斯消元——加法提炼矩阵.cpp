//�����Ҫ�Լ�����һ�µõ�mat����
// ���οռ�����ĵ�
// �����nά�ռ��У���ô���һ�����λ�ã���Ҫn�������ֵ
// ���ڸ���n+1���㣬ÿ���㶼��n�������ֵ��������nά�ռ��е�λ��
// ������n+1���㶼��nά�ռ�������ϣ��뷵�����ĵ�λ��
// ���ĵ�λ�õ�ȻҲ��n�������ֵ����ӡ����
// ��nά�ռ��У�������������ľ��룬���þ����ŷʽ����
// 1 <= n <= 10
// ������Ϣ��ȷ��С�����6λ������ֵ��������20000
// �������� : https://www.luogu.com.cn/problem/P4035
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//�������Ҫ�Լ�����ʽ��  ��������������� x1 x2 x3 ... xn
//��ô(a1-x1)^2+(a2-xn)^2+...+(an-xn)^2=(b1-x1)^2+(b2-xn)^2+...+(bn-xn)^2
//����Щʽ��չ�� ��xi�ĺϲ���һ�� ����������ұ� ���ɵõ�����Ҫ��ľ���
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 12;
// 0.0000001 == 1e-7
// ��Ϊdouble�����о������⣬������Ϊ
// ���һ�����־���ֵ  <  sml������Ϊ��������0
// ���һ�����־���ֵ  >= sml������Ϊ�����ֲ���0
const double sml = 1e-7;

int n;
double mat[MAXN][MAXN + 1];

void swap(int a, int b) {
    //swap�����������ڽ������������ĳһ��
    //ʹ��ϵͳ�����ú�������  ����ʱ����΢��һ��
    //�ڳ����� ����ȫ����д
    //������д��ʱ��һ��Ҫע���м�����tmp��������int ���� double
    //������д��ʱ��һ��Ҫע���еķ�Χ  ����ȱ��
    double tmp[MAXN + 1];
    for (int j = 0; j <= n+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        int max = i;
        for (int j = 1; j <= n; j++) {
            if (j < i && abs(mat[j][j]) >= sml) {
                continue;
            }
            if (abs(mat[j][i]) > abs(mat[max][i])) {
                max = j;
            }
        }
        swap(i, max);//�����������ֵ
        if (abs(mat[i][i]) >= sml) {
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++) {
                mat[i][j] /= tmp;
            }
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}

int main()
{
    cin>>n;
    double data[12][12];
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++) {
            cin>>data[i][j];
        }
    }
    //�������Ҫ�Լ���������ʽ
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mat[i][j] = 2 * (data[i][j] - data[i + 1][j]);
            mat[i][n + 1] += data[i][j] * data[i][j] - data[i + 1][j] * data[i + 1][j];
        }
    }
    gauss(n);
    for (int i = 1; i <= n; i++) {
        printf("%.3f ", mat[i][n + 1]);
    }
    return 0;
}
