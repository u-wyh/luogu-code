#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
int n,m,a[500005];
char s[500005];
struct node{
	ll i,o,oi,io,ioi;
	inline void mem(){
		i=o=oi=io=ioi=0;
	}
}tree[4000005];
inline node add(register node a,register node b){
	register node c;
	c.mem();
	c.i=a.i+b.i;
	c.o=a.o+b.o;
	c.oi=a.oi+b.oi+a.o*b.i;
	c.io=a.io+b.io+a.i*b.o;
	c.ioi=a.ioi+b.ioi+a.i*b.oi+a.io*b.i;
	return c;
}
inline void pushup(register int now){
	tree[now]=add(tree[now*2],tree[now*2+1]);
	return;
}
inline void update(register int now,register int nowl,register int nowr,register int pos,register int k){
	if (nowl==nowr){
		tree[now].mem();
		if (k==0)tree[now].i=1;
		else tree[now].o=1;
		return;
	}
	register int mid=(nowl+nowr)/2;
	if (pos<=mid)update(now*2,nowl,mid,pos,k);
	else update(now*2+1,mid+1,nowr,pos,k);
	pushup(now);
	return;
}
inline node query(register int now,register int nowl,register int nowr,register int lt,register int rt){
	if (nowl>=lt&&nowr<=rt)return tree[now];
	register int mid=(nowl+nowr)/2;
	register node s;s.mem();
	if (mid>=lt)s=add(s,query(now*2,nowl,mid,lt,rt));
	if (mid+1<=rt)s=add(s,query(now*2+1,mid+1,nowr,lt,rt));
	return s;
}
inline void build(register int now,register int nowl,register int nowr){
	tree[now].mem();
	if (nowl==nowr){
		if (a[nowl]==0)tree[now].i=1;
		else tree[now].o=1;
		return;
	}
	int mid=(nowl+nowr)/2;
	build(now*2,nowl,mid);
	build(now*2+1,mid+1,nowr);
	pushup(now);

	return;
}
int main(){
	cin>>n>>m;
	scanf("%s",s+1);
    for (int i=1;i<=n;i++){
        if (s[i]=='I')a[i]=0;
        else a[i]=1;
    }
	build(1,1,n);
	for (int i=1;i<=m;i++){
		int flag;
		scanf("%d",&flag);
		if (flag==1){
			int x,c;
			char ch[5];
			scanf("%d%s",&x,ch);
			if (ch[0]=='I')c=0;
			else c=1;
			update(1,1,n,x,c);
		}
		else{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(1,1,n,l,r).ioi);
		}
	}
	return 0;
}
