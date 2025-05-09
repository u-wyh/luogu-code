// ���Բ�������Ƶ������������
// ����һ���������� nums ����һ����ʾ���Ƶ����� limit
// ���㷵�������������ĳ���
// ���������е���������Ԫ��֮��ľ��Բ����С�ڻ��ߵ��� limit
// ������������������������飬�򷵻� 0
// �������� : https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
#include<bits/stdc++.h>
using namespace std;

int n,limit;
int nums[10000];
int maxq[10000],minq[10000],maxh,maxt,minh,mint;

void push(int r) {
    while (maxh < maxt && nums[maxq[maxt - 1]] <= nums[r]) {
        maxt--;
    }
    maxq[maxt++] = r;
    while (minh < mint && nums[minq[mint - 1]] >= nums[r]) {
        mint--;
    }
    minq[mint++] = r;
}
//��һ���µ�����ѹ��minq  maxq��

void pop(int l) {
    if (maxh < maxt && maxq[maxh] == l) {
        maxh++;
    }
    if (minh < mint && minq[minh] == l) {
        minh++;
    }
}
//�����Ѿ����ڵ�����

bool ok(int number) {
    // max : ���number�������´��ڵ����ֵ
    int max1 = maxh < maxt ? max(nums[maxq[maxh]], number) : number;
    // min : ���number�������´��ڵ���Сֵ
    int min1 = minh < mint ? min(nums[minq[minh]], number) : number;
    return max1 - min1 <= limit;
}

int longest(){
    maxh=0,maxt=0,minh=0,mint=0;
    //���Ƚ������������еĿ�ͷ��β��ʼ��
    int ans = 0;
    for (int l = 0, r = 0; l < n; l++) {
        // [l,r)��r��Զ��û�н��봰�ڵġ���һ�������ڵ�λ��
        while (r < n && ok(nums[r])) {
            push(r++);
            //�������  ˵��������ֿ��Լ���
        }
        // �ж�����˵��������һ������  ����������ּ�����Ǵ���
        // ��while������ʱ��[l,r)��l��ͷ����������������������Χ
        ans = max(ans, r - l);
        pop(l);
        //�����Ϊͷ�������������  ����һ������  ��������ֵ���
    }
    //forѭ��ÿһ�ο��Է���һ����i��ͷ������곤��
    return ans;
}

int main()
{
    cin>>n>>limit;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    cout<<longest()<<endl;
    return 0;
}
