#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19260817;

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
    int T;
    cin>>T;
    while(T--){
        int p;
        cin>>p;
        if(p==1){
            cout<<2<<endl;
            continue;
        }
        if(p==2){
            cout<<4<<endl;
            continue;
        }
        vector<vector<int>>base={{1,1,1},{1,0,0},{0,1,0}};
        vector<vector<int>>m={{4},{2},{1}};
        long long ans=0;
        vector<vector<int>> base_pow = power(base, p-3);
        m = multiply(base_pow, m); // �� m ���
        for(int i=0;i<3;i++){
            ans+=m[i][0];
        }
        ans%=MOD;
        cout<<ans<<endl;
    }
    return 0;
}
