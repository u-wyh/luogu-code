//P8112
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;

// b��bÿһ����׺���������ǰ׺���ȣ�z����
// b��aÿһ����׺���������ǰ׺���ȣ�e����
int z[MAXN];
int e[MAXN];
char a[MAXN];
char b[MAXN];
int n,m;

int q[MAXN];
int f[MAXN];
//�Ӻ���ǰ  ����Ҫ�����β��ܵ������  ����Խ����һ��ԽС  ������Ϊ���Ǳ��Դ�û�й��׵Ĳ���ȫ��ȥ����

void zArray(char* s, int n) {
    z[0] = n;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

void eArray(char* a, char* b, int n, int m) {
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && len < m && a[i + len] == b[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}
//���˵�в����Ļ�ֱ�Ӿ���ģ��

int main()
{
    cin>>m>>n;
    scanf("%s",b);
    scanf("%s",a);
    zArray(b,m);
    eArray(a,b,n,m);
    for(int i=0;i<=n;i++){
        f[i]=1e9;
    }
    for(int i=0,r=-1;i<n;i++){
        r>i+e[i]?e[i]=0:r=i+e[i];
        //�������˼�� ���ǰ����Ѿ�����ת�Ƶ��ĺ��沢�ҵ�ǰ��ȴ�޷�ת�Ƶ���֮��
        //˵�������Դ�û���κΰ���  ��ô����Ϊ0
        //�����Щ��û��ȥ���Ļ�  ��ô���ȶ��н���ʱҪ�в���  �ж�
    }
    //��ô��ʱ���еĵ� ֻҪe[i]Ϊ0  �Դ�һ��û��Ӱ��
    f[n]=0;
    int l=1,r=1;
    q[r++]=n;
    for(int i=(n-1);i>=0;i--){
        if(!e[i]){
            continue;
        }
        while(l<r&&q[l]>i+e[i]){
            //�����˽��޷�Χ
            l++;
        }
        f[i]=f[q[l]]+1;
        q[r++]=i;
    }
    if(f[0]<=1e9){
        cout<<f[0]<<endl;
    }
    else{
        cout<<"Fake"<<endl;
    }
    return 0;
}
