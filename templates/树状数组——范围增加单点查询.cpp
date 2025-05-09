// ��״���鷶Χ���ӡ������ѯģ��
// �������� : https://www.luogu.com.cn/problem/P3368
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int tree[MAXN];
//�������ʵ������һ���������
int n,m;

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //ÿһ�ζ������Լ����Ҳ��1
    }
}
//��������������������iλ�ü���v

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //ÿһ�ζ���ȥ�Լ����Ҳ��1
    }
    return ans;
}
//�����������������������1��i���ֵ��ۼӺ�  ��ô���൱���������ʵ��ֵ

int main()
{
    cin>>n>>m;
    int pre=0;
    for(int i=1;i<=n;i++){
        int cur;
        cin>>cur;
        add(i,cur-pre);
        //���ǳ�ʼʱ��Ϊ��״�������������ȫ����0   ֱ�ӵ���add����������״����
        //cur-pre  �൱�ڲ��ֵ  ���ǰ������ֵ�ӵ����λ����
        //��Ȼ  ����ֱ�ӿ�����ôд  add(i,cur)  add(i+1,-cur)   �������Ҳ��һ����
        pre=cur;
    }
    for(int i=1,op,x,y,k;i<=m;i++){
        cin>>op;
        if(op==1){
            cin>>x>>y>>k;
            add(x,k);
            add(y+1,-k);
        }else {
            cin>>x;
            cout<<sum(x)<<endl;
        }
    }
    return 0;
}
