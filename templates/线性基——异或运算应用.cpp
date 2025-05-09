// Ԫ��
// ����n��ħ����ʯ��ÿ����ʯ��״̬��ħ������������
// ���ɿ�ʯ��ɵ�����ܷ���Ч������״̬���Ľ��������
// ���һ����ʯ����ڲ����������Ϊ0���Ӽ�����ô��������Ч
// ������Ч�Ŀ�ʯ����У�����ħ�����Ƕ���
// 1 <= n <= 1000
// 1 <= ״̬ <= 10^18
// 1 <= ħ�� <= 10^4
// �������� : https://www.luogu.com.cn/problem/P4570
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1001;
const int BIT = 61; // ����long long��64λ�������λ�Ƿ���λ������������61λ

typedef long long ll;

struct Node {
    ll num, power;
};

Node arr[MAXN];
ll basis[BIT];
int n;

// �ȽϺ��������ڰ�power��������
bool cmp(Node a, Node b) {
    return a.power > b.power;
}

// ���Ի������num��������Ի������˷���true�����򷵻�false
bool insert(ll num) {
    for (int i = BIT - 1; i >= 0; i--) {
        if (num >> i & 1) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    }
    return false;
}

// ����õ�������Ի������ٻ��ѣ�ʵ���������ħ���ͣ�
ll compute() {
    ll ans = 0;
    sort(arr + 1, arr + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        if (insert(arr[i].num)) {
            //��Ϊ�Ѿ���˳����ǰ�ź���  ���մӴ�С����
            //����ֻҪ����ɹ�  ��ֱ�Ӽ���  ����һ�������ŵ�
            ans += arr[i].power;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); // �ر�ͬ���������������
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].num >> arr[i].power;
    }
    cout << compute() << endl;
    return 0;
}
