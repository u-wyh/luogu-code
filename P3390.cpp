#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

// �������
// a������һ��Ҫ����b������
vector<vector<int>> multiply(vector<vector<int>>& a,const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]%=MOD;
            }
        }
    }
    return ans;
}

// ���������
vector<vector<int>> power(vector<vector<int>>& m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//��λ���� �൱�ڳ˷��������е�1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//ÿ�ζ��Ǳ���
    }
    return ans;
}

signed main()
{
    int n,p;
    cin>>n>>p;
    vector<vector<int>>base(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>base[i][j];
        }
    }
    vector<vector<int>> base_pow = power(base, p);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<base_pow[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}

