//P9725
#include<bits/stdc++.h>
using namespace std;

int u[100005]={0},v[100005]={0},du[100005]={0};

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        memset(du,0,sizeof du);//�����������
        for(int i=1;i<n;i++){
            cin>>u[i]>>v[i];
            du[u[i]]++;
            du[v[i]]++;//��Ӧ��ȼ�һ
        }
        if(n<=3){
            //��������㶼û�� һ������
            puts("-1");
            continue;
        }
        map<int,int> q;//��ʾ��iΪ����ֱ�����ӵĵ���  �ж�����Ҷ�ӽ��
        int leaf=0;
        for(int i=1;i<n;i++){
            if(du[u[i]]==1)q[v[i]]++,leaf++;
            if(du[v[i]]==1)q[u[i]]++,leaf++;//���һ���ڵ���Ҷ�ӽ��  ��ô���������ĵ��һ
        }
        if(q.size()==1){
            //˵���Ǿջ�ͼ   һ������ ��ֻ��һ���ڵ���Ҷ�ӽ��
            puts("-1");
            continue;
        }
        //������һ����û���˳�  ˵��һ���д�
        int ans=0;
        for(auto it=q.begin();it!=q.end();it++){
            ans=max(ans,it->second);//��ʾһ���ڵ�������Ӷ��ٸ�Ҷ�ӽ��
        }
        cout<<((ans>leaf/2)?ans:(leaf+1)/2)<<endl;
        //���˵��һ���ڵ��Ҷ�ӽ���������Ҷ�ӽ������һ��  ��ôû�취 ֻ�����������
        //�������Ҷ�ӽ�����������  ����ȡ��
    }
    return 0;
}

