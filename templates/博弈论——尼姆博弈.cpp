// ��ķ����(Nim Game)
// һ����n��ʯͷ����������������Ϸ
// ��ÿ����ҵĻغ��У������Ҫѡ���κ�һ���ǿյ�ʯͷ�ѣ��������ʯͷ���Ƴ�����������ʯͷ����
// ˭����������ʯͷ�ͻ�ʤ����������˭���ʤ
// �������� : https://www.luogu.com.cn/problem/P2197
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int eor=0;
        while(n--){
            int u;
            cin>>u;
            eor^=u;
        }
        if(eor){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}
