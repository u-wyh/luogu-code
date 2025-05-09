#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int BASE = 499;

char s1[MAXN];
char s2[MAXN];
int Next[MAXN];
long long p[MAXN];
long long h[MAXN];//��һ���ַ����Ĺ�ϣ����
long long val;
int n,m;

//��ϣ��Ԥ����
void build(const char* str) {
    p[0] = 1;
    for (int j = 1; j < n; ++j) {
        p[j] = p[j - 1] * BASE;
    }
    h[0] = str[0] - ' ' + 1;
    for (int j = 1; j < n; ++j) {
        h[j] = h[j - 1] * BASE + str[j] - ' ' + 1;
    }
}

//�����Ǽ���s2�Ĺ�ϣֵ
inline long long hashString(const char* str) {
    long long ans = str[0] - ' ' + 1;
    for (int j = 1; j < m; ++j) {
        ans = ans * BASE + str[j] - ' ' + 1;
    }
    return ans;
}

// ��Χ��s1[l,r]������ұ�
inline long long getHash(int l, int r) {
    long long ans = h[r];
    if (l > 0) {
        ans -= h[l - 1] * p[r - l + 1];
    }
    return ans;
}

// ����next����
void nextArray(const char *s, int m) {
    if (m == 1) {
        Next[0] = -1;
        return ;
    }
    Next[0] = -1;
    Next[1] = 0;
    int i = 2, cn = 0;
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            Next[i] = ++cn;
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i] = 0;
        }
        if(s[Next[i]]==s[i]){
            Next[i]=Next[Next[i]];
        }
        i++;
    }
}

// KMP�㷨�ĺ��ĺ���
int kmp(const char *s1, const char *s2) {
    int x = 0, y = 0;
    nextArray(s2, m);
//    for(int i=0;i<m;i++){
//        cout<<Next[i]<<' ';
//    }
//    cout<<endl;
    // s1�е�ǰ�ȶԵ�λ����x
    // s2�е�ǰ�ȶԵ�λ����y
    while (x < n && y < m) {
        if (s1[x] == s2[y]) {
            x++;
            y++;
        } else if (y == 0) {
            x++;
            //��ʾs2�Ѿ��ڵ�һ��λ����
        } else {
            y = Next[y];
            //��ʾs2��ǰ��
        }
    }

    return y == m ? x - y : -1;
}

int main()
{
    cin>>s1>>s2;
    n=strlen(s1);
    m=strlen(s2);//�����ַ����ĳ���
    auto start = std::chrono::high_resolution_clock::now();
    int result = kmp(s1, s2);
    if (result != -1) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found\n");
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start; // ʹ��΢����Ϊ��λ
    // �������ʱ��
    std::cout << "kmp����ʱ��: " << duration.count() << " ΢��" << std::endl;

    auto start1 = std::chrono::high_resolution_clock::now();
    val=hashString(s2);
    build(s1);
    result=-1;
    for(int i=0;i<=n-m;i++){
        if(val==getHash(i,i+m-1)){
            result=i;
            break;
        }
    }
    if (result != -1) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found\n");
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration1 = end1 - start1;
    // �������ʱ��
    std::cout << "��ϣ����ʱ��: " << duration1.count() << " ΢��" << std::endl;
    return 0;
}
/*
aabaacdbcabbabcd
babc

abcdcbcdcdaddva
cdcd
*/
