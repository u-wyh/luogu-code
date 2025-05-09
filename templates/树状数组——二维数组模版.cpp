// ��ά�����Ϸ�Χ���ӡ���Χ��ѯ��ʹ����״�����ģ��(java)
// �������� : https://www.luogu.com.cn/problem/P4514
// ����ʵ������ȷ�ģ��������ƽ̨�Կռ俨�ĺ��ϣ�ֻ��ʹ��C++��ȫ��ͨ��
// java�İ汾�����޷���ȫͨ���ģ��ռ�ᳬ�����ƣ���Ҫ��IO�ռ�ռ�ô�
// �������ƽ̨û���չ˸������Ե�ʵ�������µ�
// ���������ԡ�����ʱ��һ���Ǽ�˸������Եģ���ʵ����һ����ȷ��
// C++�汾����Code05_TwoDimensionIntervalAddIntervalQuery2�ļ�
// C++�汾��java�汾�߼���ȫһ������ֻ��C++�汾����ͨ�����в�������
//��Ҫ��ʽ�Ƶ�  Ҫ�ĸ���״����
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2050;
const int MAXM = 2050;

int info1[MAXN][MAXM], info2[MAXN][MAXM], info3[MAXN][MAXM], info4[MAXN][MAXM];
// ά����Ϣ :  d[i][j]   d[i][j]*i    d[i][j]*j    d[i][j]*i*j
int n, m;

int lowbit(int x){
    return x&-x;
}

//��������������ǽ�������״�����ֵ����һ��ֵ
void add(int x,int y,int v){
    int v1=v;
    int v2=v*x;
    int v3=v*y;
    int v4=v*x*y;
    //����ÿһ����״����  ÿһ�ε�����ֵ����һ����

    for(int i=x;i<=n;i+=lowbit(i)){
        //�������� ֻҪ����������
        for(int j=y;j<=m;j+=lowbit(j)){
            //�������� ֻҪ����������
            info1[i][j]+=v1;
            info2[i][j]+=v2;
            info3[i][j]+=v3;
            info4[i][j]+=v4;
        }
    }
}

//��������������Ǽ����(1,1)��(x,y)���ۼӺ�
//����ļ��㷽ʽ���Ƶ������Ľ��
int sum(int x,int y){
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            ans+=(x + 1) * (y + 1) * info1[i][j] - (y + 1) * info2[i][j] - (x + 1) * info3[i][j] + info4[i][j];
        }
    }
    return ans;
}

//��������������ǽ�һ������ȫ������һ��ֵ
//��������ά�����ǲ������  ��ά���   �Ӷ�ֻ��Ҫ���ĸ�λ�ø�һ�¾�����
void add(int a, int b, int c, int d, int v) {
    add(a, b, v);
    add(a, d + 1, -v);
    add(c + 1, b, -v);
    add(c + 1, d + 1, v);
}

int range(int a, int b, int c, int d) {
	return sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
}

int main()
{
    char op;
    cin>>op>>n>>m;
    int a,b,c,d,v;
    while(scanf("%c",&op)==1){
        if(op=='L'){
            cin>>a>>b>>c>>d>>v;
            add(a,b,c,d,v);
        }else if(op=='k'){
            cin>>a>>b>>c>>d;
            cout<<range(a,b,c,d)<<endl;
        }
    }
    return 0;
}
