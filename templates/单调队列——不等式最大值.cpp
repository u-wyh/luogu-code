// ���㲻��ʽ�����ֵ
// ����һ������ points ��һ������ k
// ������ÿ��Ԫ�ض���ʾ��άƽ���ϵĵ�����꣬�����պ����� x ��ֵ��С��������
// Ҳ����˵ points[i] = [xi, yi]
// ������ 1 <= i < j <= points.length ��ǰ���£�xi < xj �ܳ���
// �����ҳ� yi + yj + |xi - xj| �� ���ֵ��
// ���� |xi - xj| <= k �� 1 <= i < j <= points.length
// ��Ŀ�������ݱ�֤���ٴ���һ���ܹ����� |xi - xj| <= k �ĵ㡣
// �������� : https://leetcode.cn/problems/max-value-of-equation/
#include<bits/stdc++.h>
using namespace std;

struct node{
    int x,y;
}nums[10005];
int n,k;
int q[10005],h,t;

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    int ans=-1e9;
    for(int i=0;i<n;i++){
        while(h<t&&nums[i].x-nums[q[h]].x>k){
            h++;
        }
        if(h<t)
            ans=max(ans,nums[i].x+nums[i].y+nums[q[h]].y-nums[q[h]].x);
        while(h<t&&nums[q[t]].y-nums[q[t]].x<=nums[i].y-nums[i].x){
            //ÿ�θ���y-x��ֵ�ж�λ��  ��Ϊÿ�μ�������ʱ����� x+y+(ͷλ�õ�y-x)
            t--;
        }
        q[t++]=i;
    }
    cout<<ans;
    return 0;
}
