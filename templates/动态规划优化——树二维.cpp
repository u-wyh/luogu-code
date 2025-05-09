// ��������������
// ����һ������Ϊn������arr
// ÿ�ο���ѡ��һ������[l,r]�������ڵ����ֶ�+1�����ִ��k��
// ����ִ����ɺ���Ĳ��½������г���
// 1 <= n <= 10^4
// 1 <= arr[i] <= 5000
// 2 <= k <= 500
// �������� : https://www.luogu.com.cn/problem/P3287
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10001;
const int MAXK = 501;
const int MAXH = 5500;

int arr[MAXN];
int tree[MAXH + 1][MAXK + 1];
int n, k;

void update(int x, int y, int v) {
	for (int i = x; i <= MAXH; i += i & -i) {
		for (int j = y; j <= k + 1; j += j & -j) {
			tree[i][j] = max(tree[i][j], v);
		}
	}
}

int querymax(int x, int y) {
	int ans = 0;
	for (int i = x; i > 0; i -= i & -i) {
		for (int j = y; j > 0; j -= j & -j) {
			ans = max(ans, tree[i][j]);
		}
	}
	return ans;
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    // ע������ڶ���forѭ����jһ���Ǵ�k~0��ö��
    // ���Ͻ������ص�ͼ�⣬��ֹͬһ��i�����ļ�¼֮���໥Ӱ��
    int v, dp;
    for (int i = 1; i <= n; i++) {
        for (int j = k; j >= 0; j--) {
            v = arr[i] + j;
            // �޸Ĵ���j����״�����ж�Ӧ���±���j+1
            dp = querymax(v, j + 1) + 1;
            update(v, j + 1, dp);
        }
    }
    // �޸Ĵ���k����״�����ж�Ӧ���±���k+1
    cout<<querymax(MAXH, k + 1);

    return 0;
}
