// �����޸ĵĿɳ־û��߶���ģ����1��java��
// ����һ������Ϊn������arr���±�1~n��ԭʼ������Ϊ��0�Ű汾
// һ����m��������ÿ���������������������е�һ��
// v 1 x y : ����v�Ű汾�����飬��xλ�õ�ֵ���ó�y�������°汾������
// v 2 x   : ����v�Ű汾�����飬��ӡxλ�õ�ֵ�������°汾�������v�汾һ��
// ÿ��������õ����°汾���飬�汾���Ϊ�����ļ���
// 1 <= n, m <= 10^6
// �������� : https://www.luogu.com.cn/problem/P3919
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;
const int MAXT = MAXN * 23;

int n, m;

// ԭʼ����
int arr[MAXN];

// �ɳ־û��߶�����Ҫ
// root[i] : i�Ű汾�߶�����ͷ�ڵ���
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// value[i] : �ڵ�i��ֵ��Ϣ��ֻ��Ҷ�ڵ��������Ϣ
int value[MAXT];

// �ɳ־û��߶����Ľڵ�ռ����
int cnt = 0;

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

// ����������ͷ�ڵ���
int build(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        value[rt] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

// �߶�����Χl~r����Ϣ��i�Žڵ���
// ��l~r��Χ�ϣ�jobiλ�õ�ֵ�����ó�jobv
// ���ɵ��½ڵ��ŷ���
int update(int jobi, int jobv, int l, int r, int i) {
    int rt = ++cnt;//�½�һ���ڵ㣨��;�ڵ㣩
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    value[rt] = value[i];
    //����ԭ����Ϣ
    if (l == r) {
        //������Ҫ�޸ĵĽڵ�λ��
        value[rt] = jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
        } else {
            rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

// �߶�����Χl~r����Ϣ��i�Žڵ���
// ����l~r��Χ��jobiλ�õ�ֵ
int query(int jobi, int l, int r, int i) {
	if (l == r) {
		return value[i];
	}
	int mid = (l + r) >> 1;
	if (jobi <= mid) {
		return query(jobi, l, mid, ls[i]);
	} else {
		return query(jobi, mid + 1, r, rs[i]);
	}
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    root[0]=build(1,n);
    for(int i=1;i<=m;i++){
        int op,x,y,version;
        version=read(),op=read(),x=read();
        if(op==1){
            y=read();
            root[i]=update(x,y,1,n,root[version]);
        }
        else{
            root[i]=root[version];
            cout<<query(x,1,n,root[version])<<endl;
        }
    }
    return 0;
}
