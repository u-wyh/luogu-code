#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;

int n,m;
char ss[MAXN << 1];//这个数组中间添加了#
char a[MAXN];//原始数组
int p[MAXN << 1];//半径数组

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

int manacher() {
    manacherss();
    int maxans = 0;
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {//i是此时来到的中心位置
        len = r > i ? min(p[2 * c - i], r - i) : 1;//这个值是基本值  如果包住了  那么基本值就是最终值  否则后续再加
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //如果被包住了  那么直接跳出来了
        }
        //此时已经求出了以i为中心的回文半径大小
        if (i + len > r) {
            r = i + len;
            c = i;
            //如果更新了右边界  那么c就是i  r就是i+len
        }
        maxans = max(maxans, len);
        p[i] = len;
        //得到回文半径
    }
    return maxans - 1;
}
int main()
{
    cin>>n;
    m=n;
    scanf("%s",a);
    manacher();
    int ans;
    for(int i=0;i<n;i++){
        //cout<<i/2<<' '<<p[i]/2<<' '<<i<<' '<<p[i]<<endl;
        if((i+p[i])==n){
            ans=m-(p[i]-1);
            break;
        }
    }
    cout<<ans;
    return 0;
}
