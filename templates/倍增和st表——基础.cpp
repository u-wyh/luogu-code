//����Ǳ���˼���һ������  �ܻ���
//show������������Ϊ�˴�ӡ������ֵĶ�����
//show1 show2��������������������С�� 1�Ķ��ٴη�
#include<bits/stdc++.h>
using namespace std;

int t,m=31;

void show(int t,int m){
    //չʾһ�����Ķ����Ƹ�����λ�ϵ�����
    //���Ŀǰ�����ִ���(1<<p)  ˵����ǰλ����1  ��ô��ȥ�������
    //������0
    //m�ĺ��������������಻����2��m�η�
    int n=t;
    for(int p=m-1;p>=0;p--){
        if(t>=(1<<p)){
            printf("%d �ĵ�%02dλ�� 1\n",n,p);
            t-=(1<<p);
        }else
            printf("%d �ĵ�%02dλ�� 0\n",n,p);
    }
}

int show1(int t){
    int p=0;
    while((1<<p)<=t){
        p++;
    }
    return p-1;
}

int show2(int t){
    int p=0;
    while((1<<p)<=(t>>1)){
        p++;
    }
    return p;
}
//show1  show2  ��������������ʵ���������������t�����2�Ĵη�
//�������show2���ӵİ�ȫ   ���õ����������
//���磺20000000000  ��ʱshow1�޷����  ��ѭ����

int main()
{
    cin>>t;
    show(t,m);
    cout<<show2(t)<<endl;
    cout<<show1(t)<<endl;
    return 0;
}
