// ��ӽ�Ŀ��ֵ�������к�
// ����һ���������� nums ��һ��Ŀ��ֵ goal
// ����Ҫ�� nums ��ѡ��һ�������У�ʹ������Ԫ���ܺ���ӽ� goal
// Ҳ����˵�����������Ԫ�غ�Ϊ sum ������Ҫ ��С�����Բ� abs(sum - goal)
// ���� abs(sum - goal) ���ܵ� ��Сֵ
// ע�⣬�������������ͨ���Ƴ�ԭʼ�����е�ĳЩԪ�أ�����ȫ�����ޣ����γɵ����顣
// ����������:
// 1 <= nums.length <= 40
// -10^7 <= nums[i] <= 10^7
// -10^9 <= goal <= 10^9
// �������� : https://leetcode.cn/problems/closest-subsequence-sum/
#include<bits/stdc++.h>
using namespace std;

int n,goal;
int nums[20];
//������ȫչ������Ϣ
int lsum[1<<10];
int rsum[1<<10];
int fi=0;

void collect(int* nums, int i, int e, int s, int* sum) {
    if (i == e) {
        sum[fi++] = s;
    } else {
        // nums[i.....]��һ�飬��ͬ�������м���
        int j = i + 1;
        while (j < e && nums[j] == nums[i]) {
            j++;
        }
        // nums[ 1 1 1 1 1 2....
        //       i         j
        for (int k = 0; k <= j - i; k++) {
            // k = 0��
            // k = 1��
            // k = 2��
            collect(nums, j, e, s + k * nums[i], sum);
        }
    }
}

int main()
{
    cin>>n>>goal;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    long minans = 0;
    long maxans = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] >= 0) {
            maxans += nums[i];
        } else {
            minans += nums[i];
        }
    }
    //��ǰ��֦
    if (maxans < goal) {
        cout<< abs(maxans - goal);
        return 0;
    }
    if (minans > goal) {
        cout<< abs(minans - goal);
        return 0;
    }
    sort(nums,nums+n);//��������Ż�
    fi = 0;
    collect(nums, 0, n >> 1, 0, lsum);
    int lsize = fi;
    fi = 0;
    collect(nums, n >> 1, n, 0, rsum);
    int rsize = fi;
    sort(lsum,lsum+ lsize);
    sort(rsum,rsum+ rsize);
    int ans = abs(goal);
    for (int i = 0, j = rsize - 1; i < lsize; i++) {
        while (j > 0 && abs(goal - lsum[i] - rsum[j - 1]) <= abs(goal - lsum[i] - rsum[j])) {
            j--;
        }
        ans = min(ans, abs(goal - lsum[i] - rsum[j]));
    }
    cout<<ans;
    return 0;
}
