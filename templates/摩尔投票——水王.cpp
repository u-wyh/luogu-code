// ���ִ�������n/2����
// ����һ����СΪn������nums
// ˮ������ָ�������г��ִ�������n/2����
// �������е�ˮ������������鲻����ˮ��������-1
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;

int n;
int nums[MAXN];
int cand,hp;//����cand  hp�ֱ��Ǻ�ѡ���� Ѫ��

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        if(hp==0){
            //�����ǰѪ��hp==0  ˵��û�к�ѡ����
            //��ô�������������Զ�Ϊ��ѡ����  ����hp==1
            cand=nums[i];
            hp=1;
        }else if(nums[i]==cand){
            //�����ǰ���ֺͺ�ѡ����һ��  Ѫ��hp++
            hp++;
        }else{
            //�����һ��  ��ôhp--
            //���õ��ĺ�ѡ����  ���hpΪ1 ��ô��Ϊ0  �������1  ˵����ѡ����û�б仯
            hp--;
        }
    }
    if(hp==0){
        cout<<"no water-king"<<endl;
        return 0;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i]==cand){
            ans++;
        }
    }
    if(ans>n/2){
        cout<<"the water-king is: "<<cand<<endl;
    }else{
        cout<<"no water-king"<<endl;
    }
    return 0;
}
