#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;//���������

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

int preword(string word){
    int cur=1;
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            return 0;
            //û��·˵���߲�ͨ
        }
        cur=tree[cur][path];
    }
    return pass[cur];
}

void erase(string word){
    if(search(word)>0){
        int cur=1;
        for (char ch : word){
            path=ch-'a';
            if(--pass[tree[cur][path]]==0){
                tree[cur][path]=0;
                //������ڵ�����Ϊ0  ��ô����ڵ������ŵ�·ȫ��ʧЧ
                //��Ϊ��ʹ�����н������������  ���ǻḳ������½ڵ�����һ�����
                return ;
            }
            cur=tree[cur][path];
        }
        en[cur]--;
    }
}

void clear(){
    for(int i=1;i<=cnt;i++){
        pass[i]=0;
        en[i]=0;
        for(int j=0;j<26;j++){
            tree[i][j]=0;
        }
    }
}
//��������������ȫ�����

int main()
{
    return 0;
}
