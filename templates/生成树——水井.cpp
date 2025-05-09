#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20001;
const int MAXM = 20001;

int father[MAXN];
int n,m;
struct node{
    int st,en,val;
}edge[MAXM<<1];
int well[MAXN];
int road[MAXM][3];

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
    int cnt=1;
    for(int i=1;i<=n;i++){
        cin>>well[i];
        edge[cnt].st=0;
        edge[cnt].en=i;
        edge[cnt++].val=well[i];
    }
    for(int i=1;i<=m;i++){
        cin>>road[i][0]>>road[i][1]>>road[i][2];
        edge[cnt].st=road[i][0];
        edge[cnt].en=road[i][1];
        edge[cnt++].val=road[i][2];
    }
    sort(edge+1,edge+cnt,cmp);
    int ans=0;
    int edgecnt=0;
    //edgecntͳ�Ƽ�¼�˶�������
    for(int i=1;i<cnt;i++){
        if(un(edge[i].st,edge[i].en)){
            //��������ߵ�������ǰ����һ��������   ����
            ans+=edge[i].val;
            edgecnt++;
        }
    }
    if(edgecnt==n){
        cout<<ans;
    }else{
        cout<<"orz";
    }
    return 0
}
