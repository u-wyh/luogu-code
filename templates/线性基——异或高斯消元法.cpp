// ��kС������
// ����һ������Ϊn������arr��arr�ж���long���͵ķǸ������������ظ�ֵ
// ����Щ����ѡȡ�����������Ҫѡһ������
// ���Եõ��ܶ����ͣ��������͵Ľ��ȥ��
// ���ص�kС������
// 1 <= n <= 10^5
// 0 <= arr[i] <= 2^50
// 1 <= k <= 2^50
// �������� : https://loj.ac/p/114
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int BIT = 50;

long arr[MAXN];
int len;
bool zero;
int n;

void swap(int a, int b) {
    long long tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

//����Ǹ�˹��Ԫ��  �õ����Ǳ�׼���Ի�
void compute() {
    len = 1;
    for (int i = BIT; i >= 0; i--) {
        for (int j = len; j <= n; j++) {
            if (arr[j] & (1LL << i)) {
                swap(j, len);
                break;
            }
        }
        if (arr[len] & (1LL << i)) {
            for (int j = 1; j <= n; j++) {
                if (j != len && (arr[j] & (1LL << i))) {
                    arr[j] ^= arr[len];
                }
            }
            len++;
        }
    }
    len--;
    zero = len != n;
}

// ���ص�kС������
long query(long k) {
	if (zero && k == 1) {
        //�����0  ���Ҳ�ѯ��һС������
        //��ôֱ�ӷ���0�ͺ���
		return 0;
	}
	if (zero) {
	    //�����0  ��ôk��Ҫ��1
	    //��Ϊ����ͳ�Ƶ������󲻲���0�����Ի�
		k--;
	}
	if (k >= 1L << len) {
        //������Χ
		return -1;
	}
	long ans = 0;
	for (int i = len, j = 0; i >= 1; i--, j++) {
		if ((k & (1L << j)) != 0) {
			ans ^= arr[i];
		}
	}
	return ans;
}

int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i] ;
    }
    compute();
    int q ;
    cin>>q;
    for (int i = 1; i <= q; i++) {
        long k ;
        cin>>k;
        cout<<query(k)<<endl;
    }
    return 0;
}
