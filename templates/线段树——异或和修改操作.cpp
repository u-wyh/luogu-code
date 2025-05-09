//P5568
//Ϊʲô���·����丳ֵ������ǣ���Ϊ���丳ֵ����ʱ�����Ѿ������������������ǣ�
//��ʱ���������������Ǳ����丳ֵ������ģ��������´����丳ֵ��
//�����  ���ǽ� (a -> 2*a+2  [a -> 2*a+1   b)->  2*b   b] ->  2*b+1
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 65540<<1;

struct node{
    int len,sum,eor,change;
}tree[MAXN<<2];
vector<int>vec;//��������ڼ�¼���в���������  λ������1������λ��

void build(int l,int r,int i){
    tree[i].eor=0;
    tree[i].change=-1;
    tree[i].len=r-l+1;
    if(l==r){
        tree[i].sum=0;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i].sum=tree[i<<1].sum+tree[i<<1|1].sum;
    }
}

//����������Ϣ���´���һ��
//����ÿ��ֻҪ��һ��change��Ϣ ��ôeor��ϢҪ���
void changedown(int i){
    if(tree[i].change==-1){
        return ;
    }
    tree[i<<1].eor=tree[i<<1|1].eor=0;
    tree[i<<1].change=tree[i<<1|1].change=tree[i].change;
    tree[i<<1].sum=tree[i].change*tree[i<<1].len;
    tree[i<<1|1].sum=tree[i].change*tree[i<<1|1].len;
    tree[i].change=-1;
}

//���������Ϣ���´���һ��
//ÿ����һ��eor��Ϣ ��ôchange��Ϣ���ù�
//��Ϊÿ�����ͬʱ����eor  change��Ϣ  ��ôchange��Ϣһ����ǰ  ����ÿ������down��ʱ�� Ҳ��change��Ϣ��down
void eordown(int i){
    if(tree[i].eor==0){
        return ;
    }
    tree[i<<1].eor^=1;
    tree[i<<1|1].eor^=1;
    tree[i<<1].sum=tree[i<<1].len-tree[i<<1].sum;
    tree[i<<1|1].sum=tree[i<<1|1].len-tree[i<<1|1].sum;
    tree[i].eor=0;
}

void updatelazy(int i,int v){
    tree[i].change=v;
    tree[i].eor=0;
    tree[i].sum=tree[i].len*v;
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        updatelazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        changedown(i);
        eordown(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        tree[i].sum=tree[i<<1].sum+tree[i<<1|1].sum;
    }
}

void eorlazy(int i){
    tree[i].eor^=1;
    tree[i].sum=tree[i].len-tree[i].sum;
}

void eor(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        eorlazy(i);
        return ;
    }
    else{
        int mid=(l+r)/2;
        changedown(i);
        eordown(i);
        if(jobl<=mid){
            eor(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            eor(jobl,jobr,mid+1,r,i<<1|1);
        }
        tree[i].sum=tree[i<<1].sum+tree[i<<1|1].sum;
    }
}

//������ֵ��1��λ����ӵ�vec
void compute(int l,int r,int i){
    changedown(i);
    eordown(i);
    int mid=(l+r)/2;
    if(tree[i<<1].len==tree[i<<1].sum){
        for(int j=l;j<=mid;j++){
            vec.push_back(j);
        }
    }
    else if(tree[i<<1].sum!=0){
        compute(l,mid,i<<1);
    }
    if(tree[i<<1|1].len==tree[i<<1|1].sum){
        for(int j=mid+1;j<=r;j++){
            vec.push_back(j);
        }
    }
    else if(tree[i<<1|1].sum!=0){
        compute(mid+1,r,i<<1|1);
    }
}

int main()
{
    build(1,MAXN,1);
    char op,l,r,c;
    int u,v;
    while(cin>>op>>l>>u>>c>>v>>r){
        if(l=='(')  u=2*u+2;
        else    u=2*u+1;
        if(r==')')  v=2*v;
        else    v=2*v+1;
        if(op=='U'){
            update(u,v,1,1,MAXN,1);
        }
        else if(op=='I'){
            if(u>1){
                //��ֹԽ�� �����������һ������  ��Ϊ�Ͻ粻�ᳬԽ
                update(1,u-1,0,1,MAXN,1);
            }
            update(v+1,MAXN,0,1,MAXN,1);
        }
        else if(op=='D'){
            update(u,v,0,1,MAXN,1);
        }
        else if(op=='C'){
            if(u>1){
                //��ֹԽ�� �����������һ������  ��Ϊ�Ͻ粻�ᳬԽ
                update(1,u-1,0,1,MAXN,1);
            }
            update(v+1,MAXN,0,1,MAXN,1);
            eor(u,v,1,MAXN,1);
        }
        else{
            eor(u,v,1,MAXN,1);
        }
    }

    //�����
    if(tree[1].sum==0){
        //˵����ȫ�ռ���
        cout<<"empty set"<<endl;
        return 0;
    }

    vec.push_back(-1);//����һ��Ԫ��  �����ʱ���Բ����жϱ߽�
    compute(1,MAXN,1);
    
    int n=vec.size();
    sort(vec.begin(),vec.end());//������λ������  ���������
    for(int i=1;i<n;i++){
        if(vec[i]!=vec[i-1]+1){
            //��ǰ��Ĳ��Ǽ�һ  һ����һ������Ŀ�ͷ
            if(vec[i]%2==1){
                cout<<'['<<(vec[i]-1)/2<<',';
            }
            else{
                cout<<'('<<vec[i]/2-1<<',';
            }
        }
        if(vec[i]!=vec[i+1]-1){
            //�ͺ���Ĳ��Ǽ�һ  һ����һ������Ľ�β
            if(vec[i]%2==1){
                cout<<vec[i]/2<<"] ";
            }
            else{
                cout<<vec[i]/2<<") ";
            }
        }
    }

    return 0;
}