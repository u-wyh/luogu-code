#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 1e5+5;

int n,m;
string name[MAXN];
string word[MAXM];
int cnt=1;//���ڸ�ֵ�±��   ȫ����1��ʼʹ��
int tree[MAXN*50][26];//��ʾ���ֻ��26���ַ�
//tree[i][j]:��ʾ���Ϊi�Ľڵ�ͨ��j������һ���ַ�������·��������һ���ڵ�
//������λ������0  ��ʾû������·
int en[MAXN*50];
int pass[MAXN*50];
int path;
//end  pass��ʾ�������ϵľ�����Ϣ�ͽ�β��Ϣ

void insert(string word){
    int cur=1;
    //pass[cur]++;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //û��·��Ҫ�½�һ��·  ��������
        }
        cur=tree[cur][path];
        //pass[cur]++;
    }
    en[cur]++;
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
    pass[cur]++;
    if(en[cur]!=0&&pass[cur]<=1){
        return 1;
    }else if(pass[cur]>1){
        return 2;
    }else {
        return 0;
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>name[i];
        insert(name[i]);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>word[i];
        int k=search(word[i]);
        if(k==0){
            cout<<"WRONG\n";
        }else if(k==1){
            cout<<"OK\n";
        }else
            cout<<"REPEAT\n";
    }
    return 0;
}

