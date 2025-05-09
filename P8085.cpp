#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 1e6 + 3;
typedef unsigned int       u32;
typedef unsigned long long u64;
const u64 BAS = 13331;

int L1[MAXN], R1[MAXN];
int L2[MAXN], R2[MAXN];
int A[MAXN], B[MAXN], n, m;
u64 H[MAXN], P[MAXN];
map <string, int> M;

int main(){
    string t;
    while(cin >> t && t != "$"){
        R1[M[t]] = ++ n, L1[n] = M[t], M[t] = n;
    }
    M.clear();
    while(cin >> t && t != "$"){
        R2[M[t]] = ++ m, L2[m] = M[t], M[t] = m;
    }
    for(int i = 1;i <= n;++ i)
        if(!R1[i]) R1[i] = INF;
    for(int i = 1;i <= m;++ i)
        if(!R2[i]) R2[i] = INF;
    for(int i = 1;i <= n;++ i)
        A[i] = L1[i] ? i - L1[i] : -1;
    for(int i = 1;i <= m;++ i)
        B[i] = L2[i] ? i - L2[i] : -1;
    u64 h0 = 0, h = 0; P[0] = 1;
    for(int i = 1;i <= m;++ i)
        P[i] = P[i - 1] * BAS;
    for(int i = 1;i <= m;++ i)
        h0 = h0 * BAS + B[i], h  = h  * BAS + A[i];
    if(h == h0)
        printf("%d\n", 1), exit(0);
    for(int i = m + 1;i <= n;++ i){
        h = h * BAS + A[i], h = h - A[i - m] * P[m];
        if(R1[i - m] <= i){
            h = h - A[R1[i - m]] * P[i - R1[i - m]];
            A[R1[i - m]] = -1;
            h = h + A[R1[i - m]] * P[i - R1[i - m]];
        }
        else if(R1[i - m] <= n)
            A[R1[i - m]] = -1;
        if(h == h0)
            printf("%d\n", i - m + 1), exit(0);
    }
    return 0;
}
