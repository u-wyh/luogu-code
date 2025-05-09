#include<bits/stdc++.h>
using namespace std;

const int MAXN = 12;//�ַ�����
const int MAXS = 605;//�����ַ�������

int state[MAXS];//��ʾ��������ڵ�󣬾ͻ���ʲô����״̬

// AC�Զ���
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

// �����������л���ջ��һ���������� ����failָ��
int box[MAXS];
string s;
int path;

int n;//�ַ�������

struct node{
    int now,status;
};
queue<node>q;

bool vis[600][1<<12];
int ans[600*(1<<12)],fa[600*(1<<12)],c[605];

void insert(int i,string word){
    //i��Ŀ�괮�ı��
    int cur=0;//ͷ�������Ϊ0
    for (char ch : word){
        path=ch-'A';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
            //û��·��Ҫ�½�һ��·  ��������
        }
        cur=tree[cur][path];
    }
    state[cur]|=(1<<i);
    //cout<<i<<' '<<state[cur]<<endl;
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
                state[tree[u][i]]|=state[tree[fail[u]][i]];//����failָ��������ַ�����Ҳ����
                box[r++] = tree[u][i];//��ʾ������֧·  ���뵽������
                //cout<<state[tree[u][i]]<<endl;
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s;
        //cout<< "   "<<i<<endl;
        insert(i,s);
    }
    setFail();
    //cout<<endl;
    q.push({0,0});
    vis[0][0]=true;
    int t=0,nod=0,tot=0;
    while(!q.empty()){
        int now=q.front().now;
        int status=q.front().status;
        q.pop();
        if(status==((1<<n)-1)){
            while(t){
                c[++nod]=ans[t];
                t=fa[t];
            }//�ݹ��ȥ���
            for(int i=nod;i>0;i--)
                putchar(c[i]+'A');
            return 0;
        }
        for(int i=0;i<26;i++){
            if(!vis[tree[now][i]][status|state[tree[now][i]]]){
                vis[tree[now][i]][status|state[tree[now][i]]]=true;
                q.push({tree[now][i],status|state[tree[now][i]]});
                //�ҳ����µ�״̬
                fa[++tot]=t;
                ans[tot]=i;
                //��¼��ǰ�ѵ����ַ�,ͬʱ��1�ù��ڴ𰸵���,��������ѯ
            }
        }
        t++;//Ti��ʾ��ǰ���������ı��
    }
    return 0;
}
