// ����Ӣ�۴�˵
// һ����30000��ս�������1~30000��һ��ʼÿ��ս�����Գ�һ��
// �������ս�����һ�ӣ���ô�����������ս����ֱ���ų�һ��
// ʵ���������ֲ���������һ������t��
// M l r : �ϲ�l��ս�����ڶ����r��ս�����ڶ���
//         l��ս���Ķ��飬�����ƶ�����r��ս�����ڶ������ĩβս���ĺ���
//         ���l��ս����r��ս���Ѿ���һ�ӣ��������κβ���
// C l r : ���l��ս����r��ս������һ�����飬��ӡ-1
//         ���l��ս����r��ս����һ�����飬��ӡ�����м���ż���ս��
// 1 <= t <= 5 * 10^5
// �������� : https://www.luogu.com.cn/problem/P1196
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30001;

int n=30000;
int fa[MAXN];
int dist[MAXN];
int sz[MAXN];

//��ʼ����Ȩ���鼯
void prepare() {
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        dist[i] = 0;
        sz[i]=1;
    }
}

//Ѱ��i�ڵ�ĸ��� ��ƽ������  ���ڸù����и��¾���
int find(int i) {
    if (i != fa[i]) {
        int tmp = fa[i];
        fa[i] = find(tmp);
        dist[i] += dist[tmp];//�����������ȷ
    }
    return fa[i];
}

void un(int l, int r) {
    int lf = find(l), rf = find(r);
    if (lf != rf) {
        fa[lf] = rf;//ǿ��Ҫ�����Ľڵ���Ϊ����
        dist[lf] += sz[rf];
        sz[rf] += sz[lf];
    }
}

int query(int l, int r) {
    if (find(l) != find(r)) {
        //����һ��������
        return -1;
    }
    return abs(dist[l] - dist[r])-1;
}

int main()
{
    prepare();
    int t;
    cin>>t;
    for(int i=1,l,r;i<=t;i++){
        char op;
        cin>>op>>l>>r;
        if(op=='M'){
            un(l,r);
        }
        else{
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}
