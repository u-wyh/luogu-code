// �ƻ������ˣ���Ȩ���鼯ģ����2
// ��n���µ����룬�±�1 ~ n�����ǲ���֪��ÿ���������Ƕ���
// ���� l r v������ӵ�l���µ���r���£�������Ϊv
// һ������m�����������жϸ�������������Ǣ��������ì��
// ��Ǣ��ӡtrue������ì�ܴ�ӡfalse
// 1 <= n <= 100    1 <= m <= 1000
// �����벻�ᳬ��int���ͷ�Χ
// �������� : https://www.luogu.com.cn/problem/P2294
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 102;

int n,m,t;
int fa[MAXN];
int dist[MAXN];
bool ans;

//��ʼ����Ȩ���鼯
void prepare() {
    ans=true;
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
    cin>>t;
    while(t--){
        cin>>n>>m;
        n++;
        prepare();
        for (int i = 1, l, r, v; i <= m; i++) {
            cin>>l>>r>>v;
            r++;
            if (!check(l, r, v)) {
                ans = false;
                //��ʹ����������Ҳ����ֹͣ   ��Ҫ�����е����ݶ���
            } else {
                un(l, r, v);
            }
        }
        if(ans){
            cout<<"true"<<endl;
        }
        else{
            cout<<"false"<<endl;
        }
    }
    return 0;
}
