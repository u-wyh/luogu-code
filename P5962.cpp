#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 1e6+5;

int n;
int now,last;//��ʾ��һ�к���һ�зֱ��ж��ٸ���ͨ��
struct node{
    int u,v,id;//��ʾ��� �յ� ���
}nums[MAXN],arr[MAXN];//�ֱ��ʾ��һ�к���һ�е���ͨ����Ϣ
int cnt;//��ͨ����
int fa[MAXM];
int sz[MAXM];
string str;
int ans[1005];//ans[i]��ʾ��СΪi����ͨ��ĸ���

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    fa[fx]=fy;
    sz[fy]+=sz[fx];
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str;
        if(str==";"){
            now=0;
            continue;
        }

        //������һ�����Ϣ
        for(int j=1;j<=now;j++){
            arr[j]=nums[j];
        }
        last=now;
        now=0;

        bool flag=false;//�����ж���  ��  ����  ��
        int a,b,num=0;//����Ƕ�  ��ôa����߽� b���ұ߽�  num�����ڸ��������λ��
        for(int j=0;j<(int)str.size();j++){
            if(str[j]>='0'&&str[j]<='9'){
                num=num*10+(str[j]-'0');
            }
            else if(str[j]=='-'){
                a=num,flag=true,num=0;
            }
            else if(str[j]==','||str[j]==';'){
                if(flag){
                    //��ʾ����һ��
                    b=num;//�ұ߽�
                }
                else{
                    a=b=num;//���ұ߽綼��һ����
                }
                //�½���ͨ��
                fa[++cnt]=cnt;
                sz[cnt]=b-a+1;

                nums[++now]={a,b,cnt};
                //�ж�����һ���Ƿ��ཻ
                int u=1;
                while(u<=last&&arr[u].v<a){
                    u++;
                }
                while(u<=last&&arr[u].u<=b){
                    un(arr[u].id,cnt);
                    u++;
                }

                a=0,b=0,num=0,flag=false;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        if(i==find(i)){
            ++ans[sz[i]];
        }
    }
    for(int i=1000;i>=1;i--){
        if(ans[i]){
            cout<<i<<' '<<ans[i]<<endl;
        }
    }
    return 0;
}