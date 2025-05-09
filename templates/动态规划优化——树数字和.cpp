// ���������ĸ���
// ����һ������Ϊn������nums��������������lower��upper
// ����������������ۼӺ���[lower, upper]��Χ��
// ����nums���ж��ٸ����������
// 1 <= n <= 10^5
// nums[i]��������������
// -10^5 <= lower <= upper <= +10^5
// �������� : https://leetcode.cn/problems/count-of-range-sum/

// ��״���� + ��ɢ���Ľⷨ������ѶȽϵ�
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
int countRangeSum(const vector<int>& nums, long long lower, long long upper) {
    build(nums);
    long long Sum = 0;
    int ans = 0;
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

//�鲢��
//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//// ����ȫ�ֱ���
//const int MAXN = 100001;
//long long sum[MAXN], help[MAXN];
//long long low, up;
//
//// �鲢���ε�ͳ�ƺ���
//int merge(int l, int m, int r) {
//    int ans = 0;
//    int wl = l, wr = l;
//    long long max_val, min_val;
//    for (int i = m + 1; i <= r; ++i) {
//        max_val = sum[i] - low;
//        min_val = sum[i] - up;
//        // ��Ч������[wl,wr)������ҿ�
//        while (wr <= m && sum[wr] <= max_val) {
//            ++wr;
//        }
//        while (wl <= m && sum[wl] < min_val) {
//            ++wl;
//        }
//        ans += wr - wl;
//    }
//    // ��������ĺϲ�����
//    int p1 = l, p2 = m + 1;
//    int i = l;
//    while (p1 <= m && p2 <= r) {
//        help[i++] = sum[p1] <= sum[p2] ? sum[p1++] : sum[p2++];
//    }
//    while (p1 <= m) {
//        help[i++] = sum[p1++];
//    }
//    while (p2 <= r) {
//        help[i++] = sum[p2++];
//    }
//    for (i = l; i <= r; ++i) {
//        sum[i] = help[i];
//    }
//    return ans;
//}
//
//// �ݹ���ⷶΧ�͵ĸ���
//int f(int l, int r) {
//    if (l == r) {
//        return low <= sum[l] && sum[l] <= up ? 1 : 0;
//    }
//    int m = (l + r) / 2;
//    return f(l, m) + f(m + 1, r) + merge(l, m, r);
//}
//
//// �����������������Χ�ڵĺ͵ĸ���
//int countRangeSum(const vector<int>& nums, long long lower, long long upper) {
//    int n = nums.size();
//    sum[0] = nums[0];
//    for (int i = 1; i < n; ++i) {
//        sum[i] = sum[i - 1] + nums[i];
//    }
//    low = lower;
//    up = upper;
//    return f(0, n - 1);
//}
//
//int main() {
//    int n;
//    long long lower, upper;
//    cin >> n >> lower >> upper;
//    vector<int> nums(n);
//    for (int i = 0; i < n; ++i) {
//        cin >> nums[i];
//    }
//    cout << countRangeSum(nums, lower, upper) << endl;
//    return 0;
//}
