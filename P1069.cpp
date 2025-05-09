#include<bits/stdc++.h>
using namespace std;

int prime[20000];
int cnt;

void euler(int n) {
    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0��ʾ������1��ʾ����
    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * prime[j] <= n; j++) {
            //ÿһ�δ���С��������ʼ
            visit[i * prime[j]] = 1; // ���Ϊ����
            if (i % prime[j] == 0) {
                //���i��������prime[j]˵��һ���������������
                //��ô��������Ļ�  ���ǽ������������ֵİ�����һ�������ų�
                //������С�������ų���
                break; // ÿ������ֻ������С��������ɸȥһ��
            }
        }
    }
}

int vis[30000];
int visit[30000];

int main()
{
    euler(30000);
    int n,m1,m2;
    cin>>n>>m1>>m2;
    int i=0;
    while(m1!=1){
        if(m1%prime[i]==0){
            while(m1%prime[i]==0){
                vis[i]+=m2;
                m1/=prime[i];
            }
        }
        i++;
    }
    int ans=INT_MAX,pos=n+1;
    for(int i=1;i<=n;i++){
        int u,flag=1,now=0;
        cin>>u;
        int j=0;
        while(j<cnt){
            if(u%prime[j]==0){
                while(u%prime[j]==0){
                    visit[j]++;
                    u/=prime[j];
                }
            }
            j++;
        }
        for(int j=0;j<cnt;j++){
            if(vis[j]!=0&&visit[j]==0){
                flag=0;
                break;
            }
            if(vis[j]!=0&&visit[j]!=0){
                now=max(now,(vis[j]+visit[j]-1)/visit[j]);
            }
        }
        if(flag){
            if(now<ans){
                ans=now;
                pos=i;
            }
        }
        for(int j=0;j<cnt;j++){
            visit[j]=0;
        }
    }
    if(pos==n+1){
        cout<<-1<<endl;
    }else{
        cout<<ans<<endl;
    }
    return 0;
}
