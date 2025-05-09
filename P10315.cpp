#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int mat[105][105];
int st[105],en[105];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline int inv(int x) {//��֤mΪ�����������С������Ԫ
	int res(1), q(m - 2);
	while (q) {
		if (q & 1) res = res * x % m;
		x = x * x % m;
		q >>= 1;
	}
	return res;
}

void swap(int a, int b) {
    int tmp[105];
    //cout<<"swap"<<endl;
    for (int j = 0; j <= n+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

// ��˹��Ԫ���ͬ�෽����ģ�棬��֤��ʼϵ��û�и���
int gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // �Ѿ���Ϊ��Ԫ���в�����
            if (j < i && mat[j][j] != 0) {
                continue;
            }
            // �ҵ�ϵ��������0��������Ԫ����
            if (mat[j][i] != 0) {
                swap(i,j);
                break;
            }
        }
        if (mat[i][i] != 0) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] != 0) {
                    int gcd_val = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / gcd_val;
                    int b = mat[j][i] / gcd_val;
                    if (j < i && mat[j][j] != 0) {
                        // ���j������Ԫ����ô��j�е�i-1�е�����ϵ�� * a
                        // ��ȷ������Ԫ������Ԫ֮��Ĺ�ϵ
                        for (int k = j; k < i; k++) {
                            mat[j][k] = (mat[j][k] * a) % m;
                        }
                    }
                    // ������Ԫ
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % m + m) % m;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if(mat[i][i]==0&&mat[i][n+1]!=0)
            return 2;
        // ��ģ������Ӧ������Ԫ��(a / b) % MOD = (a * b����Ԫ) % MOD
        mat[i][n + 1] = (mat[i][n + 1] * inv(mat[i][i])) % m;
        mat[i][i] = 1;
    }
    return 1;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int u;
            cin>>u;
            mat[u][i]=1;
        }
        mat[i][i]=1;
    }
    for(int i=1;i<=n;i++){
        cin>>st[i];
    }
    for(int i=1;i<=n;i++){
        cin>>en[i];
        mat[i][n+1]=((en[i]-st[i])%m+m)%m;
    }
//    for(int i=1;i<=n;i++){
//        cout<<i<<"  ";
//        for(int j=1;j<=n+1;j++){
//            cout<<mat[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<endl;
    int k=gauss(n);
    if(k==2){
        cout<<"niuza"<<endl;
    }else{
        for(int i=1;i<=n;i++){
            mat[i][n+1]=((mat[i][n+1]%m)+m)%m;
            cout<<mat[i][n+1]<<' ';
        }
    }
    return 0;
}
