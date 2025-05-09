// ���ʳ����
// һ����nֻ������1 ~ n��ÿֻ���ﶼ��A��B��C�е�һ�֣�A��B��B��C��C��A
// һ����k�仰��ϣ�����ж���Щ���Ǽٻ���ÿ�仰��������������е�һ��
// 1 X Y : ��Xֻ����͵�Yֻ������ͬ��
// 2 X Y : ��Xֻ����Ե�Yֻ����
// ��ǰ�Ļ���ǰ���ĳЩ�滰��ͻ����Ϊ�ٻ�
// ��ǰ�Ļ��ᵽ��X��Y�����κ�һ������n����Ϊ�ٻ�
// ��ǰ�Ļ�������ڳԣ�����X==Y����Ϊ�ٻ�
// ����k�仰�У��ٻ�������
// 1 <= n <= 5 * 10^4    1 <= k <= 10^5
// �������� : https://www.luogu.com.cn/problem/P2024
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50001;

int n,k,ans;
int fa[MAXN];
// dist[i] = 0������i��ͷ��ͬ��
// dist[i] = 1������i��ͷ
// dist[i] = 2������i��ͷ��
int dist[MAXN];

void prepare() {
    ans = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        dist[i] = 0;
        //һ��ʼ�Լ����Լ��϶���ͬ��
    }
}

int find(int i) {
    if (i != fa[i]) {
        int tmp = fa[i];
        fa[i] = find(tmp);
        dist[i] = (dist[i] + dist[tmp]) % 3;
        //���¹�ϵ�Ƚ�����
    }
    return fa[i];
}

// op == 1, 1 l r��l��r��ͬ��
// op == 2, 2 l r��l��r
void un(int op, int l, int r) {
    int lf = find(l), rf = find(r), v = op == 1 ? 0 : 1;//�ж϶��ߵĹ�ϵ
    if (lf != rf) {
        fa[lf] = rf;
        dist[lf] = (dist[r] - dist[l] + v + 3) % 3;
    }
}

bool check(int op, int l, int r) {
    if (l > n || r > n || (op == 2 && l == r)) {
        //����������  ֱ�����false
        return false;
    }
    if (find(l) == find(r)) {
        //����һ��������
        if (op == 1) {
            if (dist[l] != dist[r]) {
                return false;
            }
        } else {
            if ((dist[l] - dist[r] + 3) % 3 != 1) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    cin>>n>>k;
    prepare();
    for(int i=1,op,l,r;i<=k;i++){
        cin>>op>>l>>r;
        if(!check(op,l,r)){
            ans++;
        }
        else{
            un(op,l,r);
        }
    }
    cout<<ans<<endl;
    return 0;
}
