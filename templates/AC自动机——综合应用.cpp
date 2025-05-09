// ����(����AC�Զ����������)
//�ؼ��ʱ�������
#include<bits/stdc++.h>
using namespace std;
// ����Ŀ���ַ���������
const int MAXN = 10001;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 10001;

// ��¼ÿ���ڵ��Ƿ񱨾�
bool alert[MAXS];

// AC�Զ���
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

// ÿ���ڵ��¼��Ƶ
int times[MAXS];
// �����������л���ջ��һ����������
int box[MAXS];

string s;
int path;
int n;

void insert(int i,string word){
    //i��Ŀ�괮�ı��
    int cur=0;//ͷ�������Ϊ0
    for (char ch : word){
        path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //û��·��Ҫ�½�һ��·  ��������
        }
        cur=tree[cur][path];
    }
    alert[cur]=true;
}

void setFail() {
    // box����������ʹ��
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 25; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0�ڵ���ֻ���к��ӵĽڵ���������
            //�����������洢�������нڵ㶼Ҫ��fail
        }
    }
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 25; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];//����������ӽڵ��failָ��   ֱͨ���������ƻ�
                box[r++] = tree[u][i];//��ʾ������֧·  ���뵽������
            }
        }
        // ���б��ǰ��
        alert[u] |= alert[fail[u]];
    }
}
//������־��Ǩ��

int main()
{
    cout<<"������ؼ�������: ";
    cin>>n;
    for(int i=1;i<=n;i++){
        cout<<"������� "<<i<<" ���ؼ���: ";
        string str;
        cin>>str;
        insert(i,str);
    }
    setFail();
    cout<<"����������ַ���: ";
    cin>>s;
    int u=0,k=0,flag=0;
    for (char ch:s) {
        if(alert[u]){
            flag=1;
            cout<<"�ڵ� "<<k<<" ��λ�ô����ؼ��ʣ�"<<endl;
            break;
        }
        k++;
        u = tree[u][ch - 'a'];//��ʾ������һ���ڵ�
    }
    if(flag!=1)
        cout<<"����������δ�����κ����⡣"<<endl;
    return 0;
}

/*
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha

6
beta
alpha
haha
delta
dede
tata
dedaltblphahbhahototatolqha
*/
