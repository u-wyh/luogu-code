//P10513
//���������������� ��һ����������
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

struct node{
    int l,r;
    int lcnt,rcnt;//ͳ�������ź������ŵ�����
    int ans,result;//�ֱ�ͳ�� () �� )( ������
    //ͳ��result��Ϊ�˷�תʱ�������
    int tag;//�����1  ��ʾ�з�ת����
}tree[MAXN<<2];
char str[MAXN];
int n,m;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

void up(int i){
    tree[i].lcnt=tree[i<<1].lcnt+tree[i<<1|1].lcnt;
    tree[i].rcnt=tree[i<<1].rcnt+tree[i<<1|1].rcnt;
    tree[i].ans=tree[i<<1].ans+tree[i<<1|1].ans+
                min(tree[i<<1].lcnt-tree[i<<1].ans,tree[i<<1|1].rcnt-tree[i<<1|1].ans);
    tree[i].result=tree[i<<1].result+tree[i<<1|1].result+
                min(tree[i<<1].rcnt-tree[i<<1].result,tree[i<<1|1].lcnt-tree[i<<1|1].result);
}
//���ϸ�����Ϣ

void build(int l,int r,int i){
    if(l==r){
        tree[i].lcnt=str[l]=='('?1:0;
        tree[i].rcnt=str[l]==')'?1:0;
        tree[i].ans=0;
        tree[i].result=0;
    }
    else{
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    tree[i].l=l;
    tree[i].r=r;
    tree[i].tag=0;
}

inline void updatelazy(int i) {
    tree[i].tag^=1;
    //�����ǵ���˼�Ǹýڵ����Ѿ��޸Ĺ���  �����������޸ĵĴ���
    //�����Լ����������ӽڵ�û���޸�  ��Ϊû�б�Ҫ
    //ֻ��ʹ��������ӵ�ʱ��Ż��޸�

    int temp=tree[i].lcnt;
    tree[i].lcnt=tree[i].rcnt;
    tree[i].rcnt=temp;

    temp=tree[i].ans;
    tree[i].ans=tree[i].result;
    tree[i].result=temp;
}
//��ס��  �������´���
//������Ҫ��ʱ��Ż����

// ����Ϣ���·�
inline void down(int i) {
    if (tree[i].tag) {
        updatelazy(i << 1);
        updatelazy(i << 1 | 1);
        tree[i].tag=0;
    }
}

inline void update(int jobl,int jobr,int l,int r,int i){
    if (jobl <= l && r <= jobr) {
        updatelazy(i);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        //��ʾ֮ǰ����ڵ����޸���Ϣ  ��ô���´���
        //��Ȼ������Ƿ�ת���� ����������Ϊ���η�תʵ���Ͼ�û��������  ����û��Ҫdown
        //�����뷨�Ǵ���� ��Ϊ��һ�ο�����1~10  ��һ����1~5 ��Χ��һ��
        //�������ת ��ôʵ��������һ��������һ�η�ת
        if (jobl <= mid) {
            update(jobl, jobr,l, mid, i << 1);
        }
        if (jobr > mid) {
            update(jobl, jobr,mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}
//�����Ŀ��Ҫ������Ƿ�ת  ����Ҫjobv

void add(node &p, node &a, node &b)
{
	p.lcnt = a.lcnt + b.lcnt;
	p.rcnt = a.rcnt + b.rcnt;
	p.ans = a.ans + b.ans + min(a.lcnt - a.ans, b.rcnt - b.ans);
	p.result = a.result + b.result + min(a.rcnt - a.result, b.lcnt - b.result);
}
//������Ϊ��query�����  ���Բ���Ҫtag l r��

node query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return tree[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    node a={0,0,0,0,0,0,0},b={0,0,0,0,0,0,0},ans={0,0,0,0,0,0,0};
    if (jobl <= mid) {
        a=query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        b=query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    add(ans,a,b);
    return ans;
}
//�����Ĳ�ѯ�𰸲��ܽ���ͨ�����Ҷ��ӵ���ӵõ�
//����Ҫ�м�Ĳ���  ���Զ���Ϊnode

signed main()
{
    cin>>n;
    scanf("%s", str + 1);//�����ʼ�ַ�
    cin>>m;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        op=read();
        l=read();
        r=read();
        if(op==1){
            update(l,r,1,n,1);
        }
        else{
            cout<<query(l,r,1,n,1).ans<<endl;
        }
    }
    return 0;
}
