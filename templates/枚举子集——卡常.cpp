//P2396
#include <cstdio>
    #include <cmath>
    #include <cstring>
    #include <algorithm>
    #include <ctime>
    #include <cstdlib>
    using namespace std;
    typedef long long ll;
    #define enter putchar('\n')
    #define space putchar(' ')
    template <class T>
    void read(T &x){
        char c;
        bool op = 0;
        while(c = getchar(), c > '9' || c < '0')
        if(c == '-') op = 1;
        x = c - '0';
        while(c = getchar(), c >= '0' && c <= '9')
        x = x * 10 + c - '0';
        if(op) x = -x;
    }
    template <class T>
    void write(T x){
        if(x < 0) putchar('-'), x = -x;
        if(x >= 10) write(x / 10);
        putchar('0' + x % 10);
    }
    const int N = 24, P = 1e9 + 7;
    int n, m, b[2], f[1 << N], dis[1 << N];
    // b: �������֣�f: dp���飻dis��ĳ״̬ʱyyy���߹��ľ���
    int main(){
        read(n);
        for(int i = 0; i < n; i++)
            read(dis[1 << i]);
        read(m);
        if(m > 0) read(b[0]);
        if(m > 1) read(b[1]);
        f[0] = 1;
        for(int i = 1; i < (1 << n); i++){
            int j = i & -i, k = i;
            // k��һ������������������ͣ��lowbit���ҳ�i�е�����"1"
            dis[i] = dis[i ^ j] + dis[j]; //��iȥ��һ��"1"�õ���״̬����dis[i]
            if(dis[i] == b[0] || dis[i] == b[1]) continue; //����Ƕ�������
            while(k){
                j = k & -k; //j�ǵ�ǰ�ҵ���lowbit
                f[i] += f[i ^ j];
                if(f[i] >= P) f[i] -= P; //������
                k ^= j; //k��ȥ�����"1"�������´�lowbit���ҵ���һ��"1"
            }
        }
        write(f[(1 << n) - 1]), enter;
        return 0;
    }
