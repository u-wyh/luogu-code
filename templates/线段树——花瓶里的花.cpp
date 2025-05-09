// ƿ����Ļ���
// ����n��ƿ�ӣ���Ŵ�0~n-1��һ��ʼ����ƿ�Ӷ��ǿյ�
// ÿ��ƿ��������һ�仨��ʵ�������������͵Ĳ���
// ���� 1 from flower : һ����flower�仨����fromλ�ÿ�ʼ���β��뻨�䣬�Ѿ��л���ƿ������
//                     ���һֱ������ƿ�ӣ���Ҳû�����꣬�Ͷ���ʣ�µĻ���
//                     ������β���������׸���ƿ��λ�� �� ����ƿ��λ��
//                     �����from��ʼ����ƿ�Ӷ��л�����ӡ"Can not put any one."
// ���� 2 left right  : ��leftλ�ÿ�ʼ��rightλ�õ�ƿ�ӣ���ؿ�ƿ�����������������
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=4614
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int arr[MAXN];
int sum[MAXN << 2];
int change[MAXN << 2];
bool update[MAXN << 2];
int n,m;
int ans[2];

// �ۼӺ���Ϣ�Ļ���
void up(int i) {
    // ����Χ���ۼӺ� = ��Χ�ۼӺ� + �ҷ�Χ�ۼӺ�
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

// ��ǰ�������Ӧ����Ϣ�±���i
// �����յ�һ������������ : ������䷶Χ��ÿ�����ֱ�Ϊv
// ��������������п���������Χ�ѵ�ǰ�߶�����Χȫ���ǵ��µ�
// Ҳ�п����Ǹ���Χ������Ϣ�·�������
// ��֮���߶�����ǰ��Χ��sum�����change   update���������
// �Ͳ��ټ��������·��ˣ���ס��
void lazy(int i, long v, int n) {
    sum[i] = v * n;
    change[i] = v;
    update[i] = true;
}

// ����Ϣ���·�
void down(int i, int ln, int rn) {
    if (update[i]) {
        lazy(i << 1, change[i], ln);
        lazy(i << 1 | 1, change[i], rn);
        update[i] = false;
    }
}

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    sum[i] = 0;
    update[i] = false;
}

// ��Χ�޸�
// jobl ~ jobr��Χ��ÿ�����ֱ�Ϊjobv
void Update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int findZero(int s, int k) {
    int l = s, r = n, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (mid - s + 1 - query(s, mid, 1, n, 1) >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int Clear(int left, int right) {
    left++;
    right++;
    int ans = query(left, right, 1, n, 1);
    Update(left, right, 0, 1, n, 1);
    return ans;
}

void Insert(int from, int flowers) {
    // ��Ŀ����λ�ô�0��ʼ
    // �߶����±��1��ʼ
    from++;
    int zeros = n - from + 1 - query(from, n, 1, n, 1);
    if (zeros == 0) {
        ans[0] = 0;
        ans[1] = 0;
    } else {
        ans[0] = findZero(from, 1);
        ans[1] = findZero(from, min(zeros, flowers));
        Update(ans[0], ans[1], 1, 1, n, 1);
    }
    // ��Ŀ��Ҫ��0��ʼ���±�
    ans[0]--;
    ans[1]--;
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    long jobv;
    for (int i = 1, op; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            int from;
            int flowers;
            cin>>from;
            cin>>flowers;
            Insert(from,flowers);
            if(ans[0]==-1){
                printf("can not put any one\n");
            }else{
                cout<<ans[0]<<' '<<ans[1]<<endl;
            }
        } else {
            int left,right;
            cin>>left>>right;
            cout<<Clear(left,right)<<endl;
        }
    }
    return 0;
}
