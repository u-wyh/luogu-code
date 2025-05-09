// һȺ����ˮ����ÿ��λ�õ�ˮλ�߶�
// ���������Ƚϸ��ӣ�����������
// �������� : https://www.luogu.com.cn/problem/P5026
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int offset=30005;

int n,m;
int v,x;
int arr[2030005];

void Set(int l,int r,int s,int e,int d){
    arr[l+offset]+=s;
    arr[l+1+offset]+=(d-s);
    arr[r+1+offset]-=(d+e);
    arr[r+2+offset]+=e;
}

void build(){
    //����ǰ׺��
    for(int i=1;i<=n+offset;i++){
        arr[i]+=arr[i-1];
    }
    for(int i=1;i<=n+offset;i++){
        arr[i]+=arr[i-1];
    }
}

void fall(int v,int x){
    //��ʾv��x����ˮ  ���µĽ�������ĸ�����
    Set(x-3*v+1,x-2*v,1,v,1);
    Set(x-2*v+1,x,v-1,-v,-1);
    Set(x+1,x+2*v,-v+1,v,1);
    Set(x+2*v+1,x+3*v-1,v-1,1,-1);
}

int main()
{
    cin>>m>>n;
    while(m--){
        cin>>v>>x;
        fall(v,x);
    }
    build();
    for(int i=1;i<=n;i++){
        printf("%d ",arr[i+offset]);
    }
    return 0;
}
