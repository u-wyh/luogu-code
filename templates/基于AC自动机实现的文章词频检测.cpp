#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10001;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 2000001;

// ��¼ÿ��Ŀ�괮�Ľ�β�ڵ���
int en[MAXN];

// AC�Զ���
int tree[MAXS][127];
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
string str[100];

void insert(int i,string word){
    //i��Ŀ�괮�ı��
    int cur=0;//ͷ�������Ϊ0
    for (char ch : word){
        path=ch-'0';
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
    for (int i = 0; i <= 127; i++) {
        if (tree[0][i] > 0) {
            box[r++] = tree[0][i];
            //0�ڵ���ֻ���к��ӵĽڵ���������
            //�����������洢�������нڵ㶼Ҫ��fail
        }
    }
    while (l < r) {
        int u = box[l++];
        for (int i = 0; i <= 127; i++) {
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
//    cout<<('a'-'A')<<endl;
//    cout<<('A'-'A')<<endl;
    cout<<"������ؼ���������";
    cin>>n;
    for(int i=1;i<=n;i++){
        cout<<"������� "<<i<<" ���ؼ��ʣ�";
        cin>>str[i];
        insert(i,str[i]);
    }
    setFail();
    char ch;

    std::cout << "Enter text: ";

    // ʹ��getchar()����ַ����룬ֱ������ESC�ַ�
    while (std::cin.get(ch)) {
//        if (ch == '0') { // ����Ƿ���ESC�ַ���ASCII��27��
//            break;
//        }
        s += ch; // ���ַ���ӵ������ַ�����
    }

    int u=0;
    for (char ch:s) {
        u = tree[u][ch - '0'];//��ʾ������һ���ڵ�
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
        cout<<"�� "<<i<<" ���ؼ��� "<<setw(5)<<str[i] <<" ������ "<<times[en[i]]<<" ��"<<endl;
    }
    return 0;
}
