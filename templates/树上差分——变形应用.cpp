//P9648
// 1��һ���ڵ��������߱�Ȩ��ͬ��
// ����������������ڵ�ֻ�п������������������Ľڵ�������С�
// 2һ���ڵ�����һ�߱�Ȩ��������븸�׽ڵ�ı�Ȩ��ͬ��
// ��ô���ڵ�ֻ�п����������������ڵ�������С�
// 3��һ���ڵ����д������߱�Ȩ��ͬ�������߱�Ȩ��ͬ����������븸�׽ڵ�ı�Ȩ��ͬ��
// ��һ�����ж��������ߵı�Ȩ��ͬ�������۸��ڵ����Ķ��޷��Ϸ���ֱ����� 0
//��ʵ����ϸ������ϲ��������ǲ��  ����ÿ�����ӻ�Ҫ�̳и��׵���Ϣ
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 30;

int n;

//���sum�ĺ�������������Ϊͷ���    �����Ҫ�����������Ŀ
//����һ���ڵ���������ͬ��Ȩ�ı�   �ж��ٸ�����������Ҫ���
int sum;
int arr[MAXN];//��ʾ����ڵ���Խ�����������  ��û��ͳ�����մ𰸵�ʱ���ǲ������
bool flag;//�ж��Ƿ��д�
int ans;

//����ͳ��������ǰ�ڵ�  ���ĺ�����Ϣ
int tot[MAXM];
int lst[MAXM];

int cnt=1;
int head[MAXN];
int to[MAXN<<1];
int weight[MAXN<<1];
int Next[MAXN<<1];

void build(){
    cnt=1,ans=0,flag=false;
    sum=0;
    for(int i=1;i<=n;i++){
        head[i]=0;
        arr[i]=0;
    }
}

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int fa,int val){
    //u�Ǵ�fa����val�ı�Ȩ����
    for(int i=1;i<=27;i++){
        tot[i]=lst[i]=0;//ȫ�����ԭʼ��Ϣ
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i],w=weight[i];
        if(v==fa){
            //�����ظ���
            continue;
        }
        if(w==val){
            //��Ȩ�͸�����ͬ  ��ô��ǰ�ڵ���Ϸ���ʵ����Ӱ��
            //����������Ҳ��Ӱ��
            //����Ҫע��������ǲ��ܵ�ͷ����  
			arr[u]--;
			arr[v]++;
            //��������֮�� �൱��u���³���v��������нڵ㶼û���ʸ��Ϊ��ѡ�ڵ���
        }
        if(tot[w]==1){
            //��ͬ�ı�Ȩ��ǰ�й�һ��
			if(val == w){
			    //��������һ�� ����������һ����  Ҳ��������ڵ���������ͬ�ı�Ȩ  ֱ�ӽ���
				flag = true;
			}
			else{
				arr[lst[w]]++, arr[v]++, sum++;
			}
        }
        else if(tot[w]>1){
            //��ͬ��Ȩ�ı��Ѿ����������� ��������һ��  
            flag=true;
        }
        tot[w]++,lst[w]=v;
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i],w=weight[i];
        if(v==fa){
            //�����ظ���
            continue;
        }
        dfs(v,u,w);
    }
}

void compute(int u,int fa){
    arr[u]+=arr[fa];
    if(arr[u]==sum){
        ans++;
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=fa){
            compute(v,u);
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        build();
        for(int i=1;i<n;i++){
            int u,v,w;
            char c;
            cin>>u>>v>>c;
            w=c-'a'+1;
            addedge(u,v,w),addedge(v,u,w);
        }
        dfs(1,0,0);
        if(flag){
            cout<<0<<endl;
        }
        else{
            compute(1,0);
            cout<<ans<<endl;
        }
    }
    return 0;
}
