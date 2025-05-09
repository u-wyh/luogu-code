// �Ƶ����ֺͣ���Ȩ���鼯ģ����1
// ��n�����֣��±�1 ~ n�����ǲ���֪��ÿ�������Ƕ���
// �ȸ���m�����ֶε��ۼӺͣ��ٲ�ѯq�����ֶε��ۼӺ�
// �������ֶ��ۼӺ͵Ĳ��� l r v������l~r��Χ�ϵ����֣��ۼӺ�Ϊv
// ��ѯ���ֶ��ۼӺ͵Ĳ��� l r�������ѯl~r��Χ�ϵ������ۼӺ�
// �����m�����������q����ѯ�����ĳ����ѯ�޷������𰸣���ӡ"UNKNOWN"
// 1 <= n, m, q <= 10^5
// �ۼӺͲ��ᳬ��long���ͷ�Χ
// �������� : https://www.luogu.com.cn/problem/P8779
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+2;

int n,m,q;
int fa[MAXN];
long long dist[MAXN];

//��ʼ����Ȩ���鼯
void prepare() {
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

void un(int l, int r, long long v) {
    int lf = find(l), rf = find(r);
    if (lf != rf) {
        fa[lf] = rf;//ǿ��Ҫ�����Ľڵ���Ϊ����
        dist[lf] = v + dist[r] - dist[l];
    }
}

long long query(int l, int r) {
    if (find(l) != find(r)) {
        //����һ��������
        return LLONG_MAX;
    }
    return dist[l] - dist[r];
}

int main()
{
    cin>>n>>m>>q;
    prepare();
    int l,r;//���ǽ���Щ��������  ÿ��r++
    long long v;
    for(int i=1;i<=m;i++){
        cin>>l>>r>>v;
        r++;
        un(l,r,v);
    }
    for (int i = 1; i <= q; i++) {
        cin>>l>>r;
        r++;
        v = query(l, r);
        if (v == LLONG_MAX) {
            cout<<"UNKNOWN"<<endl;
        } else {
            cout<<v<<endl;
        }
    }
    return 0;
}
