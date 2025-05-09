//https://acm.hdu.edu.cn/showproblem.php?pid=1506
#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

const int MAXN = 10000001;

int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int n;
int ans=0;
int size[MAXN];

//���û�б�С������  ��ô��������һֱ���ұ߽ڵ㽨��
//Ҳ�����нڵ��ջ�е���
void build() {
    ans=0;
    for(int i=1;i<=n;i++){
        size[i]=0;
        ls[i]=0;
        rs[i]=0;
    }
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            //����ջ  ���������ϵ�Ԫ��
            pos--;
        }
        if (pos > 0) {
            //��ô����û�е��ɾ�   ��ô��ǰ�ڵ�ͻ��Ϊջ���ڵ���Һ���
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            //��ʾ��Ԫ�ص��� ��ôһ���ǵ�ǰ�ڵ�����ӽڵ�
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;//����ջ��
        top = pos;
    }
}

void dfs(int u){
    size[u]=1;
    if(ls[u]!=0){
        dfs(ls[u]);
    }
    if(rs[u]!=0){
        dfs(rs[u]);
    }
    size[u]+=(size[ls[u]]+size[rs[u]]);
    //cout<<u<<' '<<size[u]<<endl;
    ans=max(ans,size[u]*arr[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    while(n!=0){
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        build();
        dfs(sta[1]);
        cout<<ans<<endl;
        cin>>n;
    }
    return 0;
}
