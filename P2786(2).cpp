#include<iostream>
#include<map>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long ll;
ll n,p;
map<string,ll>a;
ll ans;
int main()
{
    scanf("%lld%lld",&n,&p);
    for(int i=1;i<=n;i++)
    {
        string word;
        ll value;
        cin>>word>>value;
        a[word]=value;
        //word���߼��ʻ㣬value���京����
    }
    string t="";
    char c;
    //t�洢�ʻ�
    //c�������������ʱ����
    while(scanf("%c",&c)!=EOF)
    {
        if(!(isdigit(c)||isalpha(c)))
        {
            //�������֣�Ҳ������ĸ���Ǿ��Ƿָ������߿ո�س�֮���
            ans=((ans%p)+(a[t]%p))%p;
            //��ô�͸��´𰸣�����һ���ʵĺ���������
            //�����һ���ʲ��Ǹ߼��ʻ㣬��ô��map���Ӧ�ĺ���������0
            //�൱��û�б仯
            //Ϊ�˴𰸲��������ʱȡģ
            t="";
            //��ԭ���Ա��¼��һ����
        }
        else t+=c;
    }
    printf("%lld\n",ans);
    return 0;
}
