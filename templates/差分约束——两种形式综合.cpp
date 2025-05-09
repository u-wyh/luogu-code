// ������ţ
// ���1�����n����ţ��������վ��һ�ţ�����Ծ�������������ţ֮��ľ���
// ��m1��������Ϣ����m2�������Ϣ�����Ѽ�ϣ�������������м�ϣ�������Զ
// ÿ��������ϢΪ : u v w����ʾϣ��u��v֮��ľ��� <= w�����뱣֤u < v
// ÿ�������ϢΪ : u v w����ʾϣ��u��v֮��ľ��� >= w�����뱣֤u < v
// ����Ҫ������ţ�Ĳ��֣��������еĺ�����Ϣ�������Ϣ
// ��������ںϷ�����������-1
// ������ںϷ�����������1����ţ��n����ţ֮���������
// ������ںϷ�����������1����ţ��n����ţ֮��ľ����������Զ������-2
// �������� : https://www.luogu.com.cn/problem/P4878
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 20005;

// ��ʽǰ���ǽ�ͼ��Ҫ
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int n,m,k;
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
    //fill(head+1, head+n + 1, 0);
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

int spfa(int s) {
    build();
    dis[s] = 0;
    updateCnt[s]++;
    q.push(s) ;
    enter[s] = true;
    //�����Ŀ�е�Դ�㶼��0 ���ֲ���   �������ϵĲ��������1
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
                    if (++updateCnt[v] > n) {
                        return -1;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    if(dis[n]==INT_MAX)
        return -2;
    return dis[n];
}


int main()
{
    cin>>n>>m>>k;
    for(int i=2;i<=n;i++){
        addEdge(i,i-1,0);//��֤������һ��վ  ����i-1��<=��i��-0
    }
    for(int i=1;i<=n;i++){
        addEdge(0,i,0);//�ͳ���Դ������
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);//��ʽһ������
    }
    for(int i=1;i<=k;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(v,u,-w);//��ʽ��������
    }
    int ans=spfa(0);//�ж��Ƿ����ì��  �Ƿ���ڸ���
    if(ans==-1){
        cout<<ans;
    }
    else{
        ans=spfa(1);
        cout<<ans<<endl;
    }
    return 0;
}