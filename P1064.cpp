#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<int>vec[61];//��ʾ�����ĸ�������Щ
int pri[61],val[61],nature[61];
int dp[61][32005];

int main()
{
    cin>>n>>m;
    n/=10;
    for(int i=1;i<=m;i++){
        cin>>pri[i]>>val[i]>>nature[i];
        pri[i]/=10;
        val[i]*=pri[i];
        if(nature[i]){
            vec[nature[i]].push_back(i);
        }
    }
    int pre=0;
    for(int i=1;i<=m;i++){
        if(nature[i]==0){
            //cout<<' '<<i<<endl;
            int size=vec[i].size();
            //cout<<pre<<' '<<i<<' '<<size<<endl;
            for(int j=1;j<=n;j++){
                dp[i][j]=dp[pre][j];
                if(j-pri[i]>=0){
                    dp[i][j]=max(dp[i][j],dp[pre][j-pri[i]]+val[i]);
                }
                // fan1 : ����и�1��Ʒ����Ÿ�fan1�����û�У�fan1 == -1
                // fan2 : ����и�2��Ʒ����Ÿ�fan2�����û�У�fan2 == -1
                int fan1 = size >= 1 ? vec[i][0] : -1;
                int fan2 = size >= 2 ? vec[i][1] : -1;
                if (fan1 != -1 && j - pri[i] - pri[fan1] >= 0) {
                    // ������3 : �� + ��1
                    dp[i][j] = max(dp[i][j], dp[pre][j - pri[i] - pri[fan1]] + val[i] + val[fan1]);
                }
                if (fan2 != -1 && j - pri[i] - pri[fan2] >= 0) {
                    // ������4 : �� + ��2
                    dp[i][j] = max(dp[i][j], dp[pre][j - pri[i] - pri[fan2]] + val[i] + val[fan2]);
                }
                if (fan1 != -1 && fan2 != -1 && j - pri[i] - pri[fan1] - pri[fan2] >= 0) {
                    // ������5 : �� + ��1 + ��2
                    dp[i][j] = max(dp[i][j], dp[pre][j - pri[i] - pri[fan1] - pri[fan2]]
                                    + val[i] + val[fan1] + val[fan2]);
                }
            }
            pre=i;
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        ans=max(ans,dp[i][n]);
    }
    ans*=10;
    cout<<ans;
    return 0;
}
