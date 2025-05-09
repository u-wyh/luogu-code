// ��ɱ������
// ��� A�ķ��� >= B�ķ��� * k��k����ʵ�����ͳ� A k��ɱ B����� B��A k��ɱ��
// һ�������У�һ����n��ѡ�֣���m1�����Լ�¼����m2��ѡ�ֵ÷ּ�¼���÷�ֻ��������ʵ��
// ����1������ u v k : ѡ��u û��k��ɱ ѡ��v����ôѡ��u�ʹ�Ůװ
// ����2������ u v k : ѡ��u ��ѡ��v k��ɱ�ˣ���ôѡ��u�ʹ�Ůװ
// ѡ�ֵĵ÷�    u w : ѡ��u����w�֣����ĳѡ��û�е÷ּ�¼�����վ�������Ůװ������Ʋ�
// ��ϣ���������������˴�Ůװ�������뿴���ܶ��˴�Ůװ���������ƶ���ʵ��ans��Ч������
// ����1�����ԣ�����������(k-ans)������2�����ԣ�����������(k+ans)��������˴�Ůװ������
// ����ans�����٣���Ȼ���˴�Ůװ������С�����4λ���������ԤҲû�˴�Ůװ������-1
// 1 <= n, m1, m2 <= 1000
// 1 <= k <= 10
// 1 <= w <= 10^9
// �������� : https://www.luogu.com.cn/problem/P4926
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//����⽫�˳���ϵͨ��log��������ת��Ϊ�Ӽ�����
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1002;
const int MAXM = 3001;
const int MAXQ = 1000001;
const double INF = 1e10;
const double sml = 1e-6;

int n, m1, m2;

// ���Լ�¼(��������, u, v, k)
int vow[MAXN][4];

// �÷ּ�¼(u, w)
int score[MAXN][2];

// ��ʽǰ������Ҫ
int head[MAXN];
int Next[MAXM];
int to[MAXM];
double weight[MAXM];
int cnt;

// spfa��Ҫ
double dis[MAXN];
int update[MAXN];
queue<int>q;
int h, t;
bool enter[MAXN];

//������ʽǰ����
void addedge(int u, int v, double w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void build() {
    cnt = 1;
    fill(head, head+n + 2, 0);
    fill(enter,enter+ n + 2, false);
    fill(dis,dis+ n + 2, INF);
    fill(update,update+ n + 2, 0);
    while(!q.empty()){
        q.pop();
    }
}

bool spfa(int s) {
    dis[s] = 0;
    update[s]++;
    q.push(s) ;
    enter[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u]; ei > 0; ei = Next[ei]) {
            int v = to[ei];
            double w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //���ֵ��С��  ��ô��Ҫ�ı�
                dis[v] = dis[u] + w;
                if (!enter[v]) {
                    if (++update[v] > n+1) {
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

// �Ƿ����˴�Ůװ
bool check(double limit) {
    build();
    // 0�ŵ�����ͨ����Դ�㣬��֤ͼ����ͨ
    for (int i = 1; i <= n; i++) {
        //��ͨ����Դ��
        addedge(0, i, 0);
    }
    // ��ɱ��ϵ�Ľ���
    for (int i = 1; i <= m1; i++) {
        if (vow[i][0] == 1) {
            addedge(vow[i][1], vow[i][2], -log(-limit + vow[i][3]));
        } else {
            // ��Ϊ����2��������<��ϵ�����Լ�ȥ��С���Ⱥ󣬾Ϳ�����Ϊ��<=��ϵ
            addedge(vow[i][1], vow[i][2], log(limit + vow[i][3] - sml));
        }
    }
    // n+1�ŵ������Ƴ���Դ�㣬��֤ȷ���÷ֵ�ѡ��֮��Ĺ�ϵ
    // ��������������ޣ���������Դ��ϲ���ȻҲ��ͨ��
    // ԭ������������Դ��һ��Ҫ�ֿ������Ͻ������ص㽲��
    for (int i = 1; i <= m2; i++) {
        //�����Գ���Դ��
        addedge(n + 1, score[i][0], log(score[i][1]));
        addedge(score[i][0], n + 1, -log(score[i][1]));
    }
    return spfa(0);
}

double compute(){
    double l=0,r=INF,ans=-1;
    while(r-l>=sml){
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+sml;
        }
        else{
            r=mid-sml;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m1>>m2;
    for(int i=1;i<=m1;i++){
        cin>>vow[i][0]>>vow[i][1]>>vow[i][2]>>vow[i][3];
    }
    for(int i=1;i<=m2;i++){
        cin>>score[i][0]>>score[i][1];
    }
    double ans=compute();
    if(ans==0){
        cout<<"-1"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}
