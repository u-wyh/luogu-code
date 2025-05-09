// ������û�г��ֵ���С��Ȼ����java��
// ����һ������Ϊn������arr���±�1~n��һ����m����ѯ
// ÿ����ѯ l r : ��ӡarr[l..r]��û�г��ֹ�����С��Ȼ����ע��0����Ȼ��
// ���������㷨��������⣬��Ϊ�������ǿ�����ߵ�Ҫ���������㷨ʧЧ
// 1 <= n��m <= 2 * 10^5
// 0 <= arr[i] <= 2 * 10^5
// �������� : https://www.luogu.com.cn/problem/P4137
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXT = MAXN * 22;

int n, m;
int arr[MAXN];
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// ���ַ�Χ�У�ÿ�����ֳ��ֵ�����λ���У������λ������
int lateLeft[MAXT];
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
    lateLeft[rt] = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

// ���ַ�Χl~r����Ϣ��i�Žڵ�
// ���ַ�Χ�ϣ�jobi������֣�������ֵ�λ�ø���Ϊjobv
// �����µ�ͷ�ڵ���
int update(int jobi, int jobv, int l, int r, int i) {
	int rt = ++cnt;
	ls[rt] = ls[i];
	rs[rt] = rs[i];
	lateLeft[rt] = lateLeft[i];
	if (l == r) {
		lateLeft[rt] = jobv;
	} else {
		int mid = (l + r) / 2;
		if (jobi <= mid) {
			ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
		} else {
			rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
		}
		lateLeft[rt] = min(lateLeft[ls[rt]], lateLeft[rs[rt]]);
	}
	return rt;
}

// ������l~r��Χ�ϣ�û�г��ֵ���С��Ȼ���������ص�ͼ��
int query(int pos, int l, int r, int i) {
	if (l == r) {
		return l;
	}
	int mid = (l + r) / 2;
	if (lateLeft[ls[i]] < pos) {
		// l...mid��Χ�ϣ�ÿ������������ֵ�λ����
		// �����λ�������pos����˵��l...mid��Χ�ϣ�һ����ȱʧ������
		return query(pos, l, mid, ls[i]);
	} else {
		// ȱʧ������һ����mid+1....r��Χ
		// ��Ϊl...rһ����ȱʧ�����ֲŻ����������Χ��
		// �����಻ȱʧ����ȱʧ������һ�����Ҳ෶Χ��
		return query(pos, mid + 1, r, rs[i]);
	}
}

void prepare() {
    cnt = 0;
    root[0] = build(0, n);
    for (int i = 1; i <= n; i++) {
        if (arr[i] > n || arr[i] < 0) {
            root[i] = root[i - 1];
        } else {
            root[i] = update(arr[i], i, 0, n, root[i - 1]);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    prepare();
    for(int i=1,l,r;i<=m;i++){
        l=read(),r=read();
        cout<<query(l,0,n,root[r])<<endl;
    }
    return 0;
}
