#include<bits/stdc++.h>
using namespace std;
#define MN 605

int add[MN][26],fail[MN],state[MN],nod,ans[MN*(1<<12|1)],fa[MN*(1<<12|1)],n,cnt,tot;
//add:Trie���еĵ�ַ(address)
bool vis[MN][1<<12|1];
char C[MN],ch[51];
queue<int>Q,Q1,Q2;

void getfail(){
    for(int i=0;i<26;++i)
        if(add[0][i])
            Q.push(add[0][i]);
    while(!Q.empty()){
        int x=Q.front();
        Q.pop();
        for(int i=0;i<26;++i)
            if(add[x][i]){
                fail[add[x][i]]=add[fail[x]][i];
                state[add[x][i]]|=state[add[fail[x]][i]];//����failָ��������ַ�����Ҳ����
                Q.push(add[x][i]);
                cout<<state[add[x][i]]<<endl;
            }
            else
                add[x][i]=add[fail[x]][i];
    }
}
//AC�Զ�����fail��

int main()
{
    scanf("%d",&n);
    int now;
    for(int i=1;i<=n;++i){
        scanf("%s",ch);
        now=0;
        int ln=strlen(ch);
        for(int j=0;j<ln;++j){
            if(!add[now][ch[j]-'A'])
                add[now][ch[j]-'A']=++cnt;
            now=add[now][ch[j]-'A'];
        }
        state[now]|=1<<(i-1);//i-1Ҳ�����ͻ,ʡһ��ռ�
        cout<<i<<' '<<state[now]<<endl;
        //���ظ���,Ҫ��|
    }//��trie��
//    for(int i=0;i<now;i++){
//        cout<<state[i]<<' ';
//    }
    getfail();
    Q1.push(0);
    Q2.push(0);
    //Q1:��Trie�е�λ��
    //Q2:״̬ѹ��,��ʾ��ǰ��������ЩҪ����ַ���
    vis[0][0]=1;
    int Ti=0;
    while(!Q1.empty()){
        int now=Q1.front(),St=Q2.front();
        Q1.pop();
        Q2.pop();
        if(St==((1<<n)-1)){
            while(Ti){
                C[++nod]=ans[Ti];
                Ti=fa[Ti];
            }//�ݹ��ȥ���
            for(int i=nod;i>0;--i)
                putchar(C[i]+'A');
            return 0;
        }
        for(int i=0;i<26;++i){
            if(!vis[add[now][i]][St|state[add[now][i]]]){
                vis[add[now][i]][St|state[add[now][i]]]=1;
                Q1.push(add[now][i]);
                Q2.push(St|state[add[now][i]]);
                //�ҳ����µ�״̬
                fa[++tot]=Ti;
                ans[tot]=i;
                //��¼��ǰ�ѵ����ַ�,ͬʱ��1�ù��ڴ𰸵���,��������ѯ
            }
        }
        ++Ti;//Ti��ʾ��ǰ���������ı��
    }
    return 0;
}
