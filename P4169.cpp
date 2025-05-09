#include<bits/stdc++.h>
using namespace std;
const int mod = 2009;

vector<vector<int>> multiply(vector<vector<int>>a,vector<vector<int>>b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int p = 0; p < k; p++) {
                ans[i][j] += a[i][p] * b[p][j];
                ans[i][j]%=mod;
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>> a,int p){
    int n=a.size();
    vector<vector<int>> base(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        base[i][i]=1;
    }
    while(p){
        if(p&1){
            base=multiply(base,a);
        }
        p>>=1;
        a=multiply(a,a);
    }
    return base;
}

int main()
{
    int n,t;
    cin>>n>>t;
    int m=n*9;
    vector<vector<int>>nums(m,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<8;j++){
            nums[9*i+j][9*i+j+1]=1;
        }
    }
    for(int i=0;i<n;i++){
        string str;
        cin>>str;
        for(int j=0;j<n;j++){
            if(str[j]>'0'){
                nums[9*i+str[j]-'1'][9*j]=1;
            }
        }
    }
//    for(int i=0;i<m;i++){
//        for(int j=0;j<m;j++){
//            cout<<nums[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    nums=power(nums,t);
    cout<<nums[0][9*n-9]<<endl;
    return 0;
}

