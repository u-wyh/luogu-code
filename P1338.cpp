#include <bits/stdc++.h>
using namespace std;
long long n,m;    //ĳ���Ե�Ҫ��long long���ܹ�
void solve_ (int x,int y) {    //��ʾ�������xλ��������y����������xλ������ݹ�
	for (int i=n;i>x;i--) {
		cout << (n-i+1) << ' ';    //��xλǰ����������������
	}
	cout << (n-y) << ' ';    //��xλ���ʣ��x�����е�y�����
	for (int i=n;i>=(n-x+1);i--) {
		if (i!=(n-y)) {
			cout << i << ' ';    //���x-1�������������ע����һ���Ƿ���ǰ�������
		}
	}
	return;
}
int main () {
	cin >> n >> m;
	if (m==0) {    //0������
		for (int i=1;i<=n;i++) {
			cout << i << ' ';
		}
		return 0;
	}
	for (long long i=2;i<=n;i++) {
		if ((i*(i-1))/2>=m&&((i-1)*(i-2))/2<m) {
			solve_(i,(i*(i-1))/2-m);
			break;
		}
	}
	return 0;
}
