//P7818
// ǰ��֪ʶ����״����  
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
long long k;

int arr[MAXN];//һ��ʼ����������
int pos[MAXN];//��ʾÿ�����ֵ�λ��  eg: arr[5]=6  ��ôpos[6]=5  :5λ���ϵ�������6  ��ô6���������5λ����   ���������Ϊ��vis�������õ�
bool vis[MAXN];//��ʾiλ�õ������Ƿ��Ѿ��������ˣ����Ѿ��ans�������ˣ�
int pre[MAXN];//��ʾiλ���ϵ�����  ��ǰ���ж��ٸ����ֱ�����

int tree[MAXN];//��״����
int ans[MAXN];//��������������ú������

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

// ��״����
inline int lowbit(int x){
	return x&(-x);
}

void add(int x){
	while(x<=n){
		tree[x]+=1;
		x+=lowbit(x);
	}
}

int query(int x){
	int ans=0;
	while(x){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}

// С����
struct compare{
	bool operator()(const pair<int,int>&a,const pair<int,int>&b){
		if (a.second != b.second) {
            return a.second > b.second; 
        } else {
            return a.first > b.first; 
        }
	}
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

int main()
{
	scanf("%d %lld",&n,&k);
	for(int i=1;i<=n;i++){
		arr[i]=read();
		pos[arr[i]]=i;
		add(arr[i]);
		pre[arr[i]]=i-query(arr[i]);
	}

	int now=1;//��ʾ����ans�������һλ��
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(k==0){
			//��ʾû�н����Ļ����� ֱ������
			break;
		}

		if(!heap.empty()&&heap.top().second-cnt<=k){
			ans[now++]=heap.top().first;
			vis[pos[heap.top().first]]=1;
			k-=(heap.top().second-cnt);
			heap.pop();
			heap.push({i,pre[i]+cnt});
			cnt++;
		}

		if(k>=pre[i]){
			ans[now++]=i;
			k-=pre[i];
			vis[pos[i]]=1;
			cnt++;
		}
		else{
			heap.push({i,pre[i]+cnt});
		}
	}

	if(k==0){
		//���k��0  ˵���϶�����λ��û����ò���Ҳ����������  ��ô��û��������ְ������ǵ����˳�����뼴��
		//�����Ϊʲô��������vis  ��  pos����
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				ans[now++]=arr[i];
			}
		}
	}
	if(k&1){
		//���k��һ������ ��ô���ȿ���˵���������ֶ�����֮��  k����ʣ��  ��Ϊk!=0
		//��ô��ĿҪ�����Ҫ����k�� ����Ҫ��Ҫ���ֵ�����С ��ôÿ�������� ʵ������û�н�����
		//���Ե�Ч�ڽ���һ��  ��ô��õ�һ���ǽ�����������ֽ���һ��
		swap(ans[n-1],ans[n]);
	}
	//�����
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}