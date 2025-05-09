#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
const int N=3e5+10;
const int M=3e6+10;
int n,m,fa[M],siz[M],seq[N],maxn,cnt[N];
struct node{
	int x,y;
}p[M];
vector<int> ple[N];
set<int> q;
multiset<int> res;
inline bool cmp(node a,node b){
	if(a.x==b.x){
		return a.y<b.y;
	}
	return a.x<b.x;
}
inline int find(int x){
	//����root
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
inline void hb(int fx,int fy){
	//����ʽ�ϲ�
	if(siz[fx]<siz[fy]){
		swap(fx,fy);
	}
	siz[fx]+=siz[fy];
	fa[fy]=fx;
}
inline void build(int x,int l,int r){
	//����
	maxn=max(maxn,x);
	if(l==r){
		seq[l]=x;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
inline void ycl(){
	//Ԥ����
	build(1,1,n);
	for(int i=1;i<=maxn;i++){
		fa[i]=i;
		siz[i]=1;
	}
}
inline void unify(int x,int l,int r,int ql,int qr,int k){
	//��ͨ�߶����޸�ʽ����
	if(ql<=l&&r<=qr){
		int fy=find(x),fx=find(seq[k]);
		//��ͬ�źϲ�����ʡʱ��
		if(fx!=fy){
			hb(fx,fy);
		}
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid){
		unify(x<<1,l,mid,ql,qr,k);
	}
	if(qr>mid){
		unify(x<<1|1,mid+1,r,ql,qr,k);
	}
}
inline void prepare(int x,int l,int r){
	int fx=find(x),fy;
	if(fx!=x&&l!=r){
		fy=find(x<<1);
		if(fy!=fx){
			hb(fx,fy);
		}
		fy=find(x<<1|1);
		if(fy!=fx){
			hb(fx,fy);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	ycl();
	int x,y;
	//����
	for(int i=1;i<=m;i++){
		scanf("%d%d",&p[i].x,&p[i].y);
		if(p[i].x>p[i].y){
			swap(p[i].x,p[i].y);
			//��֤��һ�ؼ��ֱȵڶ��ؼ���С
		}
	}
	//����
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++){
		ple[p[i].x].push_back(p[i].y);
	}
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		int len=ple[i].size();
		l=0;
		if(!len){
			if(i+1<=n){
				unify(1,1,n,i+1,n,i);
			}
			continue;
		}
		for(int j=0;j<len;j++){
			if(j!=0){
				l=ple[i][j-1]+1;
			}
			r=ple[i][j]-1;
			if(r<=i||l>r){
				//���ܺͱ��Լ�С������ϲ�����Ϊ��һ�ؼ��ֱȵڶ��ؼ���С���޷�ȷ����ϵ
				continue;
			}
			if(l<=i){
				//ͬ��
				l=i+1;
			}
			unify(1,1,n,l,r,i);
		}
		if(ple[i][len-1]+1<=n){
			//Сѧ������ֲ�������ԭ��
			unify(1,1,n,ple[i][len-1]+1,n,i);
		}
	}
	//ȫ���ϲ�
	prepare(1,1,n);
	for(int i=1;i<=n;i++){
		//һ��һ����root
		x=find(seq[i]);
		q.insert(x);
		cnt[x]++;
	}
	//�����
	y=q.size();
	printf("%d\n",y);
	set<int>::iterator it;
	for(it=q.begin();it!=q.end();it++){
		res.insert(cnt[*it]);
	}
	multiset<int>::iterator item;
	for(item=res.begin();item!=res.end();item++){
		printf("%d ",*item);
	}
}
