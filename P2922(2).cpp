#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 5e5+5;

int m,n;
string word[MAXN];
string code[MAXN];

int cnt=1;//���ڸ�ֵ�±��   ȫ����1��ʼʹ��
int tree[MAXN][26];//��ʾ���ֻ��26���ַ�
//tree[i][j]:��ʾ���Ϊi�Ľڵ�ͨ��j������һ���ַ�������·��������һ���ڵ�
//������λ������0  ��ʾû������·
int en[MAXN];
int pass[MAXN];
//end  pass��ʾ�������ϵľ�����Ϣ�ͽ�β��Ϣ
int path;

void insert(string word){
    int cur=1;
    pass[cur]++;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //û��·��Ҫ�½�һ��·  ��������
        }
        cur=tree[cur][path];
        pass[cur]++;
    }
    en[cur]++;
}

int preword(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            return en[cur];
            //û��·˵���߲�ͨ
        }
        cur=tree[cur][path];
    }
    return pass[cur];
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        //cin>>t;
        cin>>word[i];
        insert(word[i]);
    }
    for(int i=1;i<=n;i++){
        cin>>code[i];
        cout<<preword(code[i])<<endl;
    }
    return 0;
}
