// HH������
// һ����n��λ�ã�ÿ��λ����ɫ������iλ�õ���ɫ��arr[i]
// һ����m����ѯ��question[i] = {li, ri}
// ��ʾ��i����ѯ���arr[li..ri]��Χ��һ���ж����ֲ�ͬ��ɫ
// ����ÿ����ѯ�Ĵ�
// 1 <= n��m��arr[i] <= 10^6
// 1 <= li <= ri <= n
// �������� : https://www.luogu.com.cn/problem/P1972
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
// �����߼��Ϳ��Ͻ�����ȫһ�£�������д�˶�д�����࣬������ioЧ��
//�����������������״���� 
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000010;

int arr[MAXN];
//ԭ��������
struct Query{
    int l,r,subsrcipt;
}query[MAXN];
//��ѯ��������  �Լ���Ӧ��ѯ�±�
int ans[MAXN];
//��ʾ��Ӧ�Ĳ�ѯ�±��Ӧ�Ĵ���ʲô
int Map[MAXN];
//���һ����ɫ���ֵ�����λ����ʲô  �����0��ʾ��δ����
int tree[MAXN];
int n, m;

int lowbit(int i) {
    return i & -i;
}

//�������Ŀ��  v��ȡֵֻ��1��-1 ��ʾ�������λ���ϵ�ֵ���߸���һ��λ��ֵ
//��������� tree[i]�����1  ��ʾ���λ����Ŀǰĳһ����ɫ�����ҳ��ֵĵط�  0��ʾ��δ���ֻ��߲�������λ��
void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int range(int l, int r) {
	return sum(r) - sum(l - 1);
}

bool cmp(Query a,Query b){
    return a.r<b.r;
}

void compute() {
    sort(query+1,query+ m + 1,cmp);
    //����ѯ������ݲ�ѯ�ұ߽��������
    for (int s = 1, q = 1, l, r, i; q <= m; q++) {
        //�����ƺ���˫ָ��ķ��
        r = query[q].r;
        for (; s <= r; s++) {
            int color = arr[s];
            if (Map[color] != 0) {
                add(Map[color], -1);
            }
            //�����ǰ��ɫ�Ѿ����ֹ�  ��ô��Ҫ���临ԭΪ0  ��Ϊ�����������ҵ���
            add(s, 1);
            //����ǰλ�ñ��Ϊ1  ��ʾ��һ����ɫ���ֵ�����λ��
            Map[color] = s;
            //��¼������ɫ���ֵ�����λ��
        }
        //����˵��ٽ��r֮ǰ��ȫ�����¹���
        l = query[q].l;
        i = query[q].subsrcipt;
        ans[i] = range(l, r);
    }
    //ÿ����һ��  �������һ����ѯ����
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>query[i].l>>query[i].r;
        query[i].subsrcipt=i;
    }
    compute();
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
