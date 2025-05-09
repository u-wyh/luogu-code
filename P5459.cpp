#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXN = 100002;

int n, m;
long long sort_arr[MAXN], tree[MAXN];

// ��״����ģ����룬�����޸�
void add(int i, int c) {
    while (i <= m) {
        tree[i] += c;
        i += i & -i;
    }
}

// ��״����ģ����룬�����޸�
int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= i & -i;
    }
    return ans;
}

// ���� <= v �����ǰ׺�͵�����
int ran(long long v) {
    int left = 1, right = m, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (sort_arr[mid] <= v) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

// ����ǰ׺�����顢����ȥ�أ���ʼ����״����
void build(const vector<int>& nums) {
    n = nums.size();
    for (int i = 1, j = 0; i <= n; ++i, ++j) {
        sort_arr[i] = sort_arr[i - 1] + nums[j];
    }
    sort(sort_arr + 1, sort_arr + n + 1);
    m = 1;
    for (int i = 2; i <= n; ++i) {
        if (sort_arr[m] != sort_arr[i]) {
            sort_arr[++m] = sort_arr[i];
        }
    }
    fill(tree + 1, tree + m + 1, 0);
}

// ���������Χ�ڵĺ͵ĸ���
long long  countRangeSum(const vector<int>& nums, long long lower, long long upper) {
    build(nums);
    long long Sum = 0;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        Sum += nums[i];
        ans += sum(ran(Sum - lower)) - sum(ran(Sum - upper - 1));
        if (lower <= Sum && Sum <= upper) {
            ++ans;
        }
        add(ran(Sum), 1);
    }
    return ans;
}

int main() {
    int n;
    long long lower, upper;
    cin >> n >>lower>>upper;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    cout << countRangeSum(nums, lower, upper) << endl;
    return 0;
}
