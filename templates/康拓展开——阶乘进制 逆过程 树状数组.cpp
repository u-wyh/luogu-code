// �濵��չ��   ���ּ���״����
// ���ִ�1��n�������кܶ����У�����һ������Ϊn������s����ʾ�����һ������
// ���������е���������Ϊx����ӡ��x+m����������ʲô
// 1 <= n <= 10^5
// 1 <= m <= 10^15
// ��Ŀ��֤s��һ����1~n������ɵ���ȷ���У���Ŀ��֤x+m���ᳬ�����е�����
// �������� : https://www.luogu.com.cn/problem/U72177
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long long arr[MAXN],tmp[MAXN];
int tree[MAXN];
int n;
long long m;

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

//ͨ�����ַ��õ���
int solve(int x){
    int l=1,r=n,ans;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sum(mid)>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    add(ans,-1);
    return ans;
}

void compute(){
    //��ʼ����״����
    for(int i=1;i<=n;i++){
        add(i,1);
    }
    // ��ǰ����ת��Ϊ�׳˽��Ƶ�����
    for (int i = 1, x; i <= n; i++) {
        x = (int) arr[i];
        if (x == 1) {
            arr[i] = 0;
        } else {
            arr[i] = sum(x - 1);
        }
        //arr�����ʾһ��ʼ�������ڽ׳˽����µ�����
        add(x, -1);
        //����������ֵ�Ӱ��
    }
    // ��ǰ��������m֮�󣬵õ��µ��������ý׳˽��Ʊ�ʾ
    arr[n] += m; // ���λ������ӵķ���
    for (int i = n; i >= 1; i--) {
        // ���Ͻ�λ����
        arr[i - 1] += arr[i] / (n - i + 1);
        // ��ǰλ�Ƕ���
        arr[i] %= n - i + 1;
    }
    //������ʱ  arr���������Ǽ���m��������ڽ׳˽����µı�ʾ
    // ���ݽ׳˽���ת��Ϊ���������
    for(int i=1;i<=n;i++){
        add(tmp[i],1);
    }
    //����״�������¸�ԭ
    for (int i = 1; i <= n; i++) {
        arr[i] = solve((int) arr[i] + 1);
        //��ʱ���arr���������������
    }
}

int main()
{
    cin>>n>>m;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
        tmp[i]=arr[i];
    }
    compute();
    for (int i = 1; i <= n; i++) {
        cout<<arr[i] <<" ";
    }
    return 0;
}
