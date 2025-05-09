#include<stdio.h>
#include<string.h>

#define MAXN 26
#define MAXM 16

int n,need[MAXN],now[MAXN];
int m,vitamin[MAXM][MAXN],ans;

void dfs(int u,int v){
    if(v>=ans)
        return ;
    //��������  ���ѡ������������Ŀǰ��ans��Ҫ����ô��Ȼ����
    if(u>m){
        int i;
        for (i = 1; i <= n; i++) {
            if (now[i] < need[i]) {
                return ;
            }
        }
        ans=v;
        //����Ѿ�u>m��  ˵��û�п���ѡ�����   ��ô�ж�Ŀǰѡ��������ܷ�������ĿҪ��
        //�������  ans=v  �����˳�
    }
    dfs(u+1,v);//��ʾ��ѡu��һ������
    for(int i=1;i<=n;i++){
        now[i]+=vitamin[u][i];
    }
    dfs(u+1,v+1);//��ʾѡ����һ������
    for(int i=1;i<=n;i++){
        now[i]-=vitamin[u][i];
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&need[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&vitamin[i][j]);
        }
    }
    //�ҵ������±궼�Ǵ�1��ʼ��

    ans=m;
    //�Ȱ�ans����Ϊ����  ans=m��ʱ��һ������ʵ����ĿҪ��
    //��dfs�н��бȽ�ans�Ƿ��и��õĴ�
    memset(now,0,sizeof(now));
    //ȫ��ʵ�ֳ�ʼ��
    dfs(1,0);
    //dfs(u,v)�ĺ�����Ŀǰ���˵�u�����ϣ��Ѿ�ѡ����v��
    //dfs(1,0)���������״̬  ���������ǵ�1������   �Ѿ�ѡ�����0��
    printf("%d\n",ans);
    return 0;
}
