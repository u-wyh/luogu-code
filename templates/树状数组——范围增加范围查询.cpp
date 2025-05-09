// ��״���鷶Χ���ӡ���Χ��ѯģ��
// �������� : https://www.luogu.com.cn/problem/P3372
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
//��Χ���ӷ�Χ��ѯ��һ�����Ѷ�  ����һ�����߶������
//��Ȼ��״����Ҳͬ������ʵ��  ������Ҫ��ʽ�Ƶ�
//ά��������״����
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n,m;
long tree1[MAXN],tree2[MAXN];

int lowbit(int x){
    return x & -x;
}

void add(long *tree,int i,long  v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //ÿһ�ζ������Լ����Ҳ��1
    }
}

long sum(long *tree,int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //ÿһ�ζ���ȥ�Լ����Ҳ��1
    }
    return ans;
}

void Add(int l, int r, long v) {
    //��һ���������
    add(tree1, l, v);
    add(tree1, r + 1, -v);

    //�ڶ����������
    add(tree2, l, (l - 1) * v);
    add(tree2, r + 1, -(r * v));
}

//�����l��r���ۼӺ�
long range(int l, int r) {
    return (sum(tree1, r) * r - sum(tree2, r)) - (sum(tree1, l - 1) * (l - 1) - sum(tree2, l - 1));
    //�� ��1��r���ۼӺ�  ��ȥ��1��l-1���ۼӺ�
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        long  cur;
        cin>>cur;
        Add(i,i,cur);
    }
    long v;
    for (int i = 1, op, l, r; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            cin>>l>>r>>v;
            Add(l, r, v);
        } else {
            cin>>l>>r;
            cout<<range(l,r)<<endl;
        }
    }
    return 0;
}
