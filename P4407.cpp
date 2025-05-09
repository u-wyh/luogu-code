#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int cnt=1;//���ڸ�ֵ�±��   ȫ����1��ʼʹ��
int tree[MAXN][26];//��ʾ���ֻ��26���ַ�
//tree[i][j]:��ʾ���Ϊi�Ľڵ�ͨ��j������һ���ַ�������·��������һ���ڵ�
//������λ������0  ��ʾû������·
int en[MAXN];
int path;

int n,m;
string s;
int ans=0;
int len;
int vis[MAXN];

void insert(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //û��·��Ҫ�½�һ��·  ��������
        }
        cur=tree[cur][path];
    }
    en[cur]++;
    //cout<<cur<<endl;
}

int search(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            return 0;
            //û��·˵���߲�ͨ
        }
        cur=tree[cur][path];
    }
    return en[cur];
}

void dfs(int cur,int u,bool f,int now){
    if(u==len+1){
        if(f){
            if(vis[cur]!=now){
                ans+=en[cur];
                vis[cur]=now;
            }
        }
        else{
            for(int i=0;i<26;i++){
                if(vis[tree[cur][i]]!=now){
                    ans+=en[tree[cur][i]];
                    vis[tree[cur][i]]=now;
                }
            }
        }
    }
    path=s[u-1]-'a';
    if(tree[cur][path]!=0){
        dfs(tree[cur][path],u+1,f,now);
    }
    if(tree[cur][path]==0){
        if(u==len&&!f){
            if(vis[cur]!=now){
                ans+=en[cur];
                vis[cur]=now;
            }
        }
    }
    if(!f){
        //��ǰû���ù�
        for(int i=0;i<26;i++){
            dfs(tree[cur][i],u,1,now);//ɾ����ĸ
            dfs(tree[cur][i],u+1,1,now);//�任��ĸ
        }
        dfs(cur,u+1,1,now);//�����ĸ
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    for(int i=1;i<=m;i++){
        cin>>s;
        if(search(s)){
            cout<<-1<<endl;
            continue;
        }
        len=s.length();
        ans=0;
        dfs(1,1,0,i);
        //cout<<endl;
        cout<<ans<<endl;
    }
    return 0;
}

