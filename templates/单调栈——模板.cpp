//����ջģ��
//ͳ��ÿ��λ����ߺ��ұߵ�һ�����Լ�С��Ԫ��λ��
//��ȵĲ���
#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,r=0;
int nums[10000],L[10000],R[10000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    int cur;
    for(int i=0;i<n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            //ջ�����Ԫ���ϸ��ѹС
            cur=st[--r];
            L[cur]=r>0?st[r-1]:-1;//������û��Ԫ�� ��ô����-1
            R[cur]=i;//�ұߵ���Ȼ�������������ջ��λ����
        }
        st[r++]=i;
    }

    while (r > 0) {
        //��ջ��ʣ���Ԫ�ص���
        cur = st[--r];
        L[cur] = r > 0 ? st[r - 1] : -1;//�����ջ���Լ�ǰ���һ��Ԫ��
        R[cur] = -1;//�ұ�һ����û�б��Լ�С����
    }

    for(int i=n-2;i>=0;i--){
        if(R[i]!=-1&&nums[i]==nums[R[i]]){
            //����������ȵ����
            //��ô����r�����������r��r
            R[i]=R[R[i]];
        }
    }

    for(int i=0;i<n;i++)
        cout<<L[i]<<' '<<R[i]<<endl;
    return 0;
}