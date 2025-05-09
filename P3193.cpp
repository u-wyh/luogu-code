#include<bits/stdc++.h>
using namespace std;

int n,m,mod;
char s[21];
int nxt[21];

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

vector<vector<int>> kmp(){
    int n = strlen(s);
    nxt[0] = -1;
    nxt[1] =  0;
    int i = 2, cn = 0;
    while (i < n) {
        if (s[i - 1] == s[cn]) {
            nxt[i] = ++cn;
            if(s[nxt[i]]==s[i]){
                nxt[i]=nxt[nxt[i]];
            }
            i++;
        } else if (cn > 0) {
            cn = nxt[cn];
        } else {
            nxt[i++] = 0;
        }
    }
//    for (int i = 0; i < n; i++) {
//        cout << nxt[i] << ' ';
//    }
//    cout << endl<<endl;
    vector<vector<int>>base(n,vector<int>(n,0));
    for(int i=0;i<m;i++){
        for(char ch='0';ch<='9';ch++){
            int j=i;
            while(j&&s[j]!=ch)
                j=nxt[j];
			if(s[j]==ch)
                ++j;
			++base[i][j];
        }
    }
//    for(int i=0;i<m;i++){
//        for(int j=0;j<m;j++){
//            cout<<base[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    return base;
}

int main()
{
    cin>>n>>m>>mod>>s;
    if(n==1){
        cout<<9<<endl;
        return 0;
    }
    vector<vector<int>>a(1,vector<int>(m,0));
    a[0][0]=9,a[0][1]=1;
    vector<vector<int>>base=kmp();
    a=multiply(a,power(base,n-1));
    int ans=0;
    for(int i=0;i<m;i++){
        ans+=a[0][i];
        ans%=mod;
    }
    cout<<ans<<endl;
    return 0;
}

