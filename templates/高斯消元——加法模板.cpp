//���������ģ����
// ��˹��Ԫ����ӷ�������ģ��(�����Ƿ���Ψһ��)
// һ����n������������n���ӷ����̣�����һ���ӷ�������
// ������������ì�ܻ����޷�ȷ��Ψһ�⣬��ӡ"No Solution"
// ������������Ψһ�⣬��ӡÿ��������ֵ������С�������λ
// 1 <= n <= 100
// �������� : https://www.luogu.com.cn/problem/P3389
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
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

//������������������mat����Ľ�  n��x1 x2    xn
//����޽ⷵ��0  �нⷵ��1
int gauss(int n) {
    for (int i = 1; i <= n; i++) {
        //ÿ�����һ��xi  Ҳ�������յ�ֵ
        //ֻ�ǽ�����ʽ���е�xi��ϵ������Ϊ0
        //ֻ�����Լ���ϵ��  ���ս�ϵ����Ϊ1
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
        if (abs(mat[i][i]) < sml) {
            //��ʾxiΪ0  ��ô�������н���
            return 0;
        }
        if (abs(mat[i][i]) >= sml) {
            //��ȥ����ʽ���е�xi
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
    return 1;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            cin>>mat[i][j];
        }
    }
    if(gauss(n)==1){
        for(int i=1;i<=n;i++){
            printf("%.2lf\n",mat[i][n+1]);
        }
    }
    else{
        cout<<"No Solution"<<endl;
    }
    return 0;
}
