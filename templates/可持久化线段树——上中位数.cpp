// ����������������λ����java��
// Ϊ�˷�����⣬�Ҹ�д�����⣬���Ǹ�д�������ԭʼ�����Ч
// ����һ������Ϊn������arr���±�1~n��һ����m����ѯ
// ÿ����ѯ a b c d : ��˵���[a,b]֮�䡢�Ҷ˵���[c,d]֮�䣬��֤a<b<c<d
//                   �ĸ���������������λ������ӡ��������λ��
// ��Ŀ��ǿ�����ߵ�Ҫ����һ�δ�ӡ�Ĵ�ΪlastAns����ʼʱlastAns = 0
// ÿ�θ����ĸ��������������·�ʽ�õ�a��b��c��d����ѯ��ɺ����lastAns
// (������ÿ������ + lastAns) % n + 1���õ��ĸ�ֵ����С�����Ӧa��b��c��d
// 1 <= n <= 20000
// 1 <= m <= 25000
// 1 <= arr[i] <= 10^9
// �������� : https://www.luogu.com.cn/problem/P2839
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20001;
const int MAXT = MAXN * 20;
const int INF = 10000001;

int n, m;

// ԭʼλ�á���ֵ
struct node{
    int pos,val;
}arr[MAXN];

// �ɳ־û��߶�����Ҫ
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// ���������ǰ׺�ͣ�ǰ׺����Ϊ��
int pre[MAXT];

// ����������׺�ͣ���׺����Ϊ��
int suf[MAXT];

// �������ۼӺ�
int sum[MAXT];
int cnt;

// ��ѯ�����⣬a��b��c��d
int ques[4];
// �ռ�������Ϣ��pre��suf��sum
int info[3];

bool cmp(node a,node b){
    return a.val<b.val;
}

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

int build(int l, int r) {
    int rt = ++cnt;
    pre[rt] = suf[rt] = sum[rt] = r - l + 1;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

void up(int i) {
    pre[i] = max(pre[ls[i]], sum[ls[i]] + pre[rs[i]]);
    suf[i] = max(suf[rs[i]], suf[ls[i]] + sum[rs[i]]);
    sum[i] = sum[ls[i]] + sum[rs[i]];
}

// jobiλ�ã�ԭ����1�����ڸ�Ϊ-1
int update(int jobi, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    pre[rt] = pre[i];
    suf[rt] = suf[i];
    sum[rt] = sum[i];
    if (l == r) {
        pre[rt] = suf[rt] = sum[rt] = -1;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = update(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = update(jobi, mid + 1, r, rs[rt]);
        }
        up(rt);
    }
    return rt;
}

void prepare() {
    sort(arr+1,arr+n+1,cmp);
    //���ﲻ��ȥ��
    //��Ϊ�����޸ıȽ�����
    cnt = 0;
    root[1] = build(1, n);
    for (int i = 2; i <= n; i++) {
        //ÿ�ν���һ��λ�ñ�Ϊ-1
        root[i] = update(arr[i - 1].pos, 1, n, root[i - 1]);
    }
}

void initInfo() {
    //�޸�ȫ�ֱ���
    info[0] = info[1] = -INF;
    info[2] = 0;
}

//���µ���Դ����
void mergeRight(int r) {
    info[0] = max(info[0], info[2] + pre[r]);
    info[1] = max(suf[r], info[1] + sum[r]);
    info[2] += sum[r];
}

void query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        mergeRight(i);
        //���������ܵ�����
    } else {
        int mid = (l + r) / 2;
        if (jobl <= mid) {
            query(jobl, jobr, l, mid, ls[i]);
        }
        if (jobr > mid) {
            query(jobl, jobr, mid + 1, r, rs[i]);
        }
    }
}

bool check(int a, int b, int c, int d, int v) {
    initInfo();
    query(a, b, 1, n, root[v]);
    int best = info[1];
    initInfo();
    query(c, d, 1, n, root[v]);
    best += info[0];
    if (b + 1 <= c - 1) {
        initInfo();
        query(b + 1, c - 1, 1, n, root[v]);
        best += info[2];
    }
    return best >= 0;
}

int compute(int a, int b, int c, int d) {
    int left = 1, right = n, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (check(a, b, c, d, mid)) {
            ans = arr[mid].val;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    n=read();
    for(int i=1;i<=n;i++){
        arr[i].pos=i;
        arr[i].val=read();
    }
    prepare();
    m=read();
    for (int i = 1, lastAns = 0; i <= m; i++) {
        for (int j = 0; j < 4; j++) {
            ques[j]=read();
            ques[j] = (ques[j] + lastAns) % n + 1;
        }
        sort(ques, ques + 4);
        lastAns = compute(ques[0], ques[1], ques[2], ques[3]);
        cout << lastAns << endl;
    }
    return 0;
}
