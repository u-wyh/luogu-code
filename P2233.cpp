//P2233
#include<bits/stdc++.h>
using namespace std;

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
                ans[i][j]%=1000;
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

int main()
{
    vector<vector<int>>base={{0,2,0,0},{1,0,1,0},{0,1,0,1},{0,0,1,0}};
    vector<vector<int>>m={{1},{0},{0},{0}};
    int n;
    cin>>n;
    vector<vector<int>> base_pow = power(base, n-1); // ���� base �� n ����
    m = multiply(base_pow, m); // �� m ���
//    for(int i=0;i<4;i++){
//        cout<<m[i][0]<<' ';
//    }
//    cout<<endl;
    cout<<m[3][0]*2%1000<<endl;
    return 0;
}
