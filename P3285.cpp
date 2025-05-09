#include <bits/stdc++.h>
using namespace std;
const int MAX = 330000;
map<int, int> f;
int n, m, cnt, ans, root;

int read(){
    int x = 0, f = 1; char ch = getchar();
    while (ch > '9' || ch  < '0') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch <= '9' && ch >= '0') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

struct Node{
    int fa, son[2], siz, l, r;
} T[MAX];

void pushup(int x){
    T[x].siz = T[T[x].son[0]].siz + T[T[x].son[1]].siz + T[x].r - T[x].l + 1;
}

void rotate(int x){
    int y = T[x].fa, z = T[y].fa;
    int op = T[y].son[1] == x;
    T[x].fa = z;
    if (z) T[z].son[T[z].son[1] == y] = x;
    T[y].son[op] = T[x].son[!op];
    T[T[y].son[op]].fa = y;
    T[y].fa = x;
    T[x].son[!op] = y;
    pushup(y);
}

void splay(int x, int to){
    while (T[x].fa != to)
    {
        int y = T[x].fa, z = T[y].fa;
        if (z != to)
        {
            if ((T[z].son[0] == y) ^ (T[y].son[0] == x)) rotate(x);
            else rotate(y);
        } rotate(x);
    }
    pushup(x); 
    if (to == 0) root = x;
}

int query(int x){
    splay(x, 0);
    return T[x].siz - T[T[x].son[1]].siz;
}

int getkth(int k){
    int x = root;
    while (k){
        int sum = T[T[x].son[0]].siz + T[x].r - T[x].l + 1;
        if (T[T[x].son[0]].siz < k && k <= sum){
            k -= T[T[x].son[0]].siz;
            break;
        }
        if (sum < k){
            k -= sum;
            x = T[x].son[1];
        }
        else x = T[x].son[0];
    }
    return T[x].l + k - 1;
}

void erase(int x){
    int pre = T[x].son[0], nxt = T[x].son[1];
    while (T[pre].son[1]) pre = T[pre].son[1];
    while (T[nxt].son[0]) nxt = T[nxt].son[0];
    if (!pre && !nxt) root = 0;
    else if (!pre){
        splay(nxt, root);
        root = nxt; T[root].fa = 0;
        T[x].son[0] = T[x].son[1] = 0;
        T[x].siz = 1;
    }
    else if (!nxt){
        splay(pre, root);
        root = pre; T[root].fa = 0;
        T[x].son[0] = T[x].son[1] = 0;
        T[x].siz = 1;
    }
    else{
        splay(pre, 0);
        splay(nxt, pre);
        T[nxt].son[0] = T[x].fa = 0;
        T[x].siz = 1;
        pushup(nxt); pushup(pre);
    }
}

void push_front(int x){
    if (!root) { root = x; return ; }
    int fa_ = root;
    while (T[fa_].son[0]) T[fa_].siz ++, fa_ = T[fa_].son[0];
    T[fa_].siz ++;
    T[fa_].son[0] = x;
    T[x].fa = fa_;
    splay(x, 0);
}

void push_back(int x){
    if (!root) { root = x; return ; }
    int fa_ = root;
    while (T[fa_].son[1]) T[fa_].siz ++, fa_ = T[fa_].son[1];
    T[fa_].siz ++;
    T[fa_].son[1] = x;
    T[x].fa = fa_;
    splay(x, 0);
}

void split(int x, int id){
    int L = T[x].l, R = T[x].r, ls, rs;
    if (L == R) return ;
    if (L == id){
        rs = ++cnt;
        f[R] = rs; f[id] = x;
        T[rs].son[1] = T[x].son[1];
        T[T[rs].son[1]].fa = rs;
        T[x].son[1] = rs; T[rs].fa = x;
        T[rs].l = L + 1; T[rs].r = R;
        T[x].r = L;
        pushup(rs); pushup(x);
    }
    else if (R == id){
        ls = ++cnt;
        f[R - 1] = ls; f[id] = x;
        T[ls].son[0] = T[x].son[0];
        T[T[ls].son[0]].fa = ls;
        T[x].son[0] = ls; T[ls].fa = x;
        T[ls].l = L; T[ls].r = R - 1;
        T[x].l = R;
        pushup(ls); pushup(x);
    }
    else{
        ls = ++cnt; rs = ++cnt;
        f[id] = x; f[id - 1] = ls; f[R] = rs;
        T[ls].son[0] = T[x].son[0]; T[rs].son[1] = T[x].son[1];
        T[T[ls].son[0]].fa = ls; T[T[rs].son[1]].fa = rs;
        T[x].son[0] = ls; T[x].son[1] = rs; T[ls].fa = T[rs].fa = x;
        T[x].l = T[x].r = id;
        T[ls].l = L; T[ls].r = id - 1;
        T[rs].l = id + 1; T[rs].r = R;
        pushup(ls); pushup(rs); pushup(x);
    }
    splay(x, 0);
}

void init(){
    root = cnt = 1;
    T[root].l = 1, T[root].r = n;
    T[root].siz = n;
    f[n] = 1;
}

int main()
{
    n = read(); m = read();
    init();
    while (m --){
        int opt = read();
        if (opt == 1){
            int oid = read() - ans, nid = read() - ans;
            int x = f.lower_bound(oid) -> second;
            split(x, oid);
            ans = query(x);
            T[x].l = T[x].r = nid; f[nid] = x;
            printf("%d\n", ans);
        }
        else if (opt == 2){
            int id = read() - ans;
            int x = f.lower_bound(id) -> second;
            split(x, id);
            ans = query(x);
            erase(x);
            push_front(x);
            printf("%d\n", ans);
        }
        else if (opt == 3){
            int id = read() - ans;
            int x = f.lower_bound(id) -> second;
            split(x, id);
            ans = query(x);
            erase(x);
            push_back(x);
            printf("%d\n", ans);
        }
        else if (opt == 4){
            int k = read() - ans;
            ans = getkth(k);
            printf("%d\n", ans);
        }
    }
    return 0;
}