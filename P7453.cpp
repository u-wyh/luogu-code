#include <bits/stdc++.h>
#define mod 998244353
#define N 250005
using namespace std;
int n, a[N], b[N], c[N], m;
struct mat
{
    int a[4][4];
    mat(bool val = 1)
    {
        memset(a, 0, sizeof(a));
        if (val == 1)
            for (int i = 0; i < 4; i++)
                a[i][i] = 1;
    }
    mat operator*(const mat x) const
    {
        mat res = (0);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    res.a[i][j] += 1ll * a[i][k] * x.a[k][j] % mod, res.a[i][j] %= mod;
        return res;
    }
};

struct vec
{
    int v[4];
    vec() { memset(v, 0, sizeof(v)); }
    vec(int a, int b, int c) { v[0] = a, v[1] = b, v[2] = c, v[3] = 1; }
    vec operator+(const vec x) const
    {
        vec res;
        res.v[0] = (v[0] + x.v[0]) % mod;
        res.v[1] = (v[1] + x.v[1]) % mod;
        res.v[2] = (v[2] + x.v[2]) % mod;
        res.v[3] = v[3] + x.v[3];
        return res;
    }
    vec operator*(mat y)
    {
        vec res;
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                res.v[j] += (1ll * v[k] * y.a[k][j]) % mod, res.v[j] %= mod;
        return res;
    }
};
mat t1, t2, t3, t4, t5, t6;
void pre()
{
    t1.a[1][0] = t2.a[2][1] = t3.a[0][2] = 1;
    t6.a[2][2] = 0;
}

struct SegmentTree
{
#define root 1, 1, n
#define mid ((l + r) >> 1)
#define lpos pos << 1
#define rpos lpos | 1
#define lson lpos, l, mid
#define rson rpos, mid + 1, r
    vec tr[N << 2];
    mat tag[N << 2];
    void psu(int pos) { tr[pos] = tr[lpos] + tr[rpos]; }
    void bld(int pos, int l, int r)
    {
        if (l == r)
            return tr[pos] = vec(a[l], b[l], c[l]), void();
        bld(lson), bld(rson), psu(pos);
    }
    void ntg(int pos, mat t)
    {
        tag[pos] = tag[pos] * t;
        tr[pos] = tr[pos] * t;
    }
    void psd(int pos)
    {
        ntg(lpos, tag[pos]), ntg(rpos, tag[pos]), tag[pos] = mat();
    }
    void upd(int pos, int l, int r, int L, int R, mat t)
    {
        if (L <= l && r <= R)
            return ntg(pos, t), void();
        psd(pos);
        if (L <= mid)
            upd(lson, L, R, t);
        if (R > mid)
            upd(rson, L, R, t);
        psu(pos);
    }
    vec qry(int pos, int l, int r, int L, int R)
    {
        if (L <= l && r <= R)
            return tr[pos];
        psd(pos);
        if (R <= mid)
            return qry(lson, L, R);
        if (L > mid)
            return qry(rson, L, R);
        return qry(lson, L, R) + qry(rson, L, R);
    }
} T;
int main()
{
    pre();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    T.bld(root);
    scanf("%d", &m);
    while (m--)
    {
        int l, r, v, op;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1)
            T.upd(root, l, r, t1);
        else if (op == 2)
            T.upd(root, l, r, t2);
        else if (op == 3)
            T.upd(root, l, r, t3);
        else if (op == 7)
        {
            vec ans = T.qry(root, l, r);
            printf("%d %d %d\n", ans.v[0], ans.v[1], ans.v[2]);
        }
        else
        {
            scanf("%d", &v);
            if (op == 4)
                t4.a[3][0] = v, T.upd(root, l, r, t4);
            else if (op == 5)
                t5.a[1][1] = v, T.upd(root, l, r, t5);
            else if (op == 6)
                t6.a[3][2] = v, T.upd(root, l, r, t6);
        }
    }
    return 0;
}