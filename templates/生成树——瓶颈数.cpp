#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int MAXM = 8005;

int father[MAXN];
int n,m;
struct node{
    int st,en,val;
}edge[MAXM];

void build(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
}

int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

bool un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        father[fx]=fy;
        return true;
    }else{
        return false;
    }
}
//����������ڵ���ǰ�Ͳ���һ���������  ��ô�ϲ�����
//���򷵻�false

bool cmp(node a,node b){
    return a.val<b.val;
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=m;i++){
        cin>>edge[i].st>>edge[i].en>>edge[i].val;
    }
    sort(edge+1,edge+m+1,cmp);
    int ans=0;
    int edgecnt=0;
    //edgecntͳ�Ƽ�¼�˶�������
    for(int i=1;i<=m;i++){
        if(un(edge[i].st,edge[i].en)){
            //��������ߵ�������ǰ����һ��������   ����
            ans=max(ans,edge[i].val);
            edgecnt++;
        }
        if(edgecnt==n-1){
            break;
        }
    }
    printf("%d %d",n-1,ans);
    return 0;
}

