#include<bits/stdc++.h>
using namespace std;

int a[100][100],minn=INT_MAX,q[100],i,j,f[1000][100],qmin[100];//�����������ֿ���
void dfs(int x,int y,int s){//�������� x����ʣ x km,y����ǰy��,s��������ʱ��
	if (x<0)
	return;//��仰�����Ƕ����
	if (f[x][y]<=s)
	return;
	f[x][y]=s;//���仯��f[x][y]��ʾ��ʣx���ǰy���˲μӣ��ܴﵽ����С��ʱ��
	if (y>5){//��������˶�����
		if (x==0)//�������ȫ����
			if (minn>s){//���ʱ���ԭ���Ѽ�¼����
				minn=s;
				for (int i=1;i<=5;++i)
				qmin[i]=q[i];//��¼
			}
		 return;
	}
	for (int i=1;i<=min(x,10);++i){//ö�ٵ�ǰ���������i����
	q[y]=i;//��¼
	dfs(x-i,y+1,s+a[y][i])//;ʣ��·��-i,��һ���ˣ�ʱ��Ӹ�����i��������Ҫ��ʱ��
}
}
int main(){
	for (i=1;i<=5;++i)
	for (j=1;j<=10;++j)
	cin>>a[i][j];//����
	for (i=0;i<=100;++i)
	for (j=0;j<=80;++j)
	f[i][j]=INT_MAX;//��ʼ������Ҳ������д��
	dfs(25,1,0);//����
	cout<<minn<<endl;
	for (i=1;i<=4;++i)
	cout<<qmin[i]<<" ";cout<<qmin[5];//��ӡ��
}
