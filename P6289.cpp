//������˼���Ǻ������
//����Ҫ��������������ַ�������һ��Ľṹ���ٵĽڵ�����
//���ȿ��Ǽ����  ���ǿ���֪��  ����ǽ��������ϲ���һ��
//��ô���� �������ĳ��Ⱥ� - �ϲ���Ĺ���ǰ׺
//Ҫʹ�������ǰ׺�����ܵĴ�  �����ڵ�Ż���
//��ô�����ڿ��Ƕ������ϲ�  ������ô˵ �������ϲ�һ�����Կ����������ϲ�
//���������϶��������Ӵ�  ��ô���ǿ���ö���������������������պϲ�������
//��һ��������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
char s[MAXN];
int sum[20][26];
int cnt[1<<16];
int f[1<<16];

int compute(int sta){
    for(int i=0;i<26;i++){
        sum[n+1][i]=INT_MAX;
    }
    for(int i=0;i<n;i++){
        if(sta&(1<<i)){
            for(int j=0;j<26;j++){
                sum[n+1][j]=min(sum[n+1][j],sum[i][j]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<26;i++){
        ans+=sum[n+1][i];
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=0;i<(1<<n);i++){
        f[i]=1e9;
    }
    for(int i=0;i<n;i++){
        scanf("%s",s);
        int len=strlen(s);
        for(int j=0;j<len;j++){
            sum[i][s[j]-'a']++;
        }
        f[1<<i]=len;
    }
    for(int i=1;i<(1<<n);i++){
        cnt[i]=compute(i);
    }
    for(int i=1;i<(1<<n);i++){
        for(int j=i;j;j=i&(j-1)){
            f[i]=min(f[j]+f[i-j]-cnt[i],f[i]);
        }
    }
    cout<<f[(1<<n)-1]+1;
    return 0;
}
