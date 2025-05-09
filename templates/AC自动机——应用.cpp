//P3082
#include<bits/stdc++.h>
using namespace std;
// ����Ŀ���ַ��������ַ�����
const int MAXS = 1005;
const int MAXN = 1e4+5;

// AC�Զ���
int tree[MAXS][26];
int fail[MAXS];
int cnt = 0;

bool en[MAXS];
// �����������л���ջ��һ����������
int box[MAXS];

string s,str;
int path;
int n;

int dp[MAXN][MAXS];

void insert(string word){
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
    en[cur]=true;
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
    }
}
//������־��Ǩ��

int main()
{
    cin>>str>>s;
    insert(s);
    setFail();
    int n=str.size();
    //cout<<n<<' '<<cnt<<endl;
    //dp�ĺ�����str��ǰi���ַ�  ��  �ڵ�jƥ��  ���ʣ����ٸ���ĸ
    for(int i=1;i<=n;i++){
        for(int j=0;j<=cnt;j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j]);
            if(!en[tree[j][str[i-1]-'a']]){
                dp[i][tree[j][str[i-1]-'a']]=max(dp[i][tree[j][str[i-1]-'a']],dp[i-1][j]+1);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=cnt;i++){
        ans=max(ans,dp[n][i]);
    }
    cout<<(n-ans)<<endl;
    return 0;
}
