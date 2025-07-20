#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 25;

int n,m,mod;
int s[MAXN];
int nxt[MAXN];

// 计算1-based next数组
void calcnext(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&s[i]!=s[j+1]){
            j=nxt[j];
        }
        // 如果当前字符匹配，j增加
        if(s[i]==s[j+1]){
            j++;
        }
        // 设置当前位置的next值
        nxt[i]=j;
    }
}

// 矩阵相乘
// a的列数一定要等于b的行数
vector<vector<int>> multiply(vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]%=mod;
            }
        }
    }
    return ans;
}

// 矩阵快速幂
vector<vector<int>> power(vector<vector<int>>& m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//每次都是倍增
    }
    return ans;
}

signed main()
{
    scanf("%lld %lld %lld",&n,&m,&mod);
    char str[25];
    scanf("%s",str+1);
    for(int i=1;i<=m;i++){
        s[i]=str[i]-'0';
    }
    calcnext();
    //得到一个转换表  对于s2当前匹配的位置是i 如果填字母c会跳转到哪里
    vector<vector<int>>trans(m+1,vector<int>(10,0));
    for(int i=0;i<=m;i++){
        for(int c=0;c<10;c++){
            if(i<m&&c==s[i+1]){
                trans[i][c]=i+1;
            }
            else{
                if(i==0){
                    trans[i][c]=0;//表示还是没有匹配上
                }
                else{
                    int k=nxt[i];
                    trans[i][c]=trans[k][c];
                }
            }
        }
    }
    vector<vector<int>>mat(2*m,vector<int>(2*m,0));
    for(int cnt=0;cnt<=1;cnt++){
        for(int pos=0;pos<m;pos++){
            for(int c=0;c<10;c++){
                int newcnt=cnt;
                int newpos=trans[pos][c];//表示这一位置之后选择一个c会跳到哪里
                if(newpos==m){
                    newcnt=min(newcnt+1,1ll);
                    newpos=nxt[m];
                }
                int from=cnt*m+pos;//转移前的状态
                int to=newcnt*m+newpos;//转移后的状态
                mat[from][to]=(mat[from][to]+1)%mod;
            }
        }
    }
    mat=power(mat,n);
    //其实如果单按数值来看的话   使用vec数组就是多此一举
    //因为使用mat的n次方  然后计算特定位置的值   也是一样的
    //但是从规范的角度来讲  这是不合适的    
    vector<vector<int>>res(1,vector<int>(2*m,0));
    res[0][0]=1;
    res=multiply(res,mat);
    int ans=0;
    for(int pos=0;pos<m;pos++){
        int sta=pos;
        ans=(ans+res[0][sta])%mod;
    }
    cout<<ans<<endl;
    return 0;
}