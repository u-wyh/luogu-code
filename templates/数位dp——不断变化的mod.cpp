//P2147
#include<bits/stdc++.h>
using namespace std;

long long l,r;
long long f[20][200][200];
int len;
int arr[20];
int mod;

long long dfs(int len,int sum,int st,bool limit){
    //��ʾ����lenλû����  Ŀǰ�ܺ���sum  Ŀǰ�Ѿ���õ�����ģmod�ĺ���st
    //��ʵ���st����û��ʲô���� ��ֻ������ж��Ƿ����ģmod��ʱ���õ�
    //st�ǳ˷�ͬ�������  ����34567%8��3���Կ�����3*10*10*10*10%8
    //�� 3%8 * 10%8 * 10%8 * 10%8 * 10%8
    if(sum+9*len<mod){
        //���ʣ�µ�λ��ȫ����9���޷����� ˵��һ������
        return 0;
    }
    if(!limit&&f[len][sum][st]!=-1){
        //�ڿ�������ѡ�������¼���f
        //����  ����ִ���Ĵ𰸱�ͳ��  ������f��ʱ���������  �����ڲ�������
        return f[len][sum][st];
    }
    if(len==0){
        //������е�λ����������  ֻ����λ����sum����st%mod==0  �ſ��Լ�һ
        return sum==mod&&st==0;
    }
    int num=limit?arr[len]:9;
    long long ans=0;
    for(int i=0;i<=num&&i+sum<=mod;i++){
        ans+=dfs(len-1,sum+i,(st*10+i)%mod,limit&&(i==num));
    }
    if(!limit){
        //����Ҫ�ڿ�������ѡ��������ͳ��f
        //����  ���������ѡ�����ֹ������ܵ���λ����mod  Ҳ�ᱻ����ļӽ�����
        f[len][sum][st]=ans;
    }
    return ans;
}

long long compute(long long x){
    for(len=0;x;x/=10){
        arr[++len]=x%10;
        //���Ƚ����ַֽ������
    }
    long long ans=0;
    for(mod=1;mod<=9*len;mod++){
        //��Ȼ��Ҫ�������λ�ϵĺ�  ��ô����ֱ��ö�ٸ�����λ�ϵĺ���ֵ
        //��ֻ����λ����mod�����ָ���
        memset(f,0xff,sizeof(f));
        ans+=dfs(len,0,0,1);
    }
    return ans;
}

int main()
{
    cin>>l>>r;
    cout<<(compute(r)-compute(l-1))<<endl;
    return 0;
}
