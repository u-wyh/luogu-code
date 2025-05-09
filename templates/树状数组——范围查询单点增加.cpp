// ��״���鵥�����ӡ���Χ��ѯģ��
// �������� : https://www.luogu.com.cn/problem/P3374
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int tree[MAXN];
int n,m;

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //ÿһ�ζ������Լ����Ҳ��1
        //�൱�ڰ����а�����״̬�����ֶ�����
    }
}

//�����������Ǵ�1��i�������ֵĺ�
int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //ÿһ�ζ���ȥ�Լ����Ҳ��1
        //�൱�ڽ����������ֿ�Ϊ����С�������  �ͳ˷�����������
    }
    return ans;
}

int query(int l,int r){
    return sum(r)-sum(l-1);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        add(i,v);
        //���ǳ�ʼʱ��Ϊ��״�������������ȫ����0   ֱ�ӵ���add����������״����
    }
    for(int i=1,op;i<=m;i++){
        cin>>op;
        if(op==1){
            int x,v;
            cin>>x>>v;
            add(x,v);
        }else {
            int l,r;
            cin>>l>>r;
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}
