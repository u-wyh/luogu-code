#include<bits/stdc++.h>

#define For(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
inline int read()
{
	char c=getchar();int x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-48;
	return x*f;
}
int T,n,x;
unordered_map<int,bool>s;//����
void work()
{
	s.clear();//���
	n=read();
	For(i,1,n){
		x=read();
		if(!s[x]){//û�еĻ���ֱ�����+��ǵ���
			printf("%d ",x);
			s[x]=1;
		}
	}puts("");//����
}
int main()
{
	T=read();
	while(T--)work();
	return 0;
}
