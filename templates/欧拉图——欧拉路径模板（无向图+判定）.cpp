//P1341
//����ͼ+�ж�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;
const int MAXM = 2600;//����n���ᳬ�������

int n;
vector<pair<int,int>>vec[MAXN];
stack<int>st;
int degree[MAXN];
int cnt=0;
bool exist[MAXM];

//�����ж��Ƿ���ͨ
int vis[MAXN];
int fa[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

void dfs(int u){
    for(int i=0;i<vec[u].size();i++){
        if(!exist[vec[u][i].second]){
            //��������Ϊ�˲���ʼ������
            exist[vec[u][i].second]=true;
            exist[vec[u][i].second^1]=true;
            //����������ȫ������
            dfs(vec[u][i].first);
        }
    }
    st.push(u);
}

int main()
{
    cin>>n;
    for(int i=0;i<60;i++){
        fa[i]=i;
    }
    int tmp=100;
    for(int i=1;i<=n;i++){
        char c1,c2;
        int u,v;
        cin>>c1>>c2;
        u=c1-'A',v=c2-'A';
        vec[u].push_back({v,cnt++});
        vec[v].push_back({u,cnt++});
        vis[u]=true,vis[v]=true;
        degree[u]++,degree[v]++;
        un(u,v);
        tmp=min(tmp,min(u,v));
    }
    int father=150;//��¼��������
    bool flag=true;//�ж��Ƿ���ͨ
    for(int i=0;i<=60;i++){
        if(vis[i]){
            if(father==150){
                father=find(i);
            }
            else{
                if(find(i)!=father){
                    flag=false;
                }
            }
        }
    }
    if(!flag){
        cout<<"No Solution"<<endl;
        return 0;
    }
    for(int i=0;i<60;i++){
        sort(vec[i].begin(),vec[i].end());
    }
    //�ж���ʼ����Ƿ����Ҫ��
    int cnt=0;//��¼����Ϊ�����ĸ���
    int s=-1;
    for(int i=0;i<60;i++){
        if(vis[i]){
            if(degree[i]%2){
                flag=false;
                cnt++;
                if(s==-1){
                    s=i;
                }
            }
        }
    }
    if(!flag&&cnt>=3){
        cout<<"No Solution"<<endl;
        return 0;
    }
    if(flag){
        s=tmp;
    }
    dfs(s);
    while(!st.empty()){
        char c=st.top()+'A';
        cout<<c;
        st.pop();
    }
    cout<<endl;
    return 0;
}
