#include<bits/stdc++.h>
using namespace std;

//int cnt[31];//��ʾ����iλû�����iλ0��1�����ȵ���Ŀ
int sum[31];//��ʾ����iλû�����iλ0��1�����Ŀ
int a,b;

int C(int n,int m){
    int ans=1;
    for(int i=1;i<=m;i++){
        ans*=(n-i+1);
        ans/=i;
    }
    return ans;
}

int f(int num,int i,int gap,int free){
    //��ʾ������num Ŀǰ�ǵ�iλ  0-1������gap  free��ʾǰ׺�Ƿ�һ�����Ƿ��������ѡ��
    if(i==-1){
        if(gap>=0)
            return 1;
        else
            return 0;
    }
    if(free&&(gap==-1)){
        return sum[i];
    }
    int ans=0;
    if(free==0){
        int cur=(num&(1<<i));
        if(cur==1){
            ans+=f(num,i-1,gap+1,1);//��ʾ���λ����0
            ans+=f(num,i-1,gap-1,0);//��ʾ���λ����1
        }
        else{
            ans+=f(num,i-1,gap+1,0);
        }
    }
    else{
        //�����������ǻ�û��ֱ�Ӵ���������Ǹ� ˵����ֵ����1
            ans+=f(num,i-1,gap+1,1);//��ʾ���λ����0
            ans+=f(num,i-1,gap-1,1);//��ʾ���λ����1
    }
    return ans;
}

int cnt(int num){
    int tmp=num;
    int len=0;
    while(tmp){
        len++;
        tmp>>=1;
    }
    //cout<<len<<' ';
    int ans=0;
    for(int i=0;i<len-1;i++){
        ans+=sum[i];//���Ƚ�λ��������������
    }
    cout<<ans<<endl;
    ans+=f(num,len-1,0,0);
    //Ϊʲô��free  ����Ϊ�����1000000000  ��ʹ��3λ0�ͱ�1��  ���ǲ������ѡ
    return ans;
}

int main()
{
    sum[0]=0;
    for(int i=1;i<=30;i++){
        if(i%2==0){
            int k=C(i,i/2);
            sum[i]=(pow(2,i)-k)/2;
        }
        else{
            sum[i]=pow(2,i-1);
        }
        //cout<<i<<' '<<sum[i]<<endl;
    }
    cin>>a>>b;
    int ans=cnt(b)-cnt(a-1);
    cout<<ans<<endl;
    return 0;
}

//dfs(�����������λ,������������,��ǰ�ڼ�λ)
//	if ���һλ
//    	return �������������µķ���ֵ
//    �ֲ����� ct=��ǰλ������
//    �ֲ����� sum=0;
//    for i=0 to ct-1
//    	sum+=��ǰλȡiʱһ���������ƵĺϷ�״̬��
//        sum+=��ǰλȡiʱ���㵱ǰ���ƵĺϷ�״̬��
//    ����ct������������ ����������return sum
//    return sum+dfs(��ǰλ�������λ,���º����������,��һλ)
//
//slv(��ǰ��)
//	if(ֻ��һλ) return ��Ӧ�Ĺ���
//    �ֲ����� ct;
//    for ct=�������λ to 1
//    	if ��ǰλ������ break
//    �ֲ����� nw=��ǰλ����
//    �ֲ����� sum=0
//    for i=1 to nw-1
//    	sum+=��ǰλȡi��Ϸ��������ȡ�Ĺ���
//    for i=1 to ct-1
//    	for j=1 to 9
//        	sum+=��iλȡj��Ϸ��������ȡ�Ĺ���
//    sum+=dfs(ȥ����һλ�������λ,��������,�ڶ�λ)
//    return sum
//
//main
//	Ԥ����ǰλȡi�ĸ��������������ƵĹ���
//    ���� L R
//    --L
//    ��� slv(R)-slv(L)
//    return 0
