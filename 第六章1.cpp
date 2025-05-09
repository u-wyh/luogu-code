//˳��洢 �����ĸ߶�  Ҷ�ӽ�����  ������
//�������Ϣ����  �ڵ�����  �Լ����ǵĸ��׽ڵ���
//˫�ױ�ʾ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;              //������
int fa[MAXN];       //��ʾ����ڵ�ĸ��׽ڵ�
int val[MAXN];      //��ʾ����ڵ�洢��ֵ

int degree[MAXN];   //��ʾ����ڵ�Ķ�
int high[MAXN];     //��ʾ����ڵ�߶�
int sz[MAXN];       //������ڵ�Ϊͷ������Ҷ�ӽ�����

//��ʽǰ���ǽ�ͼ
int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

//��ʽǰ��������
void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    bool flag=0;//�ж��Ƿ��к���
    for(int i=head[u];i;i=nxt[i]){
        degree[u]++;
        int v=to[i];
        dfs(v);
        flag=1;//��ʾ�к��� ��ôһ������Ҷ�ӽ��
        high[u]=max(high[u],high[v]);//�ҵ����ӽڵ������ĸ߶�
        sz[u]+=sz[v];//���Ϻ��ӵ������е�Ҷ�ӽ�����
    }
    high[u]+=1;
    if(!flag){
        //��ʾ��Ҷ�ӽ��
        sz[u]=1;
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>fa[i];
    }
    int root=0;//��ʾ�������ĸ��ڵ�
    for(int i=0;i<n;i++){
        if(fa[i]!=-1){
            addedge(fa[i],i);
        }
        else{
            root=i;
        }
    }
    dfs(root);//�Ӹ��ڵ㿪ʼ����
    for(int i=0;i<n;i++){
        cout<<head[i]<<' ';
    }
    cout<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<nxt[i]<<' '<<to[i]<<endl;
    }
    cout<<endl;
    int ans=0;//ͳ��������
    for(int i=0;i<n;i++){
        ans=max(ans,degree[i]);
    }
    cout<<"Ҷ�ӽ������Ϊ�� "<<sz[root]<<endl;
    cout<<"������Ϊ�� "<<ans<<endl;
    cout<<"���ĸ߶�Ϊ�� "<<high[root]<<endl;
    return 0;
}
/*
14
-1 0 0 0 1 1 2 3 3 3 5 5 8 8
*/
