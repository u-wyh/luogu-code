// �����С������
// ����һ������arr��ÿ��ֵ�����������
// ÿһ��ÿ���㶼��Ե��ұ����Լ�������Լ�����С���㣬ÿ����������ֻ��һ��
// ���ǳ����������ͬʱ�����ģ�Ҳ����ͬһ����A�Ե�B��ͬʱ��AҲ���ܱ������Ե�
// ����ж������ڵ�ǰ���ҵ�����ͬһ��С�㣬��ô����һ�֣�����С��ͬʱ����Щ�����
// ���ʶ����ֺ���������͹̶���
// ���� : 8 3 1 5 6 7 2 4
// ��һ�� : 8��3��3��1��5��6��7��2��4û�б��ԡ�����ʣ�� 8 5 6 7 4
// �ڶ��� : 8��5��5��6��7��4������ʣ�� 8 6 7
// ������ : 8��6������ʣ�� 8 7
// ������ : 8��7������ʣ�� 8��
// ���̽���������4
// �������� : https://www.nowcoder.com/practice/77199defc4b74b24b8ebf6244e1793de
// �������� : https://leetcode.cn/problems/steps-to-make-array-non-decreasing/
#include<bits/stdc++.h>
using namespace std;

struct fish{
    int weight,turn;
}nums[1000];
int n;
int st[1000],r=0,ans=0;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].weight;
        nums[i].turn=0;//������������ڼ�¼��ǰ����Ե��ұ�С���Լ�������Ҫ�Ĳ���
    }
    for(int i=n-1;i>=0;i--){
        while(r>0&&nums[st[r-1]].weight<nums[i].weight){
            //������ջ��Сѹ��
            nums[i].turn=max(nums[i].turn+1,nums[st[--r]].turn);
            //�Ե�һ����ķ�1  Ȼ������Ե�����Ĳ���  �ȴ�С
        }
        st[r++]=i;
        ans=max(ans,nums[i].turn);
    }
    cout<<ans;
    return 0;
}
