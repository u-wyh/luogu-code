// ��һ�γ���λ�õ����У�java��
// ����һ������Ϊn������arr���±�1~n��һ����m����ѯ��ÿ����ѯ��ʽ����
// l r : arr[l..r]��Χ�ϣ�ÿ������һ�γ��ֵ�λ�ã�����Щλ�����һ������
//       ����÷�Χ��s�ֲ�ͬ��������ô���г���Ϊs
//       ��ӡ�����е�s/2��λ��(����ȡ��)����Ӧarr��ʲôλ��
// ��Ŀ��ǿ�����ߵ�Ҫ����һ�δ�ӡ�Ĵ�ΪlastAns����ʼʱlastAns = 0
// ÿ�θ�����l��r���������·�ʽ�õ���ʵ��l��r����ѯ��ɺ����lastAns
// a = (����l + lastAns) % n + 1
// b = (����r + lastAns) % n + 1
// ��ʵl = min(a, b)
// ��ʵr = max(a, b)
// 1 <= n��m <= 2 * 10^5    0 <= arr[i] <= 2 * 10^5
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=5919
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200002;
const int MAXT = MAXN * 37;

int cases, n, m;
//ÿ�ζ����ԭʼ����
int arr[MAXN];

// pos[v] : v��������ϴγ��ֵ�λ��
int pos[MAXN];

// �ɳ־û��߶�����Ҫ
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// ���鷶Χ��ֻ��¼ÿ������һ�γ��ֵ�λ�ã�������λ���ж��ٸ�
//Ҳ���Խ���tree����
int firstSize[MAXT];

int cnt;

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
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    firstSize[rt] = 0;
    return rt;
}

// ���鷶Χl~r����Ϣ��i�Žڵ�
// ���jobv = -1����ζ��jobiλ�ü���һ������
// ���jobv = +1����ζ��jobiλ������һ������
// �����µ�ͷ�ڵ���
int update(int jobi, int jobv, int l, int r, int i) {
	int rt = ++cnt;
	ls[rt] = ls[i];
	rs[rt] = rs[i];
	firstSize[rt] = firstSize[i] + jobv;
	if (l == r) {
		return rt;
	}
	int mid = (l + r) / 2;
	if (jobi <= mid) {
		ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
	} else {
		rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
	}
	return rt;
}

// ���������������汾���߶���
void prepare() {
    cnt = 0;
    memset(pos,0,sizeof(pos));
    root[n + 1] = build(1, n);
    for (int i = n; i >= 1; i--) {
        if (pos[arr[i]] == 0) {
            root[i] = update(i, 1, 1, n, root[i + 1]);
        } else {
            root[i] = update(pos[arr[i]], -1, 1, n, root[i + 1]);
            root[i] = update(i, 1, 1, n, root[i]);
        }
        pos[arr[i]] = i;
    }
}

// ���鷶Χl~r����Ϣ��i�Žڵ�
// jobl ~ jobr��Χ�ϣ�һ���м��ֲ�ͬ�����֣�Ҳ���������Χ�ϣ��ж��ٸ�λ����1
int querySize(int jobl, int jobr, int l, int r, int i) {
	if (jobl <= l && r <= jobr) {
		return firstSize[i];
	}
	int mid = (l + r) / 2;
	int ans = 0;
	if (jobl <= mid) {
		ans += querySize(jobl, jobr, l, mid, ls[i]);
	}
	if (jobr > mid) {
		ans += querySize(jobl, jobr, mid + 1, r, rs[i]);
	}
	return ans;
}

// ���鷶Χl~r����Ϣ��i�Žڵ�
// ��ѯ�����Χ�ϣ���jobk��1����
int queryKth(int jobk, int l, int r, int i) {
	if (l == r) {
		return l;
	}
	int mid = (l + r) / 2;
	int lsize = firstSize[ls[i]];
	if (lsize >= jobk) {
		return queryKth(jobk, l, mid, ls[i]);
	} else {
		return queryKth(jobk - lsize, mid + 1, r, rs[i]);
	}
}

int main()
{
    cases=read();
    for(int t=1;t<=cases;t++){
        n=read(),m=read();
        for(int i=1;i<=n;i++){
            arr[i]=read();
        }
        prepare();
        cout<<"Case #"<<t<<": ";
        for(int i=1,a,b,l,r,lastans=0,k;i<=m;i++){
            l=read(),r=read();
            a=(l+lastans)%n+1;
            b=(r+lastans)%n+1;
            l=min(a,b),r=max(a,b);
            k=(querySize(l,r,1,n,root[l])+1)/2;
            lastans=queryKth(k,1,n,root[l]);
            cout<<lastans<<' ';
        }
        cout<<endl;
    }
    return 0;
}
