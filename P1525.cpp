#include<bits/stdc++.h>
using namespace std;
int n,m,f[40001],x,y;
struct data
{
    int a,b,c;
} e[100001];

int gz(const data &a,const data &b){
    if(a.c>b.c)
        return 1;
    else
        return 0;
}

int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1; i<=m; i++)
        scanf("%d %d %d",&e[i].a,&e[i].b,&e[i].c);
    for(int i=1; i<=n*2; i++)
        f[i]=i;
    sort(e+1,e+m+1,gz);
    for(int i=1; i<=m; i++){
        x=find(e[i].a);
        y=find(e[i].b);
        if(x==y){
            printf("%d\n",e[i].c);
            return 0;
        }
        //������ģ���˵ڶ�������    y��b�ǵ���   x��a�ǵ���
        f[y] = find(e[i].a + n);//д��f[find(e[i].b)]=find(e[i].a+n)�������
        f[x] = find(e[i].b + n);
    }
    puts("0");
    return 0;
}
//����ΪʲôҪ����n   ��Ϊһ�����˲������������� �ͱ����������һ������
//��������ֻ��ȷ����������ļ����Ĳ��鼯   ��������������ǲ鲻��
//����Ҫ����n   ��n���ʹ����ͬλ�ã�+n���ֿ��ɵ��˺�����
//�ڵ�һ���˵�ʱ��  ʵ�����������鼯����Ч����  ��a��b+n  ���
