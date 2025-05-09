#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int LIMIT = 21;

int power;
int ans;
int stjump[MAXN << 1][LIMIT];
int n, m;
struct flag{
    int num,s,e;//��ʾ���  ��ʼ ����λ��
}line[MAXN<<1];

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
    ans=INT_MAX;
    for (int i = 1; i <= n; i++) {
        ans=min(ans,jump(i));
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        line[i].num=i;
        line[i].s=read();
        line[i].e=read()+1;
        if(line[i].s==line[i].e%m){
            cout<<1<<endl;
            return 0;
        }
    }
    compute();
    if(ans==INT_MAX||ans>n){
        cout<<"impossible";
        return 0;
    }
    cout<<ans<<endl;
    return 0;
}
