// �����η���ȡʯ��(��ʲ������չ)
// һ����n��ʯ�ӣ�������������
// ÿһ�ֵ�ǰѡ�ֿ����� p��k�η� ��ʯ��
// ��ǰѡ�ֿ����������p��k����Ҫ��֤p��������k����Ȼ��
// �õ����һ��ʯ�ӵ��˻�ʤ
// ����ʯ��������˭Ӯ
// �������Ӯ������"October wins!"
// �������Ӯ�����"Roy wins!"
// �������� : https://www.luogu.com.cn/problem/P4018
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
        if(n%6==0){
            cout<<"Roy wins!\n";
        }
        else{
            cout<<"October wins!\n";
        }
    }
    return 0;
}
