//P3107
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 20;

int n,m;
int ans;

int f[MAXN][MAXN][MAXN][2][2];
int nums[MAXN];
int len;

int dfs1(int len,int k,int cnt1,int cnt2,bool flag1,bool flag2){
    //��ʾ����Ϣ�ǻ���lenλû����  ����Ҫͳ�Ƶ�������k���ֵĴ���
    //cnt1��ʾk���ֵĴ���  cnt2��ʾ����ǰ��������������ֳ��ֵĴ���
    //flag1��ʾ�Ƿ��������ѡ��  1��ʾ������  0��ʾ����
    //flag2��ʾǰ���Ƿ���0  1��ʾ��  0��ʾ����
    if(len==0){
        return cnt1>=cnt2;//���е�λ�ö��Ѿ�������  �Ƚ��Ƿ�����
    }
    if(f[len][cnt1][cnt2][flag1][flag2]!=-1){
        return f[len][cnt1][cnt2][flag1][flag2];
    }
    int ans=0;
    for(int i=0;i<=9;i++){
        //ö����һλ����Ҫ�������
        if(i<=nums[len]||flag1==0){
            //Ҫô��С��ԭ�������� Ҫô�ǿ���������
            ans+=dfs1(len-1,k,cnt1+(i==k)*(flag2==0||i!=0),cnt2+(i!=k)*(flag2==0||i!=0),flag1&&i==nums[len],i==0&&flag2);
            //(flag2==0||i!=0)��ʾ�����Ѿ�������ǰ���ķ�Χ��
            //flag1&&i==nums[len]  ��ʾ�����ǰҲ�����ɲ������ڵ���nums[len]  ��ô������  �������0 ����
            //i==0&&flag2  �����ǰ����ǰ������������0  ��ô����ǰ��
        }
    }
    f[len][cnt1][cnt2][flag1][flag2]=ans;
    return ans;
}

int calc1(int x,int k){
    //��ʾ����С��x��������  ����k���ִ�����������һ������ָ���
    memset(f,-1,sizeof(f));
    for(len=0;x;x/=10){
        nums[++len]=x%10;
    }
    return dfs1(len,k,0,0,1,1);
}

int dfs2(int len,int k1,int k2,int cnt1,int cnt2,bool flag1,bool flag2){
    if(len==0){
        return cnt1==cnt2;//���е�λ�ö��Ѿ�������  �Ƚ��Ƿ�����
    }
    if(f[len][cnt1][cnt2][flag1][flag2]!=-1){
        return f[len][cnt1][cnt2][flag1][flag2];
    }
    int ans=0;
    if(k1<=nums[len]||flag1==0){
        //Ҫô��������ѡ�� Ҫôk1����Ҫ��
        ans+=dfs2(len-1,k1,k2,cnt1+(k1!=0||flag2==0),cnt2,k1==nums[len]&&flag1,k1==0&&flag2);
    }
    if(k2<=nums[len]||flag1==0){
        //Ҫô��������ѡ�� Ҫôk2����Ҫ��
        ans+=dfs2(len-1,k1,k2,cnt1,cnt2+(k2!=0||flag2==0),k2==nums[len]&&flag1,k2==0&&flag2);
    }
    if(k1!=0&&k2!=0&&flag2==1){
        //�����ǰ��0
        ans+=dfs2(len-1,k1,k2,cnt1,cnt2,nums[len]==0&&flag1,flag2);
    }
    f[len][cnt1][cnt2][flag1][flag2]=ans;
    return ans;
}

int calc2(int x,int k1,int k2){
    //��ʾ����С��x��������  ����k1 k2���ִ������ڵ�������һ������ָ���
    memset(f,-1,sizeof(f));
    for(len=0;x;x/=10){
        nums[++len]=x%10;
    }
    return dfs2(len,k1,k2,0,0,1,1);
}

signed main()
{
    cin>>n>>m;
    for(int i=0;i<=9;i++){
        ans+=calc1(m,i)-calc1(n-1,i);
    }
    //���ܻ�𰸶��� ����1122  ������Ϊż�� �������ֶ���һ��
    for(int i=0;i<=9;i++){
        for(int j=i+1;j<=9;j++){
            ans-=calc2(m,i,j)-calc2(n-1,i,j);
        }
    }
    cout<<ans<<endl;
    return 0;
}

