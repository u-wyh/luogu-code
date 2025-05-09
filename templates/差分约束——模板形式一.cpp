// �����Ͳ��Լ��ģ����(ת������ʽ1����ת�����жϸ���)
// һ����n�����������1~n������m������ʽ��ÿ������ʽ����ʽΪ
// Xi - Xj <= Ci������Xi��XjΪ������CiΪ����
// �������ʽ����ì�ܵ����޽⣬��ӡ"NO"
// ����н⣬��ӡ�������в���ʽ������һ���(X1, X2...)
// 1 <= n��m <= 5 * 10^3
// -10^4 <= Ci <= +10^4
// �������� : https://www.luogu.com.cn/problem/P5960
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 10005;

// ��ʽǰ���ǽ�ͼ��Ҫ
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
//n��ʾһ���ж��ٸ���  m��ʾһ���ж�����·��
int n,m;
// Դ�������ÿ���ڵ�ľ����
int dis[MAXN];
// �ڵ㱻�ɳڵĴ���
int updateCnt[MAXN];
//��ǰ�ڶ����еĻ�  ����true  �������false
bool enter[MAXN];
//ÿһ�ֶ�����������һ��  ���һ������Ա��Ż�  ��ô�������
queue<int >q;

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

//������ʽǰ����
void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool spfa() {
    dis[0] = 0;
    updateCnt[0]++;
    q.push(0) ;
    enter[0] = true;
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
                    //�������Ǽ�����һ������Դ��  �����ܵ�����һ
                    if (++updateCnt[v] > n) {
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

int main()
{
    cin>>n>>m;
    build();//ȫ���ʼ��
    for(int i=1;i<=n;i++){
        addEdge(0,i,0);//����Դ�㽨��
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(v,u,w);
        // ��ʽ1�����߷�ʽ  u<=v+w  ��v��u��һ��ȨֵΪw�ı�
    }
    if(spfa()){
        cout<<"NO"<<endl;
    }else{
        for(int i=1;i<=n;i++)
            cout<<dis[i]<<' ';
    }
    return 0;
}
