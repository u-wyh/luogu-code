#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

struct node{
    int pos,col;
}nums[MAXN];
int n;
int sum[MAXN];
map<int,int>m;

bool cmp(node a,node b){
    return a.pos<b.pos;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        char c;
        cin>>nums[i].pos>>c;
        if(c=='W')
            nums[i].col=1;
        else
            nums[i].col=-1;
    }
    sort(nums+1,nums+n+1,cmp);
    int ans=0;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+nums[i].col;

        //С��0�Ĳ���  ֻ��¼��һ�γ��ֵ�ʱ�������
        //���ҵ�һ�γ��ֵĻ�һ�����ṱ�״�
        //��Ϊ���sum�仯���������Ҳ��ᱣ�ֲ����
        //��һ�γ���˵����ǰ���е�ֵ���Ǵ�������  Ҫ��Ȼ�������ǵ�һ�γ���
        if(m[sum[i]]==0&&sum[i]<0)
        	m[sum[i]]=i;
		else if(sum[i]<0)
			ans=max(ans,nums[i].pos-nums[m[sum[i]]+1].pos);

		if(sum[i]%2==0&&sum[i]>=0)
			ans=max(ans,nums[i].pos-nums[1].pos);//��ʾ��ͷ��ʼ������  ��ɫţ���������ż��  ��ôһ������ͨ��Ϳɫ�ĳ�һ����
		else if(sum[i]>=0)
			ans=max(ans,nums[i].pos-nums[2].pos);//��ʾ��ͷ��ʼ������  ��ɫ��ţ������������� ��ô���۵�һͷţ����ʲô��ɫ
            //ֻҪ��Ҫ��һͷţ  ��һ������ͨ��Ϳɫʵ��һ��
    }
    cout<<ans<<endl;
    return 0;
}
