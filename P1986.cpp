#include<bits/stdc++.h>
using namespace std;

struct node{
    int l,r,need;
}stu[5005];
bool sound[30005];
int n,m,ans=0;

bool cmp(node a,node b){
    return a.r<b.r;
}


int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>stu[i].l>>stu[i].r>>stu[i].need;
    }
    sort(stu+1,stu+m+1,cmp);
    for(int i=1;i<=m;i++)
	{
		int a=0;//����
		//��ɨһ��ͳ�Ƹ��������л�Ͳ����
		for(int j=stu[i].l;j<=stu[i].r;j++){
			if(sound[j]){
			    a++;
			}
		}
		//��β�Ϳ�ʼ��
		for(int j=stu[i].r;j>=stu[i].l;j--){
			//���˾��˳�
			if(a>=stu[i].need){
				break;
			}
			//����û�л�Ͳ�ͷ�һ��
			if(!sound[j]){
				a++;
				ans++;
				sound[j]=1;
			}
		}
	}
	cout<<ans;
    return 0;
}
