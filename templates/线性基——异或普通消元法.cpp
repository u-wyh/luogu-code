// �������
// ����һ������Ϊn������arr��arr�ж���long���͵ķǸ������������ظ�ֵ
// ����Щ����ѡȡ�������ʹ��������󣬷�����������
// 1 <= n <= 50
// 0 <= arr[i] <= 2^50
// �������� : https://www.luogu.com.cn/problem/P3812
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 51;
const int BIT = 50;

long arr[MAXN];
long basis[BIT + 1];
int n;

// ���Ի������num��������Ի������˷���true�����򷵻�false
bool insert(long num) {
	for (int i = BIT; i >= 0; i--) {
		if (num >> i == 1) {
			if (basis[i] == 0) {
				basis[i] = num;
				return true;
			}
			num ^= basis[i];
		}
	}
	return false;
}

// ��ͨ��Ԫ
// �����������
long compute() {
	for (int i = 1; i <= n; i++) {
		insert(arr[i]);
	}
	long ans = 0;
	for (int i = BIT; i >= 0; i--) {
		ans = max(ans, ans ^ basis[i]);
	}
	//�������ʹ������  ��ô��������������
	return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cout<<compute()<<endl;
    return 0;
}
