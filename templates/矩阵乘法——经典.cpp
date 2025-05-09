//P2579
//�����Ŀ��������  ��ô����˵���������˾���˷���ԭ��
//2 3 4 �Ǽ��ʱ�� ���ǵ���С��Լ����12  Ҳ�����൱��12��Ϊһ��ѭ��
//��ô����ֱ�ӽ���12������  ��ʾ��ʱ��Ϊi��ʱ����Щ�߿�����
//���Ƚ�12��ͼ�е����б����Ϳ����ߵı�����Ϊ1
//Ȼ�����ʱ���ж���Щ���ǲ����ߵ�
//����λ�������12���������  ��������t/12�η�
//Ȼ��ʣ��Ĳ������꼴��
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e4;

int n,m;
int st,en,t;
int fish;
int to[4];
struct mat{
    vector<vector<int>>f;
    mat(int n,int m): f(n,vector<int>(m,0)){}
};

mat operator*(mat a,mat b){
    int n=a.f.size();
    int m=b.f[0].size();
    int k=a.f[0].size();
    mat ans(n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int p=0;p<k;p++){
                ans.f[i][j]+=a.f[i][p]*b.f[p][j];
                ans.f[i][j]%=MOD;
            }
        }
    }
    return ans;
}

mat power(mat a,int p){
    int n=a.f.size();
    mat base(n,n);
    for(int i=0;i<n;i++){
        base.f[i][i]=1;
    }
    while(p){
        if(p&1){
            base=base*a;
        }
        p>>=1;
        a=a*a;
    }
    return base;
}

int main()
{
    cin>>n>>m>>st>>en>>t;
    vector<mat> g(13, mat(n,n));
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        for (int j = 1; j <= 12; j++) {
            g[j].f[x][y] = g[j].f[y][x] = 1;
        }
    }
    cin>>fish;
    while(fish--){
        int num;
        cin>>num;
        for(int i=0;i<num;i++){
            cin>>to[i];
        }
        for(int i=0;i<n;i++){
            for(int j=1;j<=12;j++){
                g[j].f[i][to[j%num]]=0;
            }
        }
    }
    mat base(n,n);
    for(int i=0;i<n;i++){
        base.f[i][i]=1;
    }
    for(int i=1;i<=12;i++){
        base=base*g[i];
    }
    mat ans=power(base,t/12);
    for(int i=1;i<=t%12;i++){
        ans=ans*g[i];
    }
    cout<<ans.f[st][en];
    return 0;
}
