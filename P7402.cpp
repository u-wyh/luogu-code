#include<iostream>
#include<cmath>
#define int long long//�ǵÿ�long long
using namespace std;
const int szl=8e5+5;
int sgt[szl][2][2];//��һά���߶����ڵ��ţ��ڶ�λ��ʾ��˵�״̬������λ��ʾ�ɶ˵�״̬��0��ʾ��ѡ��1��ʾѡ
int a[szl],d[szl],root=1;
void Updata(int p,int mid){
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			if(d[mid]*d[mid+1]>=0)sgt[p][i][j]=sgt[p<<1][i][1]+sgt[p<<1|1][1][j];//���Ժϲ���һ������
			else sgt[p][i][j]=max(sgt[p<<1][i][0]+sgt[p<<1|1][1][j],sgt[p<<1][i][1]+sgt[p<<1|1][0][j]); //���ܺϲ���һ������
	return;
}
void Add(int p,int l,int r,int pos){
	if(l==r){
		sgt[p][1][1]=abs(d[l]);
		return;
	}
	int mid=l+r>>1;
	if(pos<=mid)Add(p<<1,l,mid,pos);
	else Add(p<<1|1,mid+1,r,pos);
	Updata(p,mid);
	return;
}

signed main(){
	int n,q;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		d[i]=a[i]-a[i-1];
		if(i==1)continue;
		Add(root,2,n,i);
		//Ҳ����д������O(N)������������д��ȴ�򵥣���Щһ���������������ᳬʱ�����ٴ�����
		//ע�⣺��������2��n���������Ч ��
	}
	cout<<tree[1][1][1]<<endl;
//	while(q--){
//		int l,r,x;cin>>l>>r>>x;
//		if(l>1){
//			d[l]+=x;
//			Add(root,2,n,l);
//		}
//		if(r<n){
//			d[r+1]-=x;
//			Add(root,2,n,r+1);
//		}
//		cout<<sgt[root][1][1]<<endl;//���ֱ����������ñȽ����Ҷ˵㲻ѡ�����
//	}
	return 0;
}
