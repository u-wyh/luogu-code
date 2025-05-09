// ����ƻ�
// �����������m����ı��1~m�����е�Χ��һ����
// i�ŵ�һ��˳ʱ�뵽��i+1�ŵ㣬����m�ŵ�˳ָ��ص�1�ŵ�
// ����n���߶Σ�ÿ���߶�(a, b)����ʾ�߶δӵ�a˳ʱ�뵽��b
// �������ݱ�֤�����߶ο��԰�����������
// �������ݱ�֤ÿ���߶β�����ȫ����һ���߶ε��ڲ�
// Ҳ�����߶�֮��������غϵ�һ����������
// ����һ������Ϊn�Ľ������ans��ans[x]��ʾһ��ѡx���߶ε������
// ����ѡ�����߶��ܸ���������
// �������� : https://www.luogu.com.cn/problem/P4155
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int LIMIT = 18;

int power;
int stjump[MAXN << 1][LIMIT];
// stjump[i][p] : ��i���߶γ��������Ĵ�����2��p�η����ܵ���������߶εı��
int ans[MAXN];//��¼������
int n, m;
struct flag{
    int num,s,e;//��ʾ���  ��ʼ ����λ��
}line[MAXN];

int read(){
	int a=0,k=1;
	char c=getchar();
	while (!isdigit(c)){
        if (c=='-')k=-1;c=getchar();
    }
	while (isdigit(c)){
        a=a*10+c-'0';c=getchar();
    }
	return a*k;
}//�������

bool cmp(flag a,flag b){
    return a.s < b.s;
}//�ȽϺ���

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}
//���������n�����2���ݴη��Ƕ���  ������Ծ���������ᳬ��

void build() {
    for (int i = 1; i <= n; i++) {
        if (line[i].s > line[i].e) {
            //������߽�����ұ߽�ı� ����һ��
            line[i].e += m;
        }
    }//���Ƚ��߶α��һ��������ʽ
    sort(line+1 ,line+n+1,cmp);
    // for(int i=1;i<=n;i++)
    //    printf("%d %d %d\n",line[i][0],line[i][1],line[i][2]);
    for (int i = 1; i <= n; i++) {
        line[i + n].num = line[i].num;
        line[i + n].s = line[i].s + m;
        line[i + n].e = line[i].e + m;
    }
    //ʵ���߶εĿ�¡
    int e = n << 1;//�߶ε���Ŀ��Ϊԭ������

    for (int i = 1, arrive = 1; i <= e; i++) {
        //arrive  ��ʾѰ�ҵ���Ŀǰ���߶�����
        while (arrive + 1 <= e && line[arrive + 1].s <= line[i].e) {
            //�ж�������  �����߶�û��Խ�� ���������һ���߶�
            //���������߶ε���߽�С�ڵ���Ŀǰ�߶ε��ұ߽�
            arrive++;
        }
        stjump[i][0] = arrive;//��ʾ��Ծ2��0�η������Ե�����߶α��
    }//��¼ÿ���߶���һ�����Ե�ʲô�ط�

    for (int p = 1; p <= power; p++) {
        for (int i = 1; i <= e; i++) {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        }
    }//���st��
}

int jump(int i) {
    //��ʾ���������˵�i���߶�  Ҫͳ�����սʿ�Ĵ�
    int aim = line[i].s + m, cur = i, next, ans = 0;
    //aim�������߶�������Ŀ��
    for (int p = power; p >= 0; p--) {
        next = stjump[cur][p];//��ʾ��2��p�η����Ե���
        if (next != 0 && line[next].e < aim) {
            ans += 1 << p;
            cur = next;
        }
    }
    return ans + 1 + 1;
}

void compute() {
    power = log2(n);
    build();
    for (int i = 1; i <= n; i++) {
        //���
        //���һ��ʼ��˳����  1 2 3 4 5
        //���Ǿ���������ܱ�Ϊ5 3 1 4 2
        //��ô����һ��ʼ�ͼ�¼�˱��   ����Ӧ�Ĵ����Ӧ�����
        ans[line[i].num] = jump(i);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        line[i].num=i;
        line[i].s=read();
        line[i].e=read();
    }
    compute();
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
    return 0;
}
