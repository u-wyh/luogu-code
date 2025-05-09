#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

struct stu{
    int h,num;
}arr[MAXN];
int Sort[MAXN];
int tree[MAXN];
int n, m;

int Rank(int v) {
	int l = 1, r = m, mid;
    int ans = 0;
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

int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
    while (i <= m) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 1~i��Χ���ۼӺ�
long sum(int i) {
    long ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int query(int x){

}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i].h>>arr[i].num;
        Sort[i]=arr[i].h;//��������  ���������ȥ��
    }
    sort(Sort+1,Sort+n+1);
    m = 1;
    for (int i = 2; i <= n; i++) {
        if (Sort[m] != Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }
    //������ȥ��
    for (int i = 1; i <= n; i++) {
        arr[i].h = Rank(arr[i].h);
        //��ԭ�������ֵ��Ϊ�����������еĴ�С����  ԭ�е����ݱ�����û��ʲô��
        //���������������  �Լ���Լ�ռ�
    }
    long cnt=0;
    for(int i=1;i<=n;i++){
        add(arr[i].h,arr[i].num);
        cnt+=arr[i].num;
        cout<<query(cnt/2)<<endl;
    }
    return 0;
}
