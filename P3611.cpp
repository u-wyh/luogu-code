#include <bits/stdc++.h>
using namespace std;
int n, m, q[1000001];
inline bool f(int x)//����x������Ŀ�е�k
{
	int y = 0;//y�������һͷţ����Ľ���ʱ��
	int ans = 0;//ans��ʱ���
	priority_queue < int, vector < int >, greater < int > > pru;//�ѵ�Ԫ�ش����ţ�Ľ���ʱ��
	for(register int i = 1; i <= x; ++i)//�Ȱ�ǰk�������ʱ��push��С������
	{
		pru.push(q[i]);//ע�⣺ֻ��������ʱ��(���ǽ���ʱ��)
	}
	for(register int i = x + 1; i <= n; ++i)
	{
		ans += pru.top() - y;//��ͷţ�Ľ���ʱ�� - ��ͷţ�Ľ���ʱ�� = �ֶ��õ�ʱ��
		y = pru.top();//��Ϊ��ͷţ�Ľ���ʱ��
		pru.pop();//�����Ѿ��������ţ
		pru.push(q[i] + y);//ע�⣺Ҫ����y������ͷţ�Ľ���ʱ��(��ͷţ�Ľ���ʱ�� + ��ͷţ������Ҫ��ʱ�� = ��ͷţ�Ľ���ʱ��)
		if(ans > m)//���ܴ������ֵ
		{
			return false;
		}
	}
	while(x--)//����k��û������(��������ʱ��)
	{
		ans += pru.top() - y;//��Щ��������ͬ
		y = pru.top();
		pru.pop();
		//pru.push(q[i] + y);���ﲻ�ܼӣ���Ϊ�Ѿ�û��ţ���ڵȴ�������(�����ѭ�����Ƕ������ˣ���������ţ��������������Ѿ�������)
		if(ans > m)
		{
			return false;
		}
	}
	return ans <= m;//��ʵ����ֱ��return true�ͺ���
}
inline int half()//����
{
	int l = 0;
	int r = 100000;//�����
	int ans = 0;//���Ĵ�
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(f(mid))
		{
			ans = mid;//mid����
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
	//sort(q + 1, q + n + 1);���ﲻҪ������Ϊ��Ŀ��˵���밴ţ���赸�г��ֵ�˳������(1 ~ n)
	printf("%d", half());
	return 0;
}
