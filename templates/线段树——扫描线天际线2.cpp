// ���������(��Ȳ���)
// �������� : https://www.luogu.com.cn/problem/P1904
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;

struct node{
    int l,r,h;
}nums[MAXN];
int xsort[3*MAXN];
int height[3*MAXN];
int n;

bool cmp(node a,node b){
    return a.l<b.l;
}

// ��ѯ��ֵv������(��ɢֵ)
int getrank(int n, int v) {
    int ans = 0;
    int l = 1, r = n, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (xsort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

// ׼����������
// 1) �ռ���¥��߽硢�ұ߽�-1���ұ߽��ֵ
// 2) �ռ�������ֵ����ȥ��
// 3) ��¥����߽���ұ߽磬�޸ĳ�����ֵ
// 4) ��¥������߽�����
// 5) ���height����
// 6) ������ɢֵ�ĸ���
int prepare(){
    int cnt=0;
    for(int i=1;i<=n;i++){
        xsort[++cnt]=nums[i].l;
        xsort[++cnt]=nums[i].r-1;
        xsort[++cnt]=nums[i].r;
    }
    sort(xsort+1,xsort+cnt+1);
    int m = 1;
    for (int i = 1; i <= cnt; i++) {
        if (xsort[m] != xsort[i]) {
            xsort[++m] = xsort[i];
        }
    }
    //cout<<m<<endl;
    // �޸Ĵ�¥Ӱ�쵽�����ұ߽磬���������ֵ
    for (int i = 1; i <= n; i++) {
        nums[i].l = getrank(m, nums[i].l);
        // ��¥Ӱ�쵽���ұ߽磬����1��
        // �����ص�˵��������
        nums[i].r = getrank(m, nums[i].r - 1);
    }
    // ���д�¥������߽�����
    sort(nums+1,nums+n+1,cmp);
    // �����ж��ٸ���ͬ����ɢֵ
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].l<<' '<<nums[i].r<<' '<<nums[i].h<<endl;
//    }
    return m;
}

// �Զ������ͣ���������int������
struct Node {
    int data1;
    int data2;

    // Ϊ�������ȶ�����ʹ�ã���Ҫ����Ƚ���������ṩ�ȽϺ���
    // �������Ƕ���һ���ȽϺ����������ڴ���ѣ����ȽϺ�������trueʱ����һ�������ڵ�Ӧ���ڵڶ��������ڵ�֮��
    struct Compare {
        bool operator()(const Node& lhs, const Node& rhs) const {
            // ����������Ҫ����data1����������ѣ����data1��ͬ�������data2����������ѣ���ѡ��
            if (lhs.data1 != rhs.data1) {
                return lhs.data1 < rhs.data1; // С�ں����ڴ���ѣ���Ϊpriority_queueĬ����С������Ϊͨ��<��ʵ�ִ󶥶�
            } else {
                return lhs.data2 < rhs.data2; // ���data1��ͬ����Ƚ�data2
            }
        }
    };
};

int main()
{
    n=1;
    while(cin>>nums[n].l>>nums[n].h>>nums[n].r){
        n++;
    }
    n--;
    int m=prepare();
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].l<<' '<<nums[i].r<<' '<<nums[i].h<<endl;
//    }
    priority_queue<Node, vector<Node>, Node::Compare> heap;
    for (int i = 1, j = 1; i <= m; i++) {
        for (; j <= n && nums[j].l <= i; j++) {
            heap.push({ nums[j].h, nums[j].r });
        }
        while (!heap.empty() && heap.top().data2 < i) {
            heap.pop();
        }
        if (!heap.empty()) {
            height[i] = heap.top().data1;
        }
    }
    for (int i = 1, pre = 0; i <= m; i++) {
        //cout<<height[i]<<' ';
        if (pre != height[i]) {
            cout<<xsort[i]<<' '<<height[i]<<' ';
        }
        pre = height[i];
    }
    return 0;
}
