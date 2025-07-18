#include <bits/stdc++.h>
#define int long long
using namespace std;

const double ALPHA = 0.7;
const int MAXN = 100001;
int head = 0;
int cnt = 0;//这个用于新加节点编号
int key[MAXN];
int key_count[MAXN];//用于统计该节点的出现次数
int ls[MAXN];//记录左孩子的编号
int rs[MAXN];//记录右孩子的编号
int size[MAXN];//记录以该节点为头的树节点总数大小
int diff[MAXN];//记录以该节点为头的树上不同的数字种类个数
int collect[MAXN];//用于中序遍历
int ci;
int top;// 最上方的不平衡节点
int father;// top的父节点  统计这个父亲节点是因为会重建树
int side;// top是父节点的什么孩子，1代表左孩子，2代表右孩子

//新增一个节点  初始化该节点信息  返回该结点编号
int init(int num) {
    key[++cnt] = num;
    ls[cnt] = rs[cnt] = 0;
    key_count[cnt] = size[cnt] = diff[cnt] = 1;
    return cnt;
}

//将左右孩子的节点向上汇总
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
    diff[i] = diff[ls[i]] + diff[rs[i]] + (key_count[i] > 0 ? 1 : 0);
}

//记录中序遍历的编号
void inorder(int i) {
    //中序遍历：先左  后中  最后右
    if (i != 0) {
        inorder(ls[i]);
        if (key_count[i] > 0) {
            //只要当前节点出现次数不止一个
            //因为我们再删除操作的时候  这个节点次数变为0后  在重构树的时候才会删掉
            collect[++ci] = i;
        }
        inorder(rs[i]);
    }
}

//建立树  表示将中序遍历得到的数组里面的编号全部建立成一棵合法平衡的树
//头结点一定是collect数组中一半位置的节点
//返回当前建立的数的头结点
int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    int m = (l + r) / 2;
    int h = collect[m];
    ls[h] = build(l, m - 1);
    rs[h] = build(m + 1, r);
    up(h);
    return h;
}

//重建树
//每次增加或者删除操作后  树可能是不平衡的
//那么每次都必须要从最低节点向上检查
void rebuild() {
    if (top != 0) {
        //找到了最上面的点
        ci = 0;
        inorder(top);
        //中序遍历 只要ci=0  说明合法
        if (ci > 0) {
            if (father == 0) {
                head = build(1, ci);
            } else if (side == 1) {
                ls[father] = build(1, ci);
            } else {
                rs[father] = build(1, ci);
            }
        }
    }
}

//判断一颗树是否平衡  我们判断平不平衡是根据结点个数  不是节点词频总数
bool balance(int i) {
    return ALPHA * diff[i] >= max(diff[ls[i]], diff[rs[i]]);
}

//表示要加入一个数字num  已经来到了节点i
//这个节点i是从f节点转移来的  也就是父节点转移来的
//s表示是从父节点的左右边转移来的
void add(int i, int f, int s, int num) {
    if (i == 0) {
        //表示这个num 以前不存在
        if (f == 0) {
            //如果这个点是第一个点 那么相当于建立头节点
            head = init(num);
        } else if (s == 1) {
            //否则就是来自于父亲节点左右边  并填上父亲节点的孩子信息
            ls[f] = init(num);
        } else {
            rs[f] = init(num);
        }
    } else {
        //说明这个数字以前出现过
        if (key[i] == num) {
            key_count[i]++;
        } else if (key[i] > num) {
            add(ls[i], i, 1, num);
        } else {
            add(rs[i], i, 2, num);
        }
        up(i);
        //统计当前头结点信息
        if (!balance(i)) {
            top = i;
            father = f;
            side = s;
        }
    }
}

//加入一个数字num
void add(int num) {
    top = father = side = 0;//首先设置好这些值
    add(head, 0, 0, num);
    rebuild();
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return size[ls[i]] + key_count[i] + small(rs[i], num);
    }
}

int getRank(int num) {
    return small(head, num) + 1;
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - size[ls[i]] - key_count[i]);
    }
    return key[i];
}

int index(int x) {
    return index(head, x);
}

int pre(int num) {
    if(getRank(num) != getRank(num + 1)){
        return num;
    }
    int kth = getRank(num);
    if (kth == 1) {
        return INT_MIN;
    } else {
        return index(kth - 1);
    }
}

int post(int num) {
    int kth = getRank(num + 1);
    if (kth == size[head] + 1) {
        return INT_MAX;
    } else {
        return index(kth);
    }
}

void remove(int i, int f, int s, int num) {
    if (key[i] == num) {
        key_count[i]--;
    } else if (key[i] > num) {
        remove(ls[i], i, 1, num);
    } else {
        remove(rs[i], i, 2, num);
    }
    up(i);
    if (!balance(i)) {
        top = i;
        father = f;
        side = s;
    }
}

void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        top = father = side = 0;
        remove(head, 0, 0, num);
        rebuild();
    }
}

void clear() {
    memset(key, 0, sizeof(key));
    memset(key_count, 0, sizeof(key_count));
    memset(ls, 0, sizeof(ls));
    memset(rs, 0, sizeof(rs));
    memset(size, 0, sizeof(size));
    memset(diff, 0, sizeof(diff));
    cnt = 0;
    head = 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int ans;
    cin>>ans;
    add(ans);
    for (int i = 2,x; i <= n; i++) {
        cin>>x;
        int k1=pre(x),k2=post(x);
        add(x);
        ans+=min(abs(x-k1),abs(x-k2));
        //cout<<k1<<' '<<k2<<' '<<i<<' '<<ans<<endl;
    }
    cout<<ans<<endl;
    return 0;
}

