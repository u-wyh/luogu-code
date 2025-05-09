// ������Ԫ������
// ����һ������arr�����i < j < k��arr[i] < arr[j] < arr[k]
// ��ô��(i, j, k)Ϊһ��������Ԫ��
// ����arr��������Ԫ�������
// �������� : https://www.luogu.com.cn/problem/P1637
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
//��ʵ����⻹�Ǻ�����ս��  ��һ����˼ά�Ѷ�  �Ƚϲ���
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 30001;
int arr[MAXN];
int Sort[MAXN];
// ά����Ϣ : ���Ͻ���up1����
// tree1����up1���飬��up1�������״����
long tree1[MAXN];
// ά����Ϣ : ���Ͻ���up2����
// tree2����up2���飬��up2�������״����
//�ٸ�����˵������ ��tree[2]ʵ������up[2]up[1]�Ľ��
long tree2[MAXN];
int n, m;

int lowbit(int i) {
    return i & -i;
}

void add(long* tree, int i, long c) {
    while (i <= m) {
        tree[i] += c;
        i += lowbit(i);
    }
}

long sum(long* tree, int i) {
    long ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int Rank(int v) {
    int l = 1, r = m, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (Sort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

long compute() {
    sort(Sort+1, Sort+n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (Sort[m] != Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        arr[i] = Rank(arr[i]);
    }
    long ans = 0;
    for (int i = 1; i <= n; i++) {
        // ��ѯ�Ե�ǰֵ����β��������Ԫ������
        ans += sum(tree2, arr[i] - 1);
        // �����Ե�ǰֵ����β������һԪ������  ��ʵ����ǰ��С���Լ������ֵ�����
        add(tree1, arr[i], 1);
        // �����Ե�ǰֵ����β�������Ԫ������
        add(tree2, arr[i], sum(tree1, arr[i] - 1));
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        Sort[i]=arr[i];//��������  ���������ȥ��
    }
    cout<<compute();
    return 0;
}