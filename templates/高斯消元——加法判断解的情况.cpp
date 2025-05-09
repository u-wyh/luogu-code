//���������ģ����
// ��˹��Ԫ����ӷ�������ģ��(����ì�ܡ���⡢Ψһ��)
// һ����n������������n���ӷ����̣�����һ���ӷ�������
// ������������ì�ܣ���ӡ-1
// ����������޷�ȷ��Ψһ�⣬��ӡ0
// ������������Ψһ�⣬��ӡÿ��������ֵ������С�������λ
// 1 <= n <= 50
// �������� : https://www.luogu.com.cn/problem/P2455
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include <iostream>
#include <cmath>
#include <iomanip>  // for std::setprecision
using namespace std;

const int MAXN = 101;
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

int main() {
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            cin>>mat[i][j];
        }
    }
    gauss(n);
    int sign = 1;
    for (int i = 1; i <= n; i++) {
        if (abs(mat[i][i]) < sml && abs(mat[i][n + 1]) >= sml) {
            //ì�ܿ������Ϊû����Ԫ  �����н��
            sign = -1;
            break;
        }
        if (abs(mat[i][i]) < sml) {
            //���������Ϊ������Ԫ  ���Ϊ0  ��Ϊû�н��s
            sign = 0;
        }
    }
    if (sign == 1) {
        for (int i = 1; i <= n; i++) {
            printf("x%d=%.2lf\n",i, mat[i][n + 1]);
        }
    } else {
        cout<<sign<<endl;
    }
    return 0;
}
