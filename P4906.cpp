#include<bits/stdc++.h>
using namespace std;

vector<int>vec[21];
int sta[21];//��ʾ����������غ����ʲô�������ݱ仯1��ʾ�仯
//����Ҫע��  һ��ʼȫ����0  ��ñ�Ϊ1
int n;
int dp[1<<21];
queue<int>q;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int t;
        cin>>t;
        for(int j=1;j<=t;j++){
            int u;
            cin>>u;
            vec[i].push_back(u);
        }
    }
    for(int i=1;i<=n;i++){
        //sta[i]=1;//��ʼ��
        sta[i]^=(1<<i);//�ȸı䵱ǰ��״̬
        //cout<<vec[i].size()<<endl;
        for(int j=0;j<vec[i].size();j++){
            sta[i]^=(1<<vec[i][j]);//�ı�ֱ��������״̬
        }
        for(int j=0;j<vec[i].size();j++){
            for(int k=0;k<vec[vec[i][j]].size();k++){
                //cout<<vec[vec[i][j]][k]<<' ';
                sta[i]^=(1<<vec[vec[i][j]][k]);
            }
        }
        //cout<<endl;
//        bitset<8> binary(sta[i]);
//        cout<<' '<<binary<<endl;
        //cout<<' '<<sta[i]<<endl;
    }
    dp[(1<<(n+1))-2]=1;//���մ�Ҫ��ȥ1
    //cout<<' '<<(1<<(n+1))-1<<endl;
    q.push((1<<(n+1))-2);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(u==0){
            cout<<dp[u]-1;
            return 0;
        }
        for(int i=1;i<=n;i++){
            int status=sta[i]^u;
            if(!dp[status]){
                dp[status]=dp[u]+1;
                q.push(status);
            }
        }
    }
    cout<<"Change an alarm clock��please!";
    return 0;
}
