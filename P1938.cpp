#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250;
const int MAXM = 1000;
// SPFA��Ҫ
const int MAXQ = 4000001;

// ��ʽǰ���ǽ�ͼ��Ҫ
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m,d,k,st;
//n��ʾһ���ж��ٸ���  m��ʾһ���ж�����·��
// Դ�������ÿ���ڵ�ľ����
int dis[MAXN];
// �ڵ㱻�ɳڵĴ���
int updateCnt[MAXN];
bool enter[MAXN];
//��ǰ�ڶ����еĻ�  ����true  �������false
queue<int >q;
//ÿһ�ֶ�����������һ��  ���һ������Ա��Ż�  ��ô�������

bool spfa() {
    dis[st] = -d;
    updateCnt[st]++;
    q.push(st) ;
    enter[st] = true;
    //�����Ŀ�е�Դ�㶼��1 ���ֲ���   �������ϵĲ��������1
    //ʵ����Ӧ�����Ϊ�����Դ���
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u], v, w; ei > 0; ei = Next[ei]) {
            v = to[ei];
            w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //���ֵ��С��  ��ô��Ҫ�ı�
                dis[v] = dis[u] + w;
                if (!enter[v]) {
                    //������ڶ����вŻ����
                    // �ɳڴ�������n-1���и���
                    if (++updateCnt[v] > n - 1) {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}
//�������������  ���Եõ�����㵽�κ�λ�õ����·��
//���������Ϊ���ж����ͼ����û�д�ԭ����������ĸ���

int main()
{
    cin>>d>>m>>n>>k>>st;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=-d;
        head[u]=cnt++;
    }
    for(int i=1;i<=k;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w-d;
        head[u]=cnt++;
    }
    if(spfa()){
        cout<<-1;
        return 0;
    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        ans=min(ans,dis[i]);
    }
    cout<<-ans;
    return 0;
}

