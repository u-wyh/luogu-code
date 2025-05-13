#include<bits/stdc++.h>
using namespace std;
const int MAXN = 41;
const int MAXM = 1<<20;

int n;
int posx,posy;
int x[MAXN],y[MAXN];
struct node{
    int x,y,d;
}nums1[MAXM],nums2[MAXM];
int cnt1;
int cnt2;
int ans[41];
// unordered_map<pair<pair<int,int>,int>,int>mp;

bool cmp(node a,node b){
    return (a.x==b.x)?(a.y<b.y):(a.x<b.x);
}

bool cmp1(node a,node b){
    return (a.x==b.x)?(a.y>b.y):(a.x>b.x);
}

void dfs(int u,int op,int limit,int ux,int uy,int d){
    if(u==limit+1){
        if(op==1){
            nums1[++cnt1]={ux,uy,d};
        }
        else{
            nums2[++cnt2]={ux,uy,d};
        }
    }
    else{
        dfs(u+1,op,limit,ux+x[u],uy+y[u],d+1);
        dfs(u+1,op,limit,ux,uy,d);
    }
}

int find1(int val,int l,int r,int op){
    int ans=r;
    if(op==1){
        while(l<=r){
            cout<<1<<' '<<l<<' '<<r<<' '<<op<<endl;
            int mid=(l+r)/2;
            if(nums2[mid].x>=val){
                ans=mid;
                l=mid-1;
            }
            else{
                r=mid+1;
            }
        }
    }
    else{
        while(l<=r){
            cout<<1<<' '<<l<<' '<<r<<' '<<op<<endl;
            int mid=(l+r)/2;
            if(nums2[mid].y>=val){
                ans=mid;
                l=mid-1;
            }
            else{
                r=mid+1;
            }
        }
    }
    return ans;
}

int find2(int val,int l,int r,int op){
    int ans=r;
    if(op==1){
        while(l<=r){
            cout<<2<<' '<<l<<' '<<r<<' '<<op<<endl;
            int mid=(l+r)/2;
            if(nums2[mid].x>val){
                ans=mid;
                l=mid-1;
            }
            else{
                r=mid+1;
            }
        }
    }
    else{
        while(l<=r){
            cout<<2<<' '<<l<<' '<<r<<' '<<op<<endl;
            int mid=(l+r)/2;
            if(nums2[mid].y>val){
                ans=mid;
                l=mid-1;
            }
            else{
                r=mid+1;
            }
        }
    }
    return ans;
}

int main()
{
    cin>>n>>posx>>posy;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    dfs(1,1,(n+1)/2,0,0,0);
    dfs((n+1)/2+1,2,n,0,0,1);
    sort(nums1+1,nums1+cnt1,cmp);
    sort(nums2+1,nums2+cnt2,cmp);
    int l=cnt2,r=1,lt=1,rt=0;
    nums1[0].x=nums1[1].x-1;
    for(int i=1;i<=cnt1;i++){
        // if(nums1[i].x==nums1[i-1].x&&nums1[i].y==nums1[i-1].y){
        //     for(int j=lt;j<=rt;j++){
        //         ans[nums1[i].d+nums2[j].d]++;
        //     }
        // }
        // else if(nums1[i].x==nums1[i-1].x){
        //     lt=find1(posy-nums1[i].y,l,r,2);
        //     rt=find2(posy-nums1[i].y,l,r,2);
        //     if(nums2[lt].y==posy-nums1[i].y){
        //         if(nums2[rt].y>posy-nums2[i].y){
        //             rt--;
        //         }
        //         for(int j=lt;j<=rt;j++){
        //             ans[nums1[i].d+nums2[j].d]++;
        //         }
        //     }
        //     else{
        //         rt=lt-1;
        //         continue;
        //     }
        // }
        // else{
            // int k=l;
            l=find1(posx-nums1[i].x,1,cnt2,1);
            r=find2(posx-nums1[i].x,1,cnt2,1);
            if(nums2[l].x==posx-nums1[i].x){
                if(nums2[r].x>posx-nums1[i].x){
                    r--;
                }
                lt=find1(posy-nums1[i].y,l,r,2);
                rt=find2(posy-nums1[i].y,l,r,2);
                if(nums2[lt].y==posy-nums1[i].y){
                    if(nums2[rt].y>posy-nums2[i].y){
                        rt--;
                    }
                    for(int j=lt;j<=rt;j++){
                        ans[nums1[i].d+nums2[j].d]++;
                    }
                }
                else{
                    rt=lt-1;
                    continue;
                }
            }
            else{
                continue;
            }
        // }
        cout<<' '<<l<<' '<<r<<' '<<lt<<' '<<rt<<endl;
    }
    for(int i=0;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}