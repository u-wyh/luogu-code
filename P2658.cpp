#include<cstdio>
#include<cstring>
#define id(i,j) ~-i*m+j//��ÿ����ı�ţ��൱��(i-1)*m+j
using namespace std;

int h[501][501],f[250001],a[250001],len;//h��ÿ����ĸ߶ȣ�f�ǲ��鼯���飬a����Ҫ��֤��ͨ�ĵ㣬len��a���鳤��
int ans,l,r,n,m,mid;
const short dx[4]={-1,0,1,0};
const short dy[4]={0,1,0,-1};

int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}

void add(int x,int y){
    f[find(x)]=find(y);
    return;
}

int abs(int x){
    return x<0?-x:x;
}

bool check(int high){
	for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            f[id(i,j)]=id(i,j);//��ʼ��
	for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<4;k++)//����Χ�ĸ�������
            {
                int nx=i+dx[k],ny=j+dy[k];
                if(nx<1||ny<1||nx>n||ny>m)
                    continue;//������Χ����
                if(abs(h[i][j]-h[nx][ny])>high)
                    continue;//�����߶�����
                add(id(i,j),id(nx,ny));//����
            }
	for(int i=1;i<len;i++)
        if(find(a[i])!=find(a[i+1]))
            return false;//�ж��Ƿ�����ͨ
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            scanf("%d",&h[i][j]);
            if(h[i][j]>r)
                r=h[i][j];
            }//��������r
	for(int i=1;i<=n;i++)
        for(int j=1,t;j<=m;j++){
            scanf("%d",&t);
            if(t)
                a[++len]=id(i,j);
        }//����
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))//�ж�
		{
			ans=mid;
			r=mid-1;//�����ұ߽�
		}
		else
            l=mid+1;//������߽�
	}
	printf("%d",ans);//���
}
