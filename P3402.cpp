// �ɳ־û����鼯ģ���⣬C++��
// ���ִ�1��n��һ��ʼÿ���������ڵļ���ֻ���Լ�
// ʵ���������ֲ�������i�������������������ֵ�״����Ϊi�汾������һ������m��
// ���� 1 x y : �����ϸ��������ɵİ汾����x�ļ�����y�ļ��Ϻϲ������ɵ�ǰ�İ汾
// ���� 2 x   : ������x�Ű汾��״�������ɵ�ǰ�İ汾
// ���� 3 x y : �����ϸ��������ɵİ汾�����ɵ�ǰ�İ汾����ѯx��y�Ƿ�����һ������
// 1 <= n <= 10^5
// 1 <= m <= 2 * 10^5
// �������� : https://www.luogu.com.cn/problem/P3402
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXT = MAXN*80;

int n,m;

int faroot[MAXM];
int szroot[MAXM];

int cnt=0;
int ls[MAXT];
int rs[MAXT];
int val[MAXT];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int buildfa(int l,int r){
    int rt=++cnt;
    if(l==r){
        val[rt]=l;
    }
    else{
        int mid=(l+r)/2;
        ls[rt]=buildfa(l,mid);
        rs[rt]=buildfa(mid+1,r);
    }
    return rt;
}

int buildsz(int l,int r){
    int rt=++cnt;
    if(l==r){
        val[rt]=1;
    }
    else{
        int mid=(l+r)/2;
        ls[rt]=buildsz(l,mid);
        rs[rt]=buildsz(mid+1,r);
    }
    return rt;
}

int update(int pos,int v,int l,int r,int i){
    int rt=++cnt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    if(l==r){
        val[rt]=v;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            ls[rt]=update(pos,v,l,mid,ls[rt]);
        }
        if(pos>mid){
            rs[rt]=update(pos,v,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return val[i];
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            return query(pos,l,mid,ls[i]);
        }
        else{
            return query(pos,mid+1,r,rs[i]);
        }
    }
}

int find(int x,int v){
    int fa=query(x,1,n,faroot[v]);
    while(fa!=x){
        x=fa;
        fa=query(x,1,n,faroot[v]);
    }
    return x;
}

void un(int x,int y,int v){
    int fx=find(x,v);
    int fy=find(y,v);
    if(fx==fy){
        return ;
    }
    int xsz=query(fx,1,n,szroot[v]);
    int ysz=query(fy,1,n,szroot[v]);
    if(xsz>ysz){
        szroot[v]=update(fx,xsz+ysz,1,n,szroot[v]);
        faroot[v]=update(fy,fx,1,n,faroot[v]);
    }
    else{
        szroot[v]=update(fy,xsz+ysz,1,n,szroot[v]);
        faroot[v]=update(fx,fy,1,n,faroot[v]);
    }
}

int main()
{
    n=read(),m=read();
    faroot[0]=buildfa(1,n);
    szroot[0]=buildsz(1,n);
    for(int i=1;i<=m;i++){
        faroot[i]=faroot[i-1];
        szroot[i]=szroot[i-1];
        int op,x,y;
        op=read();
        if(op==1){
            x=read(),y=read();
            un(x,y,i);
        }
        else if(op==2){
            x=read();
            faroot[i]=faroot[x];
            szroot[i]=szroot[x];
        }
        else{
            x=read(),y=read();
            int fx=find(x,i);
            int fy=find(y,i);
            if(fx==fy){
                printf("1\n");
            }
            else{
                printf("0\n");
            }
        }
    }
    return 0;
}