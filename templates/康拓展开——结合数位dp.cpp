//P2518
//�����Ĺ�˼������ �Ϳ���չ����ϵ��һ�����Ȥ
//����������λdp  ���ǿ��Խ�0����ǰ�� �͵���ǰ��0
//Ȼ��ͳ���ж����ַ����Ǻ����
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 55;//����ᳬ��50λ

int n;
int arr[10];//�������ֵ�ͳ��
int C[MAXN][MAXN];
int val[MAXN];//��ʼʱ��λ���ϵ�����

int c(int a,int b){
    if(C[a][b]){
        return C[a][b];
    }
    int ans=1;
    for(int i=1;i<=min(b,a-b);i++){
        ans*=(a-i+1);
        ans/=i;
    }
    C[a][b]=ans;
    return ans;
}

int compute(){
    int m=n;//��ʾ��m��λ�ÿ���������
    int ans=1;
    for(int i=0;i<=9;i++){
        if(arr[i]){
            ans*=c(m,arr[i]);
            m-=arr[i];//�������λ�ü���
        }
    }
    return ans;
}

signed main()
{
    char c;
    // ��ȡ���벢ͳ��ÿ�����ֵĳ��ִ���
    while (cin >> c) {
        if (isdigit(c)) {
            val[++n] = c - '0'; // ���ַ�ת��Ϊ����
            arr[val[n]]++; // ͳ�����ֳ��ִ���
        }
    }
    int ans=0;
    int len=n;//���ݳ���
    for(int i=1;i<=len;i++){
        n--;//��ʾʣ��λ�ü���
        for(int j=0;j<val[i];j++){
            if(arr[j]){
                arr[j]--;//��ʾ��λ����j  ��ôʣ�µ�λ�þͿ�������ѡ����
                ans+=compute();
                arr[j]++;
            }
        }
        arr[val[i]]--;//��ʾ��ԭ��һ��  ��ʣ�µ����ݲ������ѡ
    }
    cout<<ans<<endl;
    return 0;
}
