#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e6+4e5+5;

int nums[MAXN];
int n;
long long  ans=0;
int tree[MAXM][2];
int cnt=1;
int high;

void insert(int num) {
    int cur = 1;
    for (int i = high, path; i >= 0; i--) {
        path = (num >> i) & 1;
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
    }
}

void build(){
    int maxans=INT_MIN;
    for(int i=1;i<=n;i++){
        maxans=max(maxans,nums[i]);
    }
    high=31-__builtin_clz(maxans);//ѡ�����Ч��λ��  ����Ҫǰ׺0
    for(int num:nums){
        insert(num);//�����ֲ���ǰ׺����
    }
}

int maxXor(int num) {
    // �������Ľ��(������)
    int ans = 0;
    // ǰ׺��Ŀǰ�����Ľڵ���
    int cur = 1;
    for (int i = high, status, want; i >= 0; i--) {
        // status : num��iλ��״̬
        status = (num >> i) & 1;
        // want : num��iλϣ��������״̬
        want = status ^ 1;
        if (tree[cur][want] == 0) { // ѯ��ǰ׺�����ܲ��ܴ��
            // ���ܴ��
            want ^= 1;
        }
        // want�����������ߵ�·
        ans |= (status ^ want) << i;
        cur = tree[cur][want];
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    build();//�����е�ֵ��������
    for (int num : nums) {
        //��ÿһ����ѡ��һ������ʹ�����
        ans = max(ans,(long long) maxXor(num));
    }
    cout<<ans;
    return 0;
}

