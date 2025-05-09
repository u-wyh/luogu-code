// ������C++��
// ����nֻ���ӵ�ս������һ��ʼÿ�����Ӷ��Ƕ�������Ӫ
// һ����m�γ�ͻ��ÿ�γ�ͻ������ֻ���ӵı��x��y
// ���x��y��ͬһ��Ӫ����γ�ͻֹͣ����ӡ-1
// ���x��y�ڲ�ͬ��Ӫ��x������Ӫ����ǿ���ӻ��y������Ӫ����ǿ���ӽ��д�
// �򶷵Ľ���ǣ�����������Ӫ����ǿ���ӣ�ս���������룬����ȡ������������ս������
// Ȼ��������Ӫ�ϲ�����ӡ�ϲ������Ӫ���ս����
// ��Ŀ�����ж������ݣ���Ҫ���������ֱ������
// 1 <= n, m <= 10^5
// 0 <= ����ս���� <= 32768
// �������� : https://www.luogu.com.cn/problem/P1456
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;
int num[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// father[i]��ʾ���鼯��ڵ�i��·����Ϣ
int fa[MAXN];

void prepare() {
    dist[0] = -1;
    for (int i = 1; i <= n; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i) {
    return fa[i] == i ? i : (fa[i] = find(fa[i]));
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    int tmp;
    if (num[i] < num[j] || (num[i] == num[j] && i > j)) {
        tmp = i; i = j; j = tmp;
    }
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]]) {
        tmp = ls[i]; ls[i] = rs[i]; rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

// �ڵ�iһ������ƫ����ͷ������ƫ����ɾ���ڵ�i������������ͷ�ڵ���
int pop(int i) {
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    // ���鼯��·��ѹ��������i�·���ĳ���ڵ�x��������father[x] = i
    // ����Ҫɾ��i�ˣ�����x���ϻ��Ҳ�����ȷ��ͷ�ڵ�
    // Ϊ���κνڵ����϶����ҵ���ȷ��ͷ������Ҫ���������
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

int fight(int x,int y){
    int a=find(x);
    int b=find(y);
    if(a==b){
        return -1;
    }
    int l=pop(a);
    int r=pop(b);
    num[a]/=2;
    num[b]/=2;
    fa[a]=fa[b]=fa[l]=fa[r]=merge(merge(a,l),merge(b,r));
    return num[fa[a]];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n){
        prepare();
        for(int i=1;i<=n;i++){
            cin>>num[i];
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int a,b;
            cin>>a>>b;
            cout<<fight(a,b)<<endl;
        }
    }
    return 0;
}
