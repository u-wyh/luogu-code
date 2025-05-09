#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int p;
int mxdep;

bool dfs(int x ,int y ,int dep)
{
	if (x < y) //��ֹ����x-y���ָ��� 
	{
		swap(x ,y);
	}
	if (dep >= mxdep)
	{
		if (x == p || y == p) //x��y��һ������p������ 
		{
			return true;
		}
		return false;
	}
	if (x << (mxdep - dep) < p) //��֦1 
	{
		return false;
	}
	if (__gcd(x ,y) > 0 && p % __gcd(x ,y) != 0) //��֦2 
	{
		return false;
	}
	
	//���۶������ 
	//�� 
	if (dfs(x * 2 ,y ,dep + 1)) return true;
	if (dfs(x * 2 ,x ,dep + 1)) return true;
	if (dfs(x ,y * 2 ,dep + 1)) return true;
	if (dfs(y ,y * 2 ,dep + 1)) return true;
	if (dfs(x + y ,x ,dep + 1)) return true;
	if (dfs(x + y ,y ,dep + 1)) return true;
	//�� 
	if (dfs(x - y ,x ,dep + 1)) return true;
	if (dfs(x - y ,y ,dep + 1)) return true;
	return false;
}

int main()
{
	scanf("%d",&p);
	
	//��֮ǰһ�� 
	while (!dfs(1 ,0 ,0))
	{
		mxdep++;
	}
	
	printf("%d\n",mxdep);
	
	return 0;
}