//P2744
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 20005;

int n,m;
int arr[MAXN];//��ʾͰ������
int f[MAXM];//��ʾҪ��Щţ��������Ҫ������һ����Ͱ
//ʵ������f[i][j]��ʾǰi��Ͱ��  �ﵽj������  ������Ҫ����Ͱ  ����һά������
int q[MAXN];//��ʾ������dfs������ѡ��ķ���

void check(){
    bool vis[MAXM];//��ʾ��dfs������ѡ������ķ����Ƿ���������������ţ��
    for(int i=0;i<=m;i++){
        vis[i]=false;
    }
    vis[0]=true;
    for(int i=1;i<=f[m];i++){
        //�����f[m]��ʾ��ѡ�������Ͱ������  ���ֵһ����f[m]
        for(int j=arr[q[i]];j<=m;j++){
            if(vis[j-arr[q[i]]]){
                vis[j]=1;
            }
        }
    }
    if(vis[m]){
        //�������ʵ�� ��ôĿǰ�ķ���һ�������ŵ�
        //��Ϊ����һ��ʼ��������
        for(int i=1;i<=f[m];i++){
            cout<<arr[q[i]]<<' ';
        }
        exit(0);
    }
}

void dfs(int u,int dep){
    //��ʾĿǰ������u��Ͱ �Ѿ�ѡ��dep��Ͱ
    if(dep==f[m]){
        //���ѡ��Ͱ�ĸ����Ѿ������  ��ô��ȥ�������ַ����Ƿ���Եó���
        check();
        return ;
    }
    if(f[m]-dep>n-u){
        //��֦ ��ʾ��ʹ�����ȫѡ�� Ҳ����
        return;
    }
    for(int i=u+1;i<=n;i++){
        q[dep+1]=i;
        dfs(i,dep+1);
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    sort(arr+1,arr+n+1);//��Ͱ������������ ������ΪҪ�������
    for(int i=1;i<=m;i++){
        f[i]=1e9;
    }
    f[0]=0;
    bool vis[MAXM];//��ʾ���ǳ�������ǰţ�̵�����Ͱ����������  �Ƿ��õ������Ͱ
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            vis[j]=0;
            if(j>=arr[i]){
                int val=vis[j-arr[i]]^1;//�����ǰ�ù����Ͱ  ��ô����0  ���ü�1��
                if(f[j-arr[i]]+val<=f[j]){
                    //��ʾ���Ը���f[j]
                    f[j]=f[j-arr[i]]+val;
                    vis[j]=1;
                }
            }
        }
    }
    cout<<f[m]<<' ';
    dfs(0,0);
    return 0;
}
