// Bellman-Ford + SPFA�Ż�ģ�棨��ȣ�
// ����n���������ͼ�������ͼ���Ƿ���ڴӶ���1�����ܵ���ĸ���
// �����Ķ����ǣ�һ����Ȩ֮��Ϊ�����Ļ�·
// �������� : https://www.luogu.com.cn/problem/P3385
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ�������д��룬���������ĳ�Main������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2001;
const int MAXM = 6001;
// SPFA��Ҫ
const int MAXQ = 4000001;

// ��ʽǰ���ǽ�ͼ��Ҫ
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m;
//n��ʾһ���ж��ٸ���  m��ʾһ���ж�����·��
// Դ�������ÿ���ڵ�ľ����
int dis[MAXN];
// �ڵ㱻�ɳڵĴ���
int updateCnt[MAXN];
bool enter[MAXN];
//��ǰ�ڶ����еĻ�  ����true  �������false
queue<int >q;
//ÿһ�ֶ�����������һ��  ���һ������Ա��Ż�  ��ô�������

void build() {
    cnt = 1;
    fill(head+1, head+n + 1, 0);
    fill(enter+1,enter+ n + 1, false);
    fill(dis+ 1,dis+ n + 1, INT_MAX);
    fill(updateCnt+1,updateCnt+ n + 1, 0);
    while(!q.empty()){
        q.pop();
    }
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}
//������ʽǰ����

bool spfa() {
    dis[1] = 0;
    updateCnt[1]++;
    q.push(1) ;
    enter[1] = true;
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
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        build();
        for(int i=1;i<=m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            if (w >= 0) {
                addEdge(u, v, w);
                addEdge(v, u, w);
            } else {
                addEdge(u, v, w);
            }
            //������ĿҪ��ͼ
        }

        if(spfa()){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
    return 0;
}
