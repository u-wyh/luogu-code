#include<bits/stdc++.h>
using namespace std;

const int MAXN = 150;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 15000;

// ��¼ÿ��Ŀ�괮�Ľ�β�ڵ���
int en[MAXN];
string EN[MAXN];

// AC�Զ���
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

// ������Ŀ��أ�����Ϊ�ռ���Ƶ
// ����ÿ���ڵ��¼��Ƶ
int times[MAXS];
// �����������л���ջ��һ����������
int box[MAXS];

// ��ʽǰ���ǣ�Ϊ�˽���failָ��ķ�ͼ
int head[MAXS];
int Next[MAXS];
int to[MAXS];
int edge = 0;

string s;
int path;
int n;

void clear(){
    edge=0;
    cnt=0;
    //cout<<444<<endl;
    for(int i=1;i<=MAXS;i++){
        head[i]=0;
        Next[i]=0;
        to[i]=0;
        times[i]=0;
        box[i]=0;
        fail[i]=0;
        //cout<<555<<endl;
        for(int j=0;j<=25;j++){
            tree[i][j]=0;
        }
    }
    //s="";
}

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
    en[i]=cur;
    EN[i]=word;
}

// ��������Ŀ���ַ���֮��
// ����failָ�� �Լ� ����ֱ��ֱͨ��
// ����AC�Զ����̶����Ż�
void setFail() {
    // box����������ʹ��
    int l = 0;
    int r = 0;
    //cout<<333<<endl;
    for (int i = 0; i <= 25; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0�ڵ���ֻ���к��ӵĽڵ���������
            //�����������洢�������нڵ㶼Ҫ��fail
        }
    }
    //cout<<l<<' '<<r<<endl;
    while (l < r) {
        int u = box[l++];
        cout<<u<<' ';
        system("pause");
        //cout<<111<<endl;
        for (int i = 0; i <= 25; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];//����������ӽڵ��failָ��   ֱͨ���������ƻ�
                box[r++] = tree[u][i];//��ʾ������֧·  ���뵽������
            }
        }
    }
}
//���ֱͨ��  ��  fail��

void addEdge(int u, int v) {
    Next[++edge] = head[u];
    head[u] = edge;
    to[edge] = v;
}

void f1(int u) {
    for (int i = head[u]; i > 0; i = Next[i]) {
        f1(to[i]);
        times[u] += times[to[i]];
    }
}

int main()
{
    //cin>>n;
    while(cin>>n&&n!=0){
        //cout<<666<<endl;
        for(int i=1;i<=n;i++){
            string str;
            cin>>str;
            insert(i,str);
        }
        //cout<<777<<endl;
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=26;j++){
                cout<<tree[i][j]<<' ';
            }
            cout<<endl;
        }
        setFail();
        //cout<<666<<endl;
        cin>>s;
        //getchar();
        int u=0;
        for (char ch:s) {
            u = tree[u][ch - 'a'];//��ʾ������һ���ڵ�
            // ����ƥ�����
            times[u]++;
        }
        for (int i = 1; i <= cnt; i++) {
            // ����failָ�뽨��ͼ
            // ��ʵ��һ����
            addEdge(fail[i], i);
        }
        // ����failָ�뽨����
        // ����ÿ���ڵ�Ĵ�Ƶ
        f1(0);
        int ans=0;
        for(int i=1;i<=n;i++){
            ans=max(ans,times[en[i]]);
        }
        cout<<ans<<endl;
        for(int i=1;i<=n;i++){
            if(times[en[i]]==ans)
                cout<<EN[i]<<endl;
        }
        clear();
    }
    return 0;
}

