#include<bits/stdc++.h>
using namespace std;
const int MAXN =105;

int n,m;
int graph[MAXN][MAXN];
//�ڽӱ�
stack<int >st;
//ջ�ṹ  ���ڴ���ڵ�
int Time=1;
//����ʱ���
int dfn[MAXN];
int low[MAXN];
//�ֱ���ÿ���ڵ�Ĳ���
bool instack[MAXN];
//�ж��Ƿ���ջ��

void dfs(int x){
    dfn[x]=Time;
    low[x]=Time++;
    //dfn����һ����ֵ  �㲻�ٸı�
    //low����ֵ��ʲô��ʵ����Ҫ  ��ֻ�з����ı����û�иı���һ�����õ���Ϣ
    st.push(x);
    //ѹ��ջ��
    instack[x]=true;
    for(int k=1;k<=n;k++){
        //printf("%d ",graph[x][k]);
        if(graph[x][k]){
            //��ֻ���Է����Լ��ܵ���ĵ�
            if(!dfn[k]){
                //���Կ��������ȷ�����һ���ڵ�  ������ֵ�Լ�  �ڶ���dfs
                dfs(k);
                low[x]=min(low[x],low[k]);
                //��Ϊyû�б����ʹ�  ������dfs(y)  ��ʱy��low�Ѿ�����ֵ   �����������������  ��ôҲ�Ѿ����
            }else if(instack[k]){
                //��ô˵��yһ����x֮ǰ����  ��Ȼ�γ�һ����
                low[x]=min(low[x],dfn[k]);
            }
            //ʣ�µ���������Ǽ��Ѿ������ʹ�  Ҳ����ջ��
        }
    }
    cout<<endl;
    if(dfn[x] == low[x]){
        //���������ͬ  ��ʼ���
        int tmp;
        do{
            tmp = st.top();
            st.pop();
            instack[tmp] = false;
            cout<<tmp<<' ';
        }while(tmp != x);
        //ֱ�����xΪֹ
        cout<<endl;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        graph[u][v]=1;
    }
    //����ڽӱ�ĳ�ʼ��
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            //���û�б����ʵ��Ż����dfs
            dfs(i);
        }
    }
    return 0;
}
