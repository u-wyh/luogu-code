//P7771
//���������ͼ
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int del[MAXN];//��¼�ڵ�i�ı��Ѿ�ɾ���˼���  ��һ�δӵڼ�����ʼѡ
int in[MAXN];
int out[MAXN];
stack<int>st;
vector<int>vec[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void dfs(int u){
    for(int i=del[u];i<vec[u].size();i=del[u]){
        del[u]++;
        dfs(vec[u][i]);
    }
    st.push(u);
}

int main()
{
    n=read(),m=read();
    int u,v;
    for(int i=1;i<=m;i++){
        u=read(),v=read();
        vec[u].push_back(v);
        out[u]++,in[v]++;
    }
    for(int i=1;i<=n;i++){
        sort(vec[i].begin(),vec[i].end());//�����Ҫ�����ֵ������   ����Ҫ����
    }
    //��֤���������Ϊ����ߺ�ͼ��ͨ  �������������ͨ
    //������ͳ�Ƹ��������Ⱥͳ����Ƿ����
    bool flag=true;//��ʾ���еĽڵ�  ��Ⱥͳ�����ͬ
    int s=1;//��ʼ��  ���ܻ�仯
    int cnt1=0,cnt2=0;//�ֱ���  ��-��=1  ��  ��-��=1
    for(int i=1;i<=n;i++){
        if(in[i]!=out[i]){
            flag=false;
            if(in[i]-out[i]==1){
                cnt1++;
            }
            else if(out[i]-in[i]==1){
                cnt2++;
                s=i;
            }
            else{
                cout<<"No"<<endl;
                return 0;
            }
        }
    }
    if(!flag&&!(cnt1==cnt2&&cnt1==1)){
        //�Ȳ�����ŷ����· Ҳ������ŷ��ͨ·
        cout<<"No"<<endl;
        return 0;
    }
    dfs(s);
    while(!st.empty()){
        cout<<st.top()<<' ';
        st.pop();
    }
    return 0;
}
