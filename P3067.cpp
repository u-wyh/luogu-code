//���ַ���֮���Դ� ����Ϊ�����Ŀ�ʵ��ǿ��Ի��ֵļ��ϵĸ���  �����ǿ��Ի��ֵļ��ϵĻ��ַ�����
//���� 1 1 1 2  ���Ի��ֳ� 1 1 1     2��ֵΪ1   ��   1 1      1 2��ֵҲΪ1
// #include<bits/stdc++.h>
// using namespace std;
// const int MAXN = 1e5+5;

// int n;
// int arr[22];
// int lsum[MAXN],lsize;
// int rsum[MAXN],rsize;
// int size;

// void dfs(int u,int st,int en,int sum,int *num){
//     if(u==en+1){
//         num[++size]=sum;
//         return ;
//     }
//     dfs(u+1,st,en,sum+arr[u],num);
//     dfs(u+1,st,en,sum-arr[u],num);
//     dfs(u+1,st,en,sum,num);
// }

// int main()
// {
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         cin>>arr[i];
//     }
//     size=0;
//     dfs(1,1,n/2,0,lsum);
//     lsize=size;
//     size=0;
//     dfs(n/2+1,n/2+1,n,0,rsum);
//     rsize=size;
//     sort(lsum+1,lsum+lsize+1);
//     sort(rsum+1,rsum+rsize+1);
//     int ans=0;
//     int last=0;
//     int r=rsize;
//     lsum[0]=lsum[1]+1;//��ʾ���ǲ�һ��  ��ֹżȻ��ͬ
//     for(int i=1;i<=lsize;i++){
//         if(lsum[i]==lsum[i-1]){
//             ans+=last;
//             continue;
//         }
//         last=0;
//         while(r&&(lsum[i]+rsum[r]>=0)){
//             if(lsum[i]+rsum[r]==0){
//                 last++;
//             }
//             r--;
//         }
//         ans+=last;
//     }
//     ans/=2;
//     cout<<ans<<endl;
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1<<21;

int n;
int arr[21];
vector<int>vec[MAXN];
map<int,int>vis;
int tot=0;//��ɢ��
int ans[MAXN];

void dfs1(int u,int sum,int now){
    //now��ʾ��ĿǰΪֹѡ����״̬
    if(u==n/2+1){
        if(vis[sum]==0){
            vis[sum]=++tot;//��ɢ��
        }
        vec[vis[sum]].push_back(now);
        return ;
    }
    dfs1(u+1,sum+arr[u],now|(1<<(u-1)));
    dfs1(u+1,sum-arr[u],now|(1<<(u-1)));
    dfs1(u+1,sum,now);
}

void dfs2(int u,int sum,int now){
    if(u==n+1){
        int k=vis[sum];
        if(k!=0){
            for(int i=0;i<vec[k].size();i++){
                ans[now|vec[k][i]]=1;
            }
        }
        return ;
    }   
    dfs2(u+1,sum+arr[u],now|(1<<(u-1)));
    dfs2(u+1,sum-arr[u],now|(1<<(u-1)));
    dfs2(u+1,sum,now);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    dfs1(1,0,0);
    dfs2(n/2+1,0,0);
    int res=0;
    for(int i=1;i<(1<<n);i++){
        res+=ans[i];
    }
    cout<<res<<endl;
    return 0;
}