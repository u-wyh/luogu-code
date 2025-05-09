//P2536
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;

int sz[MAXN];
int en[MAXN];

string temp;
int n,m;
string s;

int tree[MAXN][4];
int cnt=0;
int ans=0;

void insert(string word){
    //i��Ŀ�괮�ı��
    int cur=0;//ͷ�������Ϊ0
    for (char ch : word){
        int p;
        if(ch=='A')p=0;
		if(ch=='C')p=1;
		if(ch=='T')p=2;
		if(ch=='G')p=3;
        sz[cur]++;
        if(tree[cur][p]==0){
            tree[cur][p]=++cnt;
            //û��·��Ҫ�½�һ��·  ��������
        }
        cur=tree[cur][p];
    }
    sz[cur]++;
    en[cur]++;
}

void dfs(int now,int cur){
    //now��ʾ���ڵ���ģ�洮�ĵڼ����ַ�
    //cur��ʾ���ڵ����ֵ������Ǹ��ڵ�
    if(!sz[cur]){
        //˵����ǰ����
        return;
    }
    if(now==m){
        //temp[m]�޷�����  Ҳ�������ж�
        ans+=en[cur];
		sz[cur]-=en[cur];
		en[cur]=0;
		return;
    }
    if(temp[now]=='?'){
        for(int i=0;i<4;i++){
            if(tree[cur][i]){
                dfs(now+1,tree[cur][i]);
            }
        }
    }
    else if(temp[now]=='*'){
        dfs(now+1,cur);
        for(int i=0;i<4;i++){
            if(tree[cur][i]){
                dfs(now+1,tree[cur][i]);
                dfs(now,tree[cur][i]);
            }
        }
    }
    else {
        char ch=temp[now];
        int p;
        if(ch=='A')p=0;
		if(ch=='C')p=1;
		if(ch=='T')p=2;
		if(ch=='G')p=3;
		if(tree[cur][p])
            dfs(now+1,tree[cur][p]);
    }
	sz[cur]=0;
	for(int i=0;i<4;i++)
        if(tree[cur][i])
            sz[cur]+=sz[tree[cur][i]];
}
//ƥ��ɹ��ͼ�ȥ����ַ���
//����Ϊ�˲�ʹͨ�����������ѭ����ȥ

int main()
{
    cin>>temp;
    m=temp.length();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    dfs(0,0);
    cout<<(n-ans);
    return 0;
}
