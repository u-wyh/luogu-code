#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int head = 0;
int cnt = 0;
int key[MAXN];
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
int sum[MAXN];
int arr[MAXN];

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
    sum[i]=sum[ls[i]]+sum[rs[i]]+key[i];
}

int lr(int i) {
    return rs[fa[i]] == i ? 1 : 0;
}

void rotate(int i) {
    int f = fa[i], g = fa[f], soni = lr(i), sonf = lr(f);
    if (soni == 1) {
        rs[f] = ls[i];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[i] = f;
    } else {
        ls[f] = rs[i];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[i] = f;
    }
    if (g != 0) {
        if (sonf == 1) {
            rs[g] = i;
        } else {
            ls[g] = i;
        }
    }
    fa[f] = i;
    fa[i] = g;
    up(f);
    up(i);
}

//�������ı�������ȷ��  ֻ��ʹ������ƽ��  �������Ƕ�ÿ����ѯ�����������splay
void splay(int i, int goal) {
    int f = fa[i], g = fa[f];
    while (f != goal) {
        if (g != goal) {
            if (lr(i) == lr(f)) {
                rotate(f);
            } else {
                rotate(i);
            }
        }
        rotate(i);
        f = fa[i];
        g = fa[f];
    }
    if (goal == 0) {
        head = i;
    }
}

// ���������ҵ���������Ϊrank�Ľڵ㣬���ؽڵ���
// �������������ĿҪ��Ĳ�ѯ��������Ϊ�ڲ�����ʹ��
// Ϊʲô�÷������������������
// ��Ϊremove����ʹ�ø÷���ʱ��Ҫ��find���������
int find(int rank) {
    int i = head;
    while (i != 0) {
        if (size[ls[i]] + 1 == rank) {
            return i;
        } else if (size[ls[i]] >= rank) {
            i = ls[i];
        } else {
            rank -= size[ls[i]] + 1;
            i = rs[i];
        }
    }
    return 0;
}

void add(int num) {
    key[++cnt] = num;
    size[cnt] = 1;//�����ڵ�
    sum[cnt]=0;
    if (head == 0) {
        head = cnt;
    } else {
        int f = 0, i = head, son = 0;
        while (i != 0) {
            f = i;
            if (key[i] <= num) {
                son = 1;
                i = rs[i];
            } else {
                son = 0;
                i = ls[i];
            }
        }
        if (son == 1) {
            rs[f] = cnt;
        } else {
            ls[f] = cnt;
        }
        fa[cnt] = f;//����������Ϣ
        splay(cnt, 0);
    }
}

int getRank(int num) {
    int i = head, last = head;
    int ans = 0;
    while (i != 0) {
        last = i;
        if (key[i] >= num) {
            i = ls[i];
        } else {
            ans += size[ls[i]] + 1;
            i = rs[i];
        }
    }
    splay(last, 0);
    return ans + 1;
}

int index(int x) {
    int i = find(x);
    splay(i, 0);
    return key[i];
}

int pre(int num) {
    int i = head, last = head;
    int ans = INT_MIN;
    while (i != 0) {
        last = i;
        if (key[i] >= num) {
            i = ls[i];
        } else {
            ans = max(ans, key[i]);
            i = rs[i];
        }
    }
    splay(last, 0);
    return ans;
}

int post(int num) {
    int i = head, last = head;
    int ans = INT_MAX;
    while (i != 0) {
        last = i;
        if (key[i] <= num) {
            i = rs[i];
        } else {
            ans = min(ans, key[i]);
            i = ls[i];
        }
    }
    splay(last, 0);
    return ans;
}

void remove(int num) {
    int kth = getRank(num);
    if (kth != getRank(num + 1)) {
        //��ʾ�ýڵ����
        int i = find(kth);
        splay(i, 0);//���ֲ����е����������Ϊ�˷�ֹ���ݱ��һ������  ���ײ�ѯ
        if (ls[i] == 0) {
            head = rs[i];
        } else if (rs[i] == 0) {
            head = ls[i];
        } else {
            //���������  �����Ҷ���
            int j = find(kth + 1);
            splay(j, i);//��j�ᵽi������
            ls[j] = ls[i];
            fa[ls[j]] = j;
            up(j);
            head = j;
        }
        if (head != 0) {
            fa[head] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    if(k==1){
        cout<<0;
        return 0;
    }
    for(int i=1;i<k;i++){
        add(arr[i]);
    }
    int ans=INT_MAX;
    if(k%2){
//        int u=find((k+1)/2);
//        int v=find((k+1)/2-1);
//        int num=index(u);
//        splay(v,0);
//        int sum1=sum[v];
//        splay(u,v);
//        int sum2=sum[u];
//        int temp=(sum2-num-k/2*num)+(k/2*num-sum1+sum2);
//        ans=min(temp,ans);
        for(int i=k;i<=n;i++){
            int u=find((k+1)/2);
            int v=find((k+1)/2-1);
            int num=index(u);
            splay(v,0);
            int sum1=sum[v];
            splay(u,v);
            int sum2=sum[u];
            int temp=(sum2-num-k/2*num)+(k/2*num-sum1+sum2);
            ans=min(temp,ans);
            remove(arr[i-k]);
            add(arr[i]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
