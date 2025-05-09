// ����������еĸ���
// ����һ��δ�������������nums����������������еĸ���
// �������� : https://leetcode.cn/problems/number-of-longest-increasing-subsequence/
// �����ڽ���072���������������������չ����������Ԥ��
// ������Կ�����072��Ƶ���Ĳ���
// ����״����ʵ��ʱ�临�Ӷ�O(n * logn)
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2001;
int Sort[MAXN];
// ά����Ϣ : ����ֵi��β������������У������Ƕ���
// ά������Ϣ����״������֯
int treeMaxLen[MAXN];
// ά����Ϣ : ����ֵi��β������������У������Ƕ���
// ά������Ϣ����״������֯
int treeMaxLenCnt[MAXN];
int nums[MAXN];
int m,n;
int maxLen, maxLenCnt;

int lowbit(int i) {
    return i & -i;
}

// ��ѯ��β��ֵ<=i������������еĳ��ȣ���ֵ��maxLen
// ��ѯ��β��ֵ<=i������������еĸ�������ֵ��maxLenCnt
void query(int i) {
    maxLen = maxLenCnt = 0;
    while (i > 0) {
        if (maxLen == treeMaxLen[i]) {
            maxLenCnt += treeMaxLenCnt[i];
            //������ֵһ��   ��ô�ۼ�  ��Ϊ���ǻ�������  ��ʹ������ͬ
        } else if (maxLen < treeMaxLen[i]) {
            maxLen = treeMaxLen[i];
            maxLenCnt = treeMaxLenCnt[i];
        }
        i -= lowbit(i);
    }
}

// ����ֵi��β������������У����ȴﵽ��len������������cnt
// ������״����
void add(int i, int len, int cnt) {
    while (i <= m) {
        if (treeMaxLen[i] == len) {
            treeMaxLenCnt[i] += cnt;
        } else if (treeMaxLen[i] < len) {
            treeMaxLen[i] = len;
            treeMaxLenCnt[i] = cnt;
        }
        //ʣ�µ��������  �������κθı�
        i += lowbit(i);
        //�����а��������ȫ������
    }
}

int Rank(int v) {
	int ans = 0;
    int l = 1, r = m, mid;
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

int findNumberOfLIS(int* nums) {
    for (int i = 1; i <= n; i++) {
        Sort[i] = nums[i];
    }
    sort(Sort+ 1,Sort+ n + 1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (Sort[m] !=Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }
    //���ϲ���ʵ������ ��ɢ��  �Լ�ȥ��

    memset(treeMaxLen,0,sizeof(treeMaxLen));
    memset(treeMaxLenCnt,0,sizeof(treeMaxLenCnt));
    int i;
    for (int k=1;k<=n;k++) {
        int num=nums[k];
        int i = Rank(num);
        query(i - 1);
        //��ѯ����ֵС�ڵ���i-1 ������������г���  �Լ���Ӧ����
        if (maxLen == 0) {
            // ��������ֵ<=i-1��β������������г���Ϊ0
            // ��ô˵������ֵi��β������������г��Ⱦ���1����������1
            //������Ϊ������i��1�����  �������
            add(i, 1, 1);
        } else {
            // ��������ֵ<=i-1��β������������г���ΪmaxLen != 0
            // ��ô˵������ֵi��β������������г��Ⱦ���maxLen + 1����������maxLenCnt
            add(i, maxLen + 1, maxLenCnt);
        }
        //�ٸ����� ���i��16  ����query(i-1)���ص�ֵ�ǳ�Ϊ5 ��5��  ��ôadd:��Ϊ6 5��
        //���i��1   ��ô���صı�Ȼ��0 0 �������ӵ���1 1
    }
    query(m);
    //m�������е����ֵ  ��ô��������൱�ڲ�ѯ������״��������ĳ����Լ���Ӧ�ĸ���
    return maxLenCnt;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    cout<<findNumberOfLIS(nums);
    return 0;
}
