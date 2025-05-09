// AC�Զ���ģ��(�Ż���)
// ��������Ŀ���ַ���������һƪ����
// ����ÿ��Ŀ���ַ����������г����˼���
// �������� : https://www.luogu.com.cn/problem/P5357
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200001;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 200001;

// ��¼ÿ��Ŀ�괮�Ľ�β�ڵ���
int en[MAXN];

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
}

// ��������Ŀ���ַ���֮��
// ����failָ�� �Լ� ����ֱ��ֱͨ��
// ����AC�Զ����̶����Ż�
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
    cin>>n;
    for(int i=1;i<=n;i++){
        string str;
        cin>>str;
        insert(i,str);
    }
    setFail();
    cin>>s;
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
    for(int i=1;i<=n;i++){
        cout<<times[en[i]]<<endl;
    }
    return 0;
}
