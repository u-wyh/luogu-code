#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 1050;

int n,m;
int arr[MAXN];
int nums[MAXM];
int pre[MAXM];
int sum;

int totalCake;
int needCake;
int wasteCake;

bool sub_DFS(int toTest, int origin)            // origin������������������
{
    /* �����ݹ� */
    if(toTest<1)
        return true;                            // �Ѿ����1~toTest���˵�ιʳ������ͨ��
    if(totalCake-wasteCake<needCake)
        return false;                           // �ܵ���С�������󣬱�Ȼʧ�ܣ�ֹͣ����

    /* ���� */
    bool flag = false;
    for(int i=origin;i<=n;++i)                  // �������⣬���Խ�����ι����toTest����
    {
        if(arr[i]>=nums[toTest])
        {
            needCake-=nums[toTest];            // ιʳ�����ĵ��⣬��������
            totalCake-=nums[toTest];
            arr[i]-=nums[toTest];

            bool wasted = false;                // ���ݣ��Ƿ�ʹ���˵������Ż�
            if(arr[i]<nums[1])                // �Ż�����������������������󣬲�����
            {
                wasteCake+=arr[i];             // �˵����������˷ѣ������Ż������ı�־
                wasted = true;
            }
            if(nums[toTest]==nums[toTest-1])  // ��һ�����Զ������͵�ǰ����һ����
            {
                if(sub_DFS(toTest-1,i))         // �Ż����ӵ�ǰ��λ�ü������������б�
                    flag = true;                // �Ż����ҵ�����������Ͳ��ټ�������
            }
            else if(sub_DFS(toTest-1,1))        // �޷��Ż���ֱ�ӵݹ顣
                flag = true;                    // �Ż���ͬ�Ϸ�֧

            /* ���� */
            if(wasted)                          // �������Ż����򳷻�
                wasteCake-=arr[i];
            arr[i]+=nums[toTest];             // ����ȫ���仯
            totalCake+=nums[toTest];
            needCake+=nums[toTest];

            if(flag)
                return true;
        }
    }

    /* �����ݹ� */
    return false;                               // �޷��ҵ����ʵĵ��⣬����ʧ��
}

inline bool DFS(int toTest)                     // DFS������toTest�Ƿ����
{
    /* ׼������ */
    totalCake = sum;
    needCake = pre[toTest];
    wasteCake = 0;

    /* �����ݹ� */
    return sub_DFS(toTest,1);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    sort(arr+1,arr+n+1);
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i];
    }
    sort(nums+1,nums+m+1);
    for(int i=1;i<=m;i++){
        pre[i]=pre[i-1]+nums[i];
    }
    int l=0,r=m;
    for(int i=1;i<=m;i++){
        if(nums[i]>arr[n]){
            r=i-1;
            break;
        }
        if(pre[i]>sum){
            r=i-1;
            break;
        }
    }
    int ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(DFS(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
