// 航班预订统计
// 这里有 n 个航班，它们分别从 1 到 n 进行编号。
// 有一份航班预订表 bookings ，
// 表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi]
// 意味着在从 firsti 到 lasti
//（包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
// 请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。
// 测试链接 : https://leetcode.cn/problems/corporate-flight-bookings/
#include<bits/stdc++.h>
using namespace std;

int n,m;
int a,b,c;
int nums[1000];

int main()
{
    cin>>n>>m;
    while(m--){
        cin>>a>>b>>c;
        nums[a]+=c;
        nums[b+1]-=c;
    }
    for(int i=1;i<=n;i++){
        nums[i]+=nums[i-1];
        printf("%3d",nums[i]);
    }
    return 0;
}
