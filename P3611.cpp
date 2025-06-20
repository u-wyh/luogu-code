#include <bits/stdc++.h>
using namespace std;
int n, m, q[1000001];
inline bool f(int x)//这里x就是题目中的k
{
	int y = 0;//y存的是上一头牛跳舞的结束时间
	int ans = 0;//ans存时间和
	priority_queue < int, vector < int >, greater < int > > pru;//堆的元素存的是牛的结束时间
	for(register int i = 1; i <= x; ++i)//先把前k个跳舞的时间push进小根堆中
	{
		pru.push(q[i]);//注意：只有这里是时间(不是结束时间)
	}
	for(register int i = x + 1; i <= n; ++i)
	{
		ans += pru.top() - y;//这头牛的结束时间 - 上头牛的结束时间 = 又多用的时间
		y = pru.top();//改为这头牛的结束时间
		pru.pop();//弹出已经跳完舞的牛
		pru.push(q[i] + y);//注意：要加上y才是这头牛的结束时间(上头牛的结束时间 + 这头牛跳舞需要的时间 = 这头牛的结束时间)
		if(ans > m)//不能大于最大值
		{
			return false;
		}
	}
	while(x--)//还差k个没有跳舞(加上跳舞时间)
	{
		ans += pru.top() - y;//这些和上面相同
		y = pru.top();
		pru.pop();
		//pru.push(q[i] + y);这里不能加，因为已经没有牛还在等待跳舞了(上面的循环他们都跳完了，现在所有牛不是在跳舞就是已经跳完了)
		if(ans > m)
		{
			return false;
		}
	}
	return ans <= m;//其实这里直接return true就好了
}
inline int half()//二分
{
	int l = 0;
	int r = 100000;//开大点
	int ans = 0;//最后的答案
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(f(mid))
		{
			ans = mid;//mid可行
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	return ans;
}
int main()
{
	scanf("%d %d", &n, &m);
	for(register int i = 1; i <= n; ++i)
	{
		scanf("%d", &q[i]);
	}
	//sort(q + 1, q + n + 1);这里不要排序，因为题目中说必须按牛在舞蹈中出现的顺序跳舞(1 ~ n)
	printf("%d", half());
	return 0;
}
