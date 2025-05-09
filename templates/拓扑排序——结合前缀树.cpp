//P3065
//�����Ŀ�ܺõĽ���� ǰ׺�� �� ��������
//���Ľṹ��֤�˲����ظ����߽�ͼ 
//������൱�ڽ���������ͼ  һ����ǰ׺��  һ������ĸ֮�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 3e5+5;

int n;
string str[MAXN];
int cnt=1;
int tree[MAXM][26];
int en[MAXM];
//end  pass��ʾ�������ϵľ�����Ϣ�ͽ�β��Ϣ
int path;
int indegree[26];
int edge[26][26];
queue<int>q;

void build(){
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            edge[i][j]=0;
        }
        indegree[i]=0;
    }
}

//�������� ���ɾ����
void topo(){
    for(int i=0;i<26;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(edge[cur][i]){
                indegree[i]--;
                if(indegree[i]==0){
                    q.push(i);
                }
            }
        }
    }
}

bool check(string str){
    build();//ȫ����ʼ��
    int u=1;
    int len=str.length();
    for(int i=0;i<len;i++){
        if(en[u]){
            //����е���������ǰ׺ ��ôֱ��ûϣ��  ����false
            return false;
        }
        int v=str[i]-'a';
        for(int j=0;j<26;j++){
            if(v!=j&&!edge[v][j]&&tree[u][j]){
                //������ڵ� �� ���������ֵܽڵ�����
                edge[v][j]=1;
                indegree[j]++;
            }
        }
        u=tree[u][v];
    }
    topo();
    for(int i=0;i<26;i++){
        if(indegree[i]){
            //���ж� ˵��һ���л� ��ʾ������ ����false
            return false;
        }
    }
    return true;
}

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
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
        insert(str[i]);//�������ַ�������ǰ׺����
    }
    int ans=0;
    int t[MAXN];
    for(int i=1;i<=n;i++){
        if(check(str[i])){
            //ö�ټ��ÿһ���ַ����Ƿ����ʸ���Ϊ��С��
            t[ans]=i;//��¼���
            ans++;
        }
    }
    cout<<ans<<endl;
    for(int i=0;i<ans;i++){
        cout<<str[t[i]]<<endl;
    }
    return 0;
}
