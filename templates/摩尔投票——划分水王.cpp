// ��������ʹ��ˮ������ͬ
// ����һ����СΪn������nums
// ˮ������ָ�������г��ִ�������n/2����
// �������е�һ�����ֵ��±꣬ʹ�����ˮ���������Ҳ�ˮ����
// ������鲻���������Ļ��ַ���-1
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
    int ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i]==cand){
            ans++;
        }
    }
    // lc : ˮ���������ֵĴ�Ƶ
    // rc : ˮ�����Ҳ���ֵĴ�Ƶ
    for (int i = 1, lc = 0, rc = ans; i < n; i++) {
        if (nums[i] == cand) {
            lc++;
            rc--;
        }
        if (lc > i / 2 && rc > (n - i) / 2) {
            // �ҵ��˻��ֵ�ֱ�ӷ���
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<"not find"<<endl;
    return 0;
}

