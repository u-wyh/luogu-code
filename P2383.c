#include<stdio.h>
#include<stdbool.h>
#define Max 1000

// limit : ÿ���߹涨�ĳ���
// status : ��ʾ��Щ���ֻ�����ѡ
// cur : ��ǰҪ������������Ѿ��γɵĳ���
// rest : һ�����м�����û�н��
// ���� : �ܷ��ù����л��ȥ���ʣ�µ����б�
// ��Ϊ�����ӹ���֮ǰ��һ����֤ÿ�����ۼ�������������limit
// ����status�Ǿ���cur��rest�ģ��ؼ��ɱ����ֻ��status
bool f(int* nums, int limit, int status, int cur, int rest, int* dp,int n)
{
    if (rest == 0) {
        return status == 0;
    }
    if (dp[status] != 0) {
        return dp[status] == 1;
    }
    bool ans = false;
    for (int i = 0; i < n; i++) {
        // ����ÿһ�����ֻ��ʹ��״̬Ϊ1�Ļ��
    if ((status & (1 << i)) != 0 && cur + nums[i] <= limit) {
				if (cur + nums[i] == limit) {
                ans = f(nums, limit, status ^ (1 << i), 0, rest - 1, dp,n);
            } else {
                ans = f(nums, limit, status ^ (1 << i), cur + nums[i], rest, dp,n);
            }
            if (ans) {
                break;
            }
        }
    }
    dp[status] = ans ? 1 : -1;
    return ans;
}

bool makesquare(int *nums,int sum,int n)
{
    if (sum % 4 != 0) {
        return false;
    }
    int dp [1 << n];
    for(int i=0;i<(1<<n);i++)
        dp[i]=0;
    return f(nums, sum / 4, (1 << n) - 1, 0, 4, dp,n);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
    int n;
    scanf("%d",&n);
    int nums[n];
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=nums[i];
    if(makesquare(nums,sum, n))
        printf("yes\n");
    else
        printf("no\n");
    }
    return 0;
}
