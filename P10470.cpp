#include<bits/stdc++.h>
using namespace std;
int n,m;
string s;
struct Tree
{
     int fail;
     int vis[30];
     int end;
}tree[1500000];
int cnt=1;
void build(string s)//���ַ���s�����ֵ���
{
	int l=s.size();//��ȡs�ĳ���
	int now=1;//nowָ����Ϊ1
	for(int i=0;i<l;++i)
	{
		if(tree[now].vis[s[i]-'a']==0)//û�н���
			tree[now].vis[s[i]-'a']=++cnt;
		now=tree[now].vis[s[i]-'a'];//��ת
	}
	tree[now].end+=1;//��β������1
}
int getans(string s)//��ȡ���
{
	int l=s.size();
	int now=1,ans=0;//ͬbuild
	for(int i=0;i<l;++i)
	{
		now=tree[now].vis[s[i]-'a'];//��ת
		for(int t=now;t&&tree[t].end!=-1;t=tree[t].fail)//ÿ�ζ���failָ��
		{
			ans+=tree[t].end;//���Ͻ�β�ģ���ͳ�ƴ�
		}
	}
	return ans;
}
int main()//������ûʲô�ܽ�����OVO
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		build(s);
	}
	while(m--)
	{
		cin>>s;
		cout<<getans(s)<<'\n';
	}
	return 0;//�������Ľ���
}
