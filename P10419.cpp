#include<bits/stdc++.h>
using namespace std;

int n;
int nums[10][10];
int row[100],col[100];//�ֱ��ʾÿ�ֶ�����״̬��û�б�ѡ
int cnt=0;
int ok[1<<10];
vector<int>R[10];
vector<int>C[10];
int r[10],c[10];//��ʾ�к��е�ѡ��
int tot;//��ȷ��״̬����Ŀ

// ������������ȡ״̬s�е�jλ��״̬
inline int get(int s, int j) {
    return (s >> j) & 1;
}

// ��������������״̬s�е�jλ��״̬Ϊv���������µ�״̬
inline int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

void dfs(int i,int s,int ss,int rest,int now){
    //��ʾĿǰ�����iλ  ��һ����s  ����һ����ss  ����rest��1û����  �Զ����ƴ洢��Ч״̬now
    if(i==n&&rest==0){
        ok[++cnt]=now;
    }
    if(rest<=-1){
        return ;
    }
    if(s==ss){
        if(s!=1){
            dfs(i+1,1,s,rest-1,now|(1<<(n-1-i)));
        }
        if(s!=0){
            dfs(i+1,0,s,rest,now);
        }
    }
    else{
        dfs(i+1,1,s,rest-1,now|(1<<(n-1-i)));
        dfs(i+1,0,s,rest,now);
    }
}

int main()
{
    cin>>n;
    dfs(0,-1,-1,n/2,0);//һ��ʼ��0��ʾ����λ����0
    cout<<cnt<<endl;
    for(int i=0;i<=cnt;i++){
        row[i]=-1;
        col[i]=-1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            char c;
            cin>>c;
            if(c=='0')
                nums[i][j]=0;
            else if(c=='1')
                nums[i][j]=1;
            else{
                nums[i][j]=-1;
                tot++;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<nums[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;

    for(int i=0;i<n;i++){
        if(r[i]==0){
        //��ʾ��һ�л�û�н���
            for(int k=1;k<=cnt;k++){
                cout<<444<<endl;
                if(row[k]==-1){//��ʾ�������û�б�ѡ��
                    for(int j=0;j<n;j++){
                        if(nums[i][j]!=-1){
                            cout<<555<<' '<<k<<' '<<j<<endl;
                            if(nums[i][j]!=get(ok[k],j)){
                                //j=n;//��ʾ�ս��������
                                continue;
                            }
                            cout<<888<<endl;
                            if(j==n-1){
                                //��ʾ�����������
                                R[i].push_back(k);
                            }
                        }
                    }
                }
            }
            for(int j=0;j<n;j++){
                if(nums[i][j]==-1){
                    int sum=0;
                    for(int k=0;k<R[i].size();k++){
                        sum+=get(ok[R[i][k]],j);
                    }
                    if(sum==0){//ȫ��0
                        tot--;
                        nums[i][j]=0;
                    }
                    else if(sum==R[i].size()){//ȫ��1
                        tot--;
                        nums[i][j]=1;
                    }
                }
            }
        }
    }//���ÿһ�еĳ�ɸ
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<nums[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<777<<endl;

//    for(int j=0;j<n;j++){
//        if(c[j]==0){
//        //��ʾ��һ�л�û�н���
//            for(int k=1;k<=cnt;k++){
//                if(col[k]==-1){//��ʾ�������û�б�ѡ��
//                    for(int i=0;i<n;i++){
//                        if(nums[j][i]!=-1){
//                            if(nums[j][i]!=get(ok[k],i)){
//                                i=n;//��ʾ�ս��������
//                                continue;
//                            }
//                            if(i==n-1){
//                                //��ʾ�����������
//                                C[j].push_back(k);
//                            }
//                        }
//                    }
//                }
//            }
//            for(int i=0;i<n;j++){
//                if(nums[j][i]==-1){
//                    int sum=0;
//                    for(int k=0;k<C[j].size();k++){
//                        sum+=get(ok[R[i][k]],n-i-1);
//                    }
//                    if(sum==0){//ȫ��0
//                        tot--;
//                        nums[j][i]=0;
//                    }
//                    else if(sum==C[j].size()){//ȫ��1
//                        tot--;
//                        nums[j][i]=1;
//                    }
//                }
//            }
//        }
//    }//���ÿһ�еĳ�ɸ
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            cout<<nums[i][j]<<' ';
//        }
//        cout<<endl;
//    }

//    while(tot!=0){
//        for(int i=0;i<n;i++){
//        if(r[i]==0){
//        //��ʾ��һ�л�û�н���
//            for(int k=1;k<=cnt;k++){
//                cout<<444<<endl;
//                if(row[k]==-1){//��ʾ�������û�б�ѡ��
//                    for(int j=0;j<n;j++){
//                        if(nums[i][j]!=-1){
//                            cout<<555<<endl;
//                            if(nums[i][j]!=get(ok[k],n-1-j)){
//                                //j=n;//��ʾ�ս��������
//                                continue;
//                            }
//                            //cout<<888<<endl;
//                            if(j==n-1){
//                                //��ʾ�����������
//                                R[i].push_back(k);
//                            }
//                        }
//                    }
//                }
//            }
//            for(int j=0;j<n;j++){
//                if(nums[i][j]==-1){
//                    int sum=0;
//                    for(int k=0;k<R[i].size();k++){
//                        sum+=get(ok[R[i][k]],n-j-1);
//                    }
//                    if(sum==0){//ȫ��0
//                        tot--;
//                        nums[i][j]=0;
//                    }
//                    else if(sum==R[i].size()){//ȫ��1
//                        tot--;
//                        nums[i][j]=1;
//                    }
//                }
//            }
//        }
//    }//���ÿһ�еĳ�ɸ
//    cout<<777<<endl;
//    for(int j=0;j<n;j++){
//        if(c[j]==0){
//        //��ʾ��һ�л�û�н���
//            for(int k=1;k<=cnt;k++){
//                if(col[k]==-1){//��ʾ�������û�б�ѡ��
//                    for(int i=0;i<n;i++){
//                        if(nums[j][i]!=-1){
//                            if(nums[j][i]!=get(ok[k],n-1-i)){
//                                i=n;//��ʾ�ս��������
//                                continue;
//                            }
//                            if(i==n-1){
//                                //��ʾ�����������
//                                C[j].push_back(k);
//                            }
//                        }
//                    }
//                }
//            }
//            for(int i=0;i<n;j++){
//                if(nums[j][i]==-1){
//                    int sum=0;
//                    for(int k=0;k<C[j].size();k++){
//                        sum+=get(ok[R[i][k]],n-i-1);
//                    }
//                    if(sum==0){//ȫ��0
//                        tot--;
//                        nums[j][i]=0;
//                    }
//                    else if(sum==C[j].size()){//ȫ��1
//                        tot--;
//                        nums[j][i]=1;
//                    }
//                }
//            }
//        }
//    }//���ÿһ�еĳ�ɸ
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            cout<<nums[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    }
    return 0;
}
