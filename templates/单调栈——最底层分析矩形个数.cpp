//P1950
//��ʵ�����Ҳ��ö��ÿһ����Ϊ��ײ�  Ҳ��һ���ܺõ���Ŀ
#include<bits/stdc++.h>
using namespace std;

int st[1005];
int n,m;
int l[1005],r[1005];
int nums[1005][1005];
char s[1005][1005];
long long ans=0;

inline void work(int x) {
	int top=0;
	for(int i=1;i<=m;i++){
        while(top&&nums[x][st[top]]>=nums[x][i]){
            r[st[top--]]=i;
        }
        st[++top]=i;
	}
	while(top){
        r[st[top--]]=m+1;
	}
	for(int i=m;i>=1;i--){
        while(top&&nums[x][st[top]]>nums[x][i]){
            l[st[top--]]=i;
        }
        st[++top]=i;
	}
	while(top){
        l[st[top--]]=0;
	}
}


int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[i][j];
            if(s[i][j]=='.')
                nums[i][j]=1;
            if(s[i][j]=='*')
                nums[i][j]=0;
            if(nums[i][j]!=0){
                nums[i][j]+=nums[i-1][j];//�õ�ÿһ�������
            }
        }
    }

    for(int i=1;i<=n;i++){
        work(i);//����ջ�����l r����
        for(int j=1;j<=m;j++){
            ans+=nums[i][j]*(j - l[j]) * (r[j] - j);
        }
    }
    cout<<ans<<endl;
    return 0;
}
