//�ؼ��ʱ�������

#include<bits/stdc++.h>
using namespace std;
// ����Ŀ���ַ���������
const int MAXN = 200;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 2005;

// ��¼ÿ���ڵ��Ƿ񱨾�
bool alert[MAXS];
int len[MAXS];

// AC�Զ���
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

bool ok[200005];

// �����������л���ջ��һ����������
int box[MAXS];

string s;
int path;

void insert(string word){
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
    alert[cur]=true;
    len[cur]=word.length();
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
        len[u]=max(len[fail[u]],len[u]);
    }
}
//������־��Ǩ��

int main()
{
    int ans=0;
    string key;
    while(cin>>key&&key!="."){
        insert(key);
    }
    setFail();
    //cin>>s;
    string s;
	s=" ";
	string tp;
	while (cin>>tp){
		s=s+tp;//�����еĴ��ϳ�һ��
	}
    int u=0,k=0;
    for (char ch:s) {
        if(alert[u]){
            for(int i=max(k-len[u],0);i<k;i++){
                ok[i]=true;
            }
            //cout<<6<<endl;
        }
        k++;
        u = tree[u][ch - 'A'];//��ʾ������һ���ڵ�
    }
    ok[0]=true;
    //cout<<s.length()<<endl;
    for(int i=1;i<s.length();i++){
        cout<<ok[i]<<' ';
    }
    for(int i=0;i<s.length();i++){
        if(!ok[i]){
            ans=i;
            break;
        }
    }
    cout<<ans;
    return 0;
}
