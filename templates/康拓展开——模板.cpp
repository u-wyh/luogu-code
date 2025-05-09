// ����չ��
// ���ִ�1��n�������кܶ����У����������һ�����У�������е����Σ��𰸶� 998244353 ȡģ
// 1 <= n <= 10^6
// �������� : https://www.luogu.com.cn/problem/P5367
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1000001;
const int MOD = 998244353;

int arr[MAXN];
// �׳�������
int fac[MAXN];
// ��״����
int tree[MAXN];
int n;

//���²�������״�����������
int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //ÿһ�ζ������Լ����Ҳ��1
        //�൱�ڰ����а�����״̬�����ֶ�����
    }
}

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //ÿһ�ζ���ȥ�Լ����Ҳ��1
        //�൱�ڽ����������ֿ�Ϊ����С�������  �ͳ˷�����������
    }
    return ans;
}
//�����������Ǵ�1��i�������ֵĺ�

int query(int l,int r){
    return sum(r)-sum(l-1);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }

    fac[0]=1;
    for(int i=1;i<n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    //�����׳˱�

    for(int i=1;i<=n;i++){
        add(i,1);
    }
    //����״�����ʼ��
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+(fac[n-i]*sum(arr[i]-1))%MOD)%MOD;
        add(arr[i],-1);//����һλ����Ϣȥ��
    }
    ans=(ans+1)%MOD;
    cout<<ans<<endl;
    return 0;
}
