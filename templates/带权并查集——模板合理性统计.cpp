// �������������Ȩ���鼯ģ����3
// ��n�����֣��±�1 ~ n�����ǲ���֪��ÿ�������Ƕ���
// ���� l r v������l~r��Χ���ۼӺ�Ϊv
// һ��m�����������ĳ��������֮ǰ�Ĳ�����Ϣ����ì�ܣ���Ϊ��ǰ�����Ǵ���ģ��������������
// ����ӡ�������������
// 1 <= n <= 200000    1 <= m <= 40000
// �ۼӺͲ��ᳬ��int���ͷ�Χ
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=3038
// �������� : https://vjudge.net/problem/HDU-3038
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<iostream>
using namespace std;
const int MAXN = 200002;

int n,m,ans;
int fa[MAXN];
int dist[MAXN];

//��ʼ����Ȩ���鼯
void prepare() {
    ans=0;
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        dist[i] = 0;
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

void un(int l, int r, int v) {
    int lf = find(l), rf = find(r);
    if (lf != rf) {
        fa[lf] = rf;//ǿ��Ҫ�����Ľڵ���Ϊ����
        dist[lf] = v + dist[r] - dist[l];
    }
}

//���ڼ���Ƿ�����߼�����  �Բ��ϵ����
bool check(int l, int r,int v) {
    if (find(l) == find(r)) {
        if ((dist[l] - dist[r]) != v) {
            return false;
        }
    }
    return true;
}

int main()
{
    while(cin>>n>>m){
        n++;
        prepare();
        for (int i = 1, l, r, v; i <= m; i++) {
            cin>>l>>r>>v;
            r++;
            if (!check(l, r, v)) {
                ans++;
            } else {
                un(l, r, v);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
