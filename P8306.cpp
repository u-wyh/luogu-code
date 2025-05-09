#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3000001;
const int MAXM = 1e5+5;

int cnt=1,cnt1=0;//���ڸ�ֵ�±��   ȫ����1��ʼʹ��
int tree[MAXN][80];//��ʾ���ֻ��26���ַ�
//tree[i][j]:��ʾ���Ϊi�Ľڵ�ͨ��j������һ���ַ�������·��������һ���ڵ�
//������λ������0  ��ʾû������·
int en[MAXN];
int pass[MAXN];
//end  pass��ʾ�������ϵľ�����Ϣ�ͽ�β��Ϣ
int path;
string name[MAXM];
string word[MAXM];

void insert(string word){
    int cur=1;
    pass[cur]++;
    for (char ch : word){
        path=ch-'0';
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
        path=ch-'0';
        if(tree[cur][path]==0){
            return 0;
            //û��·˵���߲�ͨ
        }
        cur=tree[cur][path];
    }
    return pass[cur];
}

void clear(){
    for(int i=cnt1;i<=cnt;i++){
        pass[i]=0;
        en[i]=0;
        for(int j=0;j<65;j++){
            tree[i][j]=0;
        }
    }
    cnt1=cnt-1;
}
//��������������ȫ�����

int main()
{
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        //cnt=1;
        for(int i=1;i<=n;i++){
            cin>>name[i];
            insert(name[i]);
        }
        for(int i=1;i<=m;i++){
            cin>>word[i];
            cout<<preword(word[i])<<endl;
        }
        clear();
    }
    return 0;
}
