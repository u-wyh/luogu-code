#include<bits/stdc++.h>
using namespace std;

long long n,m,k,q,s,t,f[100][100],a[100][100],b[100][100];

int main(){
    scanf("%lld%lld",&n,&m);
    //��ʼ��
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=INT_MAX;
   		}
    }
	for(int i=1;i<=m;i++){
		long long x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		f[x][y]=min(f[x][y],z);//�����ر�ȡ��̵�һ��
	}
	scanf("%lld%lld",&k,&q);
    //��ʼ��a
	for (int i=1;i<=n;i++){
		for (int j=1;j<= n;j++){
			a[i][j]=f[i][j];
		}
	}
	k=min(k,n);
	for(int kk=2;kk<=k;kk++){//��k��
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				b[i][j]=a[i][j];
			}
		}
		for(int lg=1;lg<=n;lg++){
			for (int i=1;i<=n;i++){
				for (int j=1;j<=n;j++){
					b[i][j]=min(b[i][j],a[i][lg]+f[lg][j]);//ֻת��һ����
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
			    a[i][j]=b[i][j];//����
			}
		}
	}
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&s,&t);
		if(s==t)printf("0\n");//����s=t�����
		else if(a[s][t]==INT_MAX)printf("-1\n");//�޷�����
		else printf("%d\n",a[s][t]);
	}
	return 0;
}
