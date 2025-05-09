// �濵��չ��   �߶�����
// ���ִ�1��n�������кܶ����У�����һ������Ϊn������s����ʾ�����һ������
// ���������е���������Ϊx����ӡ��x+m����������ʲô
// 1 <= n <= 10^5
// 1 <= m <= 10^15
// ��Ŀ��֤s��һ����1~n������ɵ���ȷ���У���Ŀ��֤x+m���ᳬ�����е�����
// �������� : https://www.luogu.com.cn/problem/U72177
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long long arr[MAXN];
// �߶���
int sum[MAXN << 2];
int n;
long m;

// ��ʼ���߶��������㷶Χ�ĳ�ʼ�ۼӺ�Ϊ1����Ϊ�������ֶ�����
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// ����jobi�ϣ�����jobv����Ϊ�ǵ�����£����Բ���Ҫ���������»���
void add(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        sum[i] += jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobi, jobv, l, mid, i << 1);
        } else {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// ��ѯjobl~jobr��Χ���ۼӺ�
int Sum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans += Sum(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += Sum(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

// �߶������ҵ���k������ʲô���ҵ���ɾ����Ƶ�����صĹ����޸��ۼӺ�
// ע������������������е�����
int getAndDelete(int k, int l, int r, int i) {
    int ans;
    if (l == r) {
        //�ҵ�Ŀ�� ɾ����Ƶ
        sum[i]--;
        ans = l;
    } else {
        int mid = (l + r) >> 1;
        if (sum[i << 1] >= k) {
            ans = getAndDelete(k, l, mid, i << 1);
        } else {
            ans = getAndDelete(k - sum[i << 1], mid + 1, r, i << 1 | 1);
            //Ҫ��ȥ���������Ӱ��
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        //���صĹ����޸��ۼӺ�
    }
    return ans;
}

void compute() {
    // ������ʼ���߶���
    build(1, n, 1);
    // ��ǰ����ת��Ϊ�׳˽��Ƶ�����
    for (int i = 1, x; i <= n; i++) {
        x = (int) arr[i];
        if (x == 1) {
            arr[i] = 0;
        } else {
            arr[i] = Sum(1, x - 1, 1, n, 1);
        }
        //arr�����ʾһ��ʼ�������ڽ׳˽����µ�����
        add(x, -1, 1, n, 1);
        //����������ֵ�Ӱ��
    }
    // ��ǰ��������m֮�󣬵õ��µ��������ý׳˽��Ʊ�ʾ
    arr[n] += m; // ���λ������ӵķ���
    for (int i = n; i >= 1; i--) {
        // ���Ͻ�λ����
        arr[i - 1] += arr[i] / (n - i + 1);
        // ��ǰλ�Ƕ���
        arr[i] %= n - i + 1;
    }
    //������ʱ  arr���������Ǽ���m��������ڽ׳˽����µı�ʾ
    // ���ݽ׳˽���ת��Ϊ���������
    build(1, n, 1);
    //���߶������¸�ԭ
    for (int i = 1; i <= n; i++) {
        arr[i] = getAndDelete((int) arr[i] + 1, 1, n, 1);
        //��ʱ���arr���������������
    }
}

int main()
{
    cin>>n>>m;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
    }
    compute();
    for (int i = 1; i <= n; i++) {
        cout<<arr[i] <<" ";
    }
    return 0;
}
