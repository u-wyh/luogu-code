#include<bits/stdc++.h>
using namespace std;

int n,k;
int minh=0,mint=0,maxh=0,maxt=0;
int minq[1000005],maxq[1000005];
int nums[1000005];

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int i=0;i<n;i++){
        while(minh<mint&&i-minq[minh]>=k){
            minh++;
        }
        while(minh<mint&&nums[i]<=nums[minq[mint-1]]){
            mint--;
        }
        minq[mint++]=i;
        if(i>=k-1)
            cout<<nums[minq[minh]]<<' ';
    }
    printf("\n");
    for(int i=0;i<n;i++){
        while(maxh<maxt&&i-maxq[maxh]>=k){
            maxh++;
        }
        while(maxh<maxt&&nums[i]>=nums[maxq[maxt-1]]){
            maxt--;
        }
        maxq[maxt++]=i;
        if(i>=k-1)
            cout<<nums[maxq[maxh]]<<' ';
    }
    printf("\n");
    return 0;
}
