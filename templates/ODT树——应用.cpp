//P4344
#include <bits/stdc++.h>
using namespace std;
#define IT set<Node>::iterator

int n,m;

// ��������ڵ�ṹ��
struct Node {
    int l, r;       // ��������Ҷ˵�
    mutable int v;  // �����ֵ��mutable ������ const �������޸�
    Node(int L, int R = -1, int V = 0) : l(L), r(R), v(V) {}
    // ���� < ����������� set ����
    bool operator<(const Node &o) const {
        return l < o.l;
    }
};

set<Node> s; // ʹ�� set �洢����ڵ�

// �������� pos ���ָ���طָ��������������
IT split(int pos) {
    IT it = s.lower_bound(Node(pos)); // �ҵ���һ����˵� >= pos ������
    if (it != s.end() && it->l == pos)
        return it; // ��� pos ������ĳ���������㣬ֱ�ӷ���
    --it; // �����ҵ����� pos ������
    int L = it->l, R = it->r, V = it->v;
    s.erase(it); // ɾ��ԭ����
    s.insert(Node(L, pos - 1, V)); // ������벿��
    return s.insert(Node(pos, R, V)).first; // �����Ұ벿�ֲ����ص�����
    // ����һ��pair�����е�һ��Ԫ����һ����������ָ������Ԫ�أ����Ѿ����ڵ�Ԫ�أ���
    // �ڶ���Ԫ����һ������ֵ����ʾ�����Ƿ�ɹ���
}

// ���丳ֵ����
void assign(int l, int r, int val) {
    IT itr = split(r + 1), itl = split(l); // �ָ����� [l, r]
    s.erase(itl, itr); // ɾ�� [l, r] �ڵ��������� ɾ����itl��itr֮�������Ԫ�أ�������itr��
    s.insert(Node(l, r, val)); // �����µ�����
}

void compute(int l,int r,int u,int v){
    IT itr=split(r+1),itl=split(l);
    int sum=0;
    for(;itl!=itr;itl++){
        if(itl->v==1){
            sum+=(itl->r - itl->l +1);
        }
    }
    assign(l,r,0);
    itr=split(v+1),itl=split(u);
    //cout<<sum<<endl;
    for(;itl!=itr&&sum;itl++){
        if(itl->v==0){
            if(sum>=(itl->r-itl->l+1)){
                itl->v=1;
                sum-=(itl->r-itl->l+1);
            }
            else{
                assign(itl->l,itl->l+sum-1,1);
                sum=0;
            }
        }
    }
}

int query(int l,int r){
    IT itr=split(r+1),itl=split(l);
    int res=0,ans=0;
    for(;itl!=itr;itl++){
        if(itl->v==0){
            res+=(itl->r-itl->l+1);
        }
        else{
            ans=max(ans,res);
            res=0;
        }
    }
    return max(ans,res);//��Ϊ����п�����0��β
}

int main()
{
    cin>>n>>m;
    s.insert(Node(1, n, 1));
    for(int i=1;i<=m;i++){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==0){
            assign(l,r,0);
        }
        else if(op==1){
            int u,v;
            cin>>u>>v;
            compute(l,r,u,v);
        }
        else{
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}

