#include<bits/stdc++.h>
using namespace std;

struct hzy{
	int x,y,z;
}a[200001];
int f[200001],n,m,b[200001],l;

int find(int k){//���鼯������ע��·��ѹ��
	return f[k]==k?k:f[k]=find(f[k]);
}
void un(int x,int y){//�ϲ�����
	int x1=find(x);
	int x2=find(y);
	if(x1!=x2){
		f[x1]=x2;
	}
}
int main() {
	cin>>n>>m;
	string ch;
	for(int i=1; i<=m; i++) {
		cin>>a[i].x>>a[i].y>>ch;
		a[i].x--;//����������㣬����ֱ�Ӽ�1
		if(ch[0]=='o') {//��ͬ�Ͳ�ͬҪ�����
			a[i].z=1;
		} else {
			a[i].z=0;
		}
		b[++l]=a[i].x;
		b[++l]=a[i].y;
	}
	sort(b+1,b+l+1);
	l=unique(b+1,b+l+1)-b-1;
	for(int i=1;i<=l*2;i++){
		f[i]=i;
	}
	for(int i=1; i<=m; i++) {
		a[i].x=lower_bound(b+1,b+l+1,a[i].x)-b;//��ɢ��
		a[i].y=lower_bound(b+1,b+l+1,a[i].y)-b;
		if(a[i].z==0){//���ಢ�鼯������ͬ�Ͳ�ͬ����
			if(find(a[i].x)==find(a[i].y+l)){//�����������ż�Բ�ͬ��ì�ܣ����
				cout<<i-1;
				return 0;
			}
			else{//��Ȼ�ͺϲ�����
				un(a[i].x,a[i].y);
				un(a[i].x+l,a[i].y+l);
			}
		}
		else{
			if(find(a[i].x)==find(a[i].y)){//ͬ��
				cout<<i-1;
				return 0;
			}
			else{
				un(a[i].x,a[i].y+l);
				un(a[i].x+l,a[i].y);
			}
		}
	}
	cout<<m;
	return 0;
}
