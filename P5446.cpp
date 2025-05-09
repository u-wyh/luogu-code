#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+55;

char ss[MAXN << 1];//��������м������#
char a[MAXN];//ԭʼ����
int p[MAXN << 1];//�뾶����
int n;
bool vis[MAXN<<1];
stack<int>st;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

void manacher() {
    manacherss();
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {//i�Ǵ�ʱ����������λ��
        len = r > i ? min(p[2 * c - i], r - i) : 1;//���ֵ�ǻ���ֵ  �����ס��  ��ô����ֵ��������ֵ  ��������ټ�
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //�������ס��  ��ôֱ����������
        }
        //��ʱ�Ѿ��������iΪ���ĵĻ��İ뾶��С
        if (i + len > r) {
            r = i + len;
            c = i;//c��ʾ��������r�����Ǹ���Ϊ���ĵ��ұ߽�
            //����������ұ߽�  ��ôc����i  r����i+len
        }
        p[i] = len-1;
        //�õ����İ뾶
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        scanf("%s",a);
        manacher();
        for(int i=0;i<=n;i++){
            vis[i]=false;
        }
        vis[n-2]=true;
        for(int i=n-2;i>=1;i-=2){
            if(i+p[i]-1==(n-2)){
                //st.push((i+1)/2);
                vis[i]=true;
            }
            else if(i==p[i]&&vis[i+p[i]-1]){
                //st.push((i+1)/2);
                vis[i]=true;
            }
        }
        for(int i=1;i<=n-2;i++){
            if(vis[i]){
                cout<<(i+1)/2<<' ';
            }
        }
        cout<<endl;
    }
    return 0;
}
