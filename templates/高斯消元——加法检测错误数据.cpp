//�����˾����е�һ���ֹ�ϵ  ��Ҫ�Լ�����ʣ�µĹ�ϵ
// ��һ�δ��������������Ʒ
// һ����n����Ʒ�����1~n������Ϸ��������£�
// 1��ÿ����Ʒ����������ȷ����
// 2��ÿ����Ʒ������һ������������
// 3�����ص���Ʒ���ҽ���1��
// ÿ�γ��ظ�ʽ���ƣ�3 2 5 6 10�������γ�����3����Ʒ�����Ϊ2��5��6��������10
// һ����n+1���������ݣ���������������Ч������Ϊ��
// ����ĳ����������ҽ���1����ֻ���ų�����������أ��������һ�ֺϷ�����
// �������������Ч����ӡ���������εı��
// �������������Ч����ӡ"illegal"
// 1 <= m <= n <= 100
// �������� : https://www.luogu.com.cn/problem/P5027
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 102;
// 0.0000001 == 1e-7
// ��Ϊdouble�����о������⣬������Ϊ
// ���һ�����־���ֵ  <  sml������Ϊ��������0
// ���һ�����־���ֵ  >= sml������Ϊ�����ֲ���0
const double sml = 1e-7;

int n;
int data[MAXN][MAXN];
double mat[MAXN][MAXN + 1];

//swap�����������ڽ������������ĳһ��
//ʹ��ϵͳ�����ú�������  ����ʱ����΢��һ��
//�ڳ����� ����ȫ����д
//������д��ʱ��һ��Ҫע���м�����tmp��������int ���� double
//������д��ʱ��һ��Ҫע���еķ�Χ  ����ȱ��
void swap(int a, int b) {
    double tmp[MAXN + 1];
    for (int j = 1; j <= n+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

void swapdata(int a, int b) {
    int tmp[MAXN + 1];
    for (int j = 1; j <= n+1; j++) {
        tmp[j] = data[a][j];
        data[a][j] = data[b][j];
        data[b][j] = tmp[j];
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

//�жϵõ��Ĵ��Ƿ�Ϸ�
int check() {
    gauss(n);
    double maxv = 0;
    int maxt = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] == 0) {
            return 0;
        }
        if (mat[i][n + 1] <= 0 || mat[i][n + 1] != (int) mat[i][n + 1]) {
            return 0;
        }
        if (maxv < mat[i][n + 1]) {
            maxv = mat[i][n + 1];
            maxt = 1;
            ans = i;
        } else if (maxv == mat[i][n + 1]) {
            maxt++;
        }
    }
    if (maxt > 1) {
        return 0;
    }
    return ans;
}

int main() {
    cin>>n;
    for (int i = 1, m; i <= n + 1; i++) {
        cin>>m;
        for (int j = 1, cur; j <= m; j++) {
            cin>>cur;
            data[i][cur] = 1;
        }
        cin>>data[i][n + 1];
    }
    int ans = 0;
    int times = 0;//times��ʾ�ж��ٸ���Ϣ��Ϊ��Ч��Ϣʱ���Եõ�����ĳ���
    for (int k = 1; k <= n + 1; k++) {
        swapdata(k, n + 1);//ö��ÿһ����Ϣ��Ϊ��Ч��Ϣ
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n + 1; j++) {
                mat[i][j] = data[i][j];
            }
        }
        swapdata(k, n + 1);
        int cur = check();
        if (cur != 0) {
            times++;
            ans = cur;
        }
    }
    if (times != 1) {
        //���������ֲ���1  ��ô�Ͳ���
        cout<<"illegal"<<endl;
    } else {
        cout<<ans<<endl;
    }
    return 0;
}

