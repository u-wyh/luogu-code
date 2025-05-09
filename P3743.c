#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool check(double ans,double m,int n,double *a ,double *b){
    double p=ans*m;
    double sum=0;
    for(int i=1;i<=n;i++){
		if(a[i]*ans<=b[i]){//���豸���е���������ʹ��ʱ����Ҫ������
			continue;//���Ը��豸
		}
		sum+=(a[i]*ans-b[i]);//�����ó������磬ʹ�豸���е���������ʹ��ʱ����Ҫ������������¼��Ҫ��������
	}
	return sum<=p;
}

int main()
{
    int n;
    double m,sum=0;
    scanf("%d %lf",&n,&m);
    double a[n+1],b[n+1];
    double ans,l=0,r=1e6,mid;
    for(int i=1;i<=n;i++){
        scanf("%lf %lf",&a[i],&b[i]);
        sum+=a[i];
    }
    if(m>=sum){
        printf("-1\n");
        return 0;
    }
    while(r-l>1e-8){
        mid=(l+r)/2;
        if(check(mid,m,n,a,b)){
            l=mid;
        } else{
            r=mid;
        }
    }
    printf("%lf",l);
    return 0;
}
