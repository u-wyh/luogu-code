//P3014
//�����Ŀ�����˿���չ��������ͷ������
//�Ƚ�ȫ��
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 22;

int arr[MAXN];
//�׳˱�
int fac[MAXN];
// �߶���
int sum[MAXN << 2];
int n;
int m;

// ��ʼ���߶��������㷶Χ�ĳ�ʼ�ۼӺ�Ϊ1����Ϊ�������ֶ�����
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// ����jobi�ϣ�����jobv����Ϊ�ǵ�����£����Բ���Ҫ���������»���
void add(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        sum[i] += jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobi, jobv, l, mid, i << 1);
        } else {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// ��ѯjobl~jobr��Χ���ۼӺ�
int Sum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans += Sum(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += Sum(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

// �߶������ҵ���k������ʲô���ҵ���ɾ����Ƶ�����صĹ����޸��ۼӺ�
// ע������������������е�����
int getAndDelete(int k, int l, int r, int i) {
    int ans;
    if (l == r) {
        //�ҵ�Ŀ�� ɾ����Ƶ
        sum[i]--;
        ans = l;
    } else {
        int mid = (l + r) >> 1;
        if (sum[i << 1] >= k) {
            ans = getAndDelete(k, l, mid, i << 1);
        } else {
            ans = getAndDelete(k - sum[i << 1], mid + 1, r, i << 1 | 1);
            //Ҫ��ȥ���������Ӱ��
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        //���صĹ����޸��ۼӺ�
    }
    return ans;
}

void compute(int k) {
    build(1, n, 1);
    //���߶������¸�ԭ
    for (int i = 1; i <= n; i++) {
        arr[i] = getAndDelete((int) arr[i] + 1, 1, n, 1);
        //��ʱ���arr���������������
    }
}

signed main()
{
    cin>>n>>m;
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i);
    }
    //�����׳˱�

    for(int i=1;i<=m;i++){
        char op;
        cin>>op;
        if(op=='P'){
            int k;
            cin>>k;
            k--;
            build(1, n, 1);
            for(int i=n;i>0;i--){
                arr[n-i+1]=k/fac[i-1];
                k=k%fac[i-1];
            }
            compute(k);
            for(int i=1;i<=n;i++){
                cout<<arr[i]<<' ';
            }
            cout<<endl;
        }
        else{
            build(1,n,1);
            for(int i=1;i<=n;i++){
                cin>>arr[i];
            }
            int ans=0;
            for(int i=1;i<=n;i++){
                if(arr[i]!=1)
                    ans+=(fac[n-i]*Sum(1,arr[i]-1,1,n,1));
                else{
                    ans+=1;
                }
                add(arr[i],-1,1,n,1);//����һλ����Ϣȥ��
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
