#include <bits/stdc++.h>
using namespace std;
#define rnt register int
const int N=5e5+10;
int n,q;
string cyj;
struct hextree{  //�߶���
	int col[N<<2],mark[N<<2];
	hextree(){memset(mark,-1,sizeof mark);}
	void pushup(rnt k){
		if(col[k<<1]==col[k<<1|1]){
			col[k]=col[k<<1];
		} else col[k]=-1;
	} void pushdown(rnt k){
		if(mark[k]!=-1){
			col[k<<1]=col[k<<1|1]=mark[k];
			mark[k<<1]=mark[k<<1|1]=mark[k];
			mark[k]=-1;
		}
	} void build(rnt l,rnt r,rnt k){
		if(l==r){
			col[k]=cyj[l-1]-'A'+1; //ȡ1��2��3
			return;
		} rnt mid=(l+r)>>1;
		build(l,mid,k<<1);
		build(mid+1,r,k<<1|1);
		pushup(k);
	} void fix(rnt x,rnt y,rnt z,rnt l,rnt r,rnt k){
		if(x>r||y<l) return;
		if(x<=l&&r<=y){
			col[k]=mark[k]=z; //������pushdown
			return;
		} pushdown(k);
		rnt mid=(l+r)>>1;
		fix(x,y,z,l,mid,k<<1);
		fix(x,y,z,mid+1,r,k<<1|1);
		pushup(k);
	} int draw(rnt x,rnt y,rnt l,rnt r,rnt k){
		/*
		0��ʾ�����䲢��ѯ�ʡ�
		���һ�������䲻ѯ�ʣ�������һ��������ķ���ֵ
		�����һ�������ɫ�����ػ�ɫ
		�������������ͬɫ�����ش�ɫ
		���򣬷��ػ�ɫ
		*/
		if(x>r||y<l) return 0;
		if(x<=l&&r<=y) return col[k];
		pushdown(k);
		rnt mid=(l+r)>>1,L,R;
		L=draw(x,y,l,mid,k<<1);
		R=draw(x,y,mid+1,r,k<<1|1);
		if(L==0) return R;
		if(R==0) return L;
		if(L==-1||R==-1) return -1;
		if(L==R) return L;
		return -1;
	}
}tree;
int main(){
	scanf("%d",&n);
	cin>>cyj;
	scanf("%d",&q);
	tree.build(1,n,1);
	while(q--){
		int x,y;
		char sign,op;
		scanf(" %c ",&sign);
		if(sign=='A'){
			scanf("%d%d %c",&x,&y,&op);
//			printf("x=%d y=%d op=%c\n",x,y,op);
			tree.fix(x,y,op-'A'+1,1,n,1);
		} else {
			scanf("%d%d",&x,&y);
			int L=tree.draw(x-1,x-1,1,n,1),
			R=tree.draw(y+1,y+1,1,n,1);
//			printf("L=%d R=%d\n",L,R);
			//����������û���ұ�û������ұ߲�ͬ��
			//�����м���ͬһ�ֿ󣬾ͷ���Ҫ��
			if(tree.draw(x,y,1,n,1)!=-1
			&&(L!=R||!L||!R)) puts("Yes");
			else puts("No"); //�����Сд
		}
	}
	return 0;
}
