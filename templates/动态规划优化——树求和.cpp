// ƽ�������е�����
// ����һ������Ϊn������nums�����涨��ƽ��������
// ����±�i���±�j��ѡ���������У�i��j�����
// ��ô������nums[j] - nums[i] >= j - i
// ���һ��������������������±궼���������Ҫ���������о���ƽ���
// ����nums����ƽ��������������ۼӺ��Ƕ���
// 1 <= n <= 10^5
// -10^9 <= nums[i] <= +10^9
// �������� : https://leetcode.cn/problems/maximum-balanced-subsequence-sum/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int arr[MAXN];
int nums[MAXN];
long tree[MAXN];
int n, m;

// ��ǰ��ָ��ֵ��v���������ǵڼ���ָ��
int Rank(int v) {
	int left = 1, right = m, mid;
	int ans = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] <= v) {
			ans = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return ans;
}

// dp[i��ָ��]����ǰ�����ֵ��v
void update(int i, long v) {
	while (i <= m) {
		tree[i] = max(tree[i], v);
		i += i & -i;
	}
}

// dp[1..i]�����ֵ���ٷ���
long querymax(int i) {
	long ans = LONG_MIN;
	while (i > 0) {
		ans = max(ans, tree[i]);
		i -= i & -i;
	}
	return ans;
}

void build() {
    for (int i = 1, j = 0; i <= n; i++, j++) {
        arr[i] = nums[j] - j;
    }
    sort(arr+1,arr + n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (arr[m] != arr[i]) {
            arr[++m] = arr[i];
        }
    }
    fill(tree+1,tree+m + 1, LONG_MIN);
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    build();
    long pre;
    for (int i = 0, k; i < n; i++) {
        // k�ĺ���Ϊ��ǰ��ָ���ǵڼ���ָ��
        k = Rank(nums[i] - i);
        // dp[1��..k��ָ��]�е����ֵ�Ƕ���
        pre = querymax(k);
        if (pre < 0) {
            // ���֮ǰ���������Ǹ�������ô��Ҫ֮ǰ������
            // ��ǰ�����Լ������γ�ƽ��������
            // ȥ����dp[k��ָ��]�����ܲ��ܱ�ø���
            update(k, nums[i]);
        } else {
            // ���֮ǰ�����������Ǹ�������ô�͵�ǰ����һ���γɸ�����ۼӺ�
            // ȥ����dp[k��ָ��]�����ܲ��ܱ�ø���
            update(k, pre + nums[i]);
        }
    }
    // ����dp[1��..m��ָ��]�е����ֵ
    cout<<querymax(m);
    return 0;
}
