//P3388
// �����жϸ��ķ����ǣ�
// 1.���������Ǹ��ڵ�  ��ô���������������  ����һ���Ǹ��
// �������������ָ������������������������µ���������  �����������ӵ�����һ���ǻ�����ɵ�  
// ��������һ�����ӵ�����һ�����������һ������
// 2.�������ڵ㲻�Ǹ��ڵ㣬���Ҳ���Ҷ�ӽ�� ����low[��������һ������]>=dfn[��]  �����Ǹ��
// �����Ҷ�ڵ�  ��ô�������Ǹ�� 
// �����������к��Ӳ��ܵ�����������  ���������˺������ϵ�ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

vector<int>vec[MAXN];
//�ڸ���ʱ��  dfn������������ ����lowȴ����������ڵ���Ե������С�����
//�������ʱ��ͬ
int dfn[MAXN],low[MAXN];
int Time;
bool cut[MAXN];
bool instack[MAXN];
int n,m;

// v:��ǰ�� r��������������root
void tarjan(int u,int r) {
	dfn[u] = low[u] = ++Time;
	int child = 0;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (!dfn[v]) {
			tarjan(v, r);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] && u != r)
                cut[u] = true;//���Ǹ��������ĺ����޷���Խ���ص�����
			if (r == u){
                child++; //������������ĸ���ͳ�ƺ�����Ŀ
                //��ʵ���еĽڵ㶼����ͳ�ƺ��ӵ����� ���ǷǸ��ڵ�ͳ�ƺ�û��ʲô����
            }
		}
		low[u] = min(low[u], dfn[v]);//����Ҫ�ر�ע�� ���ܱ��low[v]
        // �ٸ����� ����a-b-c-d-b  ���һ�����b-e-a
        // ��ô����b��һ�����  ��������ĳ�low[v] ��ôlow[d]=dfn[a]  ����b�޷���Ϊһ�����
	}
	if (child >= 2 && u == r){
        cut[r] = true;//��Ӧ��һ�����
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            ans++;
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            cout<<i<<' ';
        }
    }
    return 0;
}
