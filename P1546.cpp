#include<bits/stdc++.h>
using namespace std;

struct node{
    int st,en,cost;
}nums[100000];
int n;
int f[200002];

bool cmp(node a,node b){
    return a.cost<b.cost;
}

int find(int x){
//���鼯˵���˾����Ҹ����Ĺ��̣�ͬһ�����ڵ㼴ͬһ������
	if(x==f[x]) return x;
	f[x]=find(f[x]);
	return f[x];
}

int main()
{
    cin>>n;
    int cnt=1;
    for(int i=1;i<=n;i++){
        f[i]=i;
        for(int j=1;j<=n;j++){
            if(j<=i){
                int a;
                cin>>a;
            }else{
                nums[cnt].st=i;
                nums[cnt].en=j;
                cin>>nums[cnt++].cost;
            }
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    int ans=0,p=1;
	for(int i=1;i<=cnt;i++){
		if(find(nums[i].st)!=find(nums[i].en)){
        //�������һ������
			ans+=nums[i].cost;
			f[find(nums[i].st)]=nums[i].en;
            //�ϲ������ڵ�
			p++;
			if(p==n) break;
		}
	}
	cout<<ans;
    return 0;
}
