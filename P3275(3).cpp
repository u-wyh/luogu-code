#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;

int n,k;
int scc[MAXN],sum,low[MAXN],dfn[MAXN],cnt,tot[MAXN];
//������ǿ��ͨͼ�ıر�������Ψһtot�Ǽ�¼ÿ��ǿ��ͨ���������ж��ٸ���
int dp[MAXN];
//�������DP��¼��
int in[MAXN];
//�����¼��ȣ�����Topo
long long ans;
//���մ�
struct Node{
	int next;//��¼ÿ�������һ����
	int v;//��¼��Ȩ
};
vector<Node>nei[MAXN];//��ͼ
vector<Node>nnei[MAXN];//��ͼ
bool Stack[MAXN];//����Tarjan
stack<int> s;//����Tarjan

inline int read(){//���ٶ���
    int f = 1, x = 0;
    char c = getchar();

    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }

    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }

    return f * x;
}


void Tarjan(int u){//Tarjanģ��
	low[u] = dfn[u] = ++cnt;
	Stack[u] = true;
	s.push(u);

	int len = nei[u].size();
	for(int i = 0;i < len; i++){
		int next = nei[u][i].next;

		if(dfn[next] == 0){
			Tarjan(next);
			low[u] = min(low[u],low[next]);
		}else
		if(Stack[next]){
			low[u] = min(low[u],dfn[next]);
		}
	}

	if(dfn[u] == low[u]){
		sum++;
		scc[u] = sum;
		Stack[u] = false;
		tot[sum]++;

		while(s.top() != u){
			Stack[s.top()] = false;
			scc[s.top()] = sum;
			s.pop();
			tot[sum]++;
		}
		s.pop();
	}
}

int main()
{
	n = read(),k = read();//����

	for(int i = 1;i <= k; i++){
		int z = read(),x = read(),y = read();
		switch(z){//ʹ�ÿ��غ���
			case 1:{//һ�����
				nei[x].push_back((Node){y,0});
				nei[y].push_back((Node){x,0});
				//����һ��Ҫ�������ߣ�
				break;
			}
			case 2:{//�������
				nei[x].push_back((Node){y,1});
				break;
			}
			case 3:{//�������
				nei[y].push_back((Node){x,0});
				break;
			}
			case 4:{//�ĺ����
				nei[y].push_back((Node){x,1});
				break;
			}
			case 5:{//������
				nei[x].push_back((Node){y,0});
				break;
			}
		}
	}

	for(int i = 1;i <= n; i++){
    	if(dfn[i] == 0)Tarjan(i);//Tajan
    }

    for(int i = 1;i <= n; i++){//����ͼ
    	int len = nei[i].size();

		for(int j = 0;j < len; j++){
			int next = nei[i][j].next;
			int xx = scc[i];
        	int yy = scc[next];

        	if(xx == yy && nei[i][j].v == 1){//�ж��޽�
        		cout<<-1<<"\n";
        		return 0;
			}

        	if(xx != yy){//����ͼ
        	    nnei[xx].push_back((Node){yy,nei[i][j].v});
        	    in[yy]++;
        	}
		}
    }

    queue<int>q;//Topoģ��

    for(int i = 1;i <= sum; i++){//�����Ϊ0��ѹ�����
    	if(!in[i]){
    		q.push(i);
    		dp[i] = 1;//��ʼ��
		}
	}

	while(!q.empty()){//����ģ��
		int cur = q.front();
		q.pop();
		int len = nnei[cur].size();

		for(int i = 0;i < len; i++){
			int next = nnei[cur][i].next;
			in[next]--;
			dp[next] = max(dp[next],dp[cur] + nnei[cur][i].v);//Dp����

			if(!in[next])q.push(next);
		}
	}

	for(int i = 1;i <= sum; i++){//�ۼӴ�
		ans += (long long) dp[i] * tot[i];
	}
	cout<<ans;//���
	return 0;
}
