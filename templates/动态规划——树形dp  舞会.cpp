// û����˾�����
// ĳ��ѧ��n��ְԱ�����Ϊ1...n
// ����֮���д�����ϵ��Ҳ����˵���ǵĹ�ϵ����һ����У��Ϊ������
// ���������ӽ���ֱ����˾
// �����и���������ᣬ���ÿ������һ��ְԱ��������һ���Ŀ���ָ��
// �������ĳ��ְԱ��ֱ����˾���μ������
// ��ô���ְԱ���������Ҳ�������μ������
// ���������̼���������ЩְԱ����ʹ����ָ�����
// �������Ŀ���ָ����
// �������� : https://www.luogu.com.cn/problem/P1352
// ����ͽ���037����Ŀ7����
// ��ʽ���� : https://leetcode.cn/problems/house-robber-iii/
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6001;

int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
//��ʽǰ���ǽ�����
int nums[MAXN];
bool boss[MAXN];
int yes[MAXN];
// yes[i] : iΪͷ������������i��������£��������ܵõ���������ֵ
int no[MAXN];
// no[i] : iΪͷ������������i����������£��������ܵõ���������ֵ
int n,h;

void f(int u) {
    no[u] = 0;
    yes[u] = nums[u];
    for (int ei = head[u], v; ei > 0; ei = Next[ei]) {
        v = to[ei];
        f(v);//ͨ���������  ����ʵ��ÿһ�ζ����Ե����Լ��ӽڵ��yes��no
        no[u] += max(no[v], yes[v]);
        yes[u] += no[v];
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        boss[i]=true;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
        boss[u]=false;//Ϊ��Ѱ�������ϰ�
    }
    for (int i = 1; i <= n; i++) {
        if (boss[i]) {
            h = i;
            break;
        }
    }
    f(h);
    cout<<max(no[h],yes[h]);
    return 0;
}

