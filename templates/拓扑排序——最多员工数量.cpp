// �μӻ�������Ա����
// һ����˾׼����֯һ�����飬������������ n λԱ��
// ��˾׼����һ�� Բ�� �����ӣ��������� ������Ŀ ��Ա��
// Ա�����Ϊ 0 �� n - 1 ��ÿλԱ������һλ ϲ�� ��Ա��
// ÿλԱ�� ���ҽ��� ����������ϲ��Ա�����Աߣ����Ż�μӻ���
// ÿλԱ��ϲ����Ա�� ���� �����Լ�������һ���±�� 0 ��ʼ���������� favorite
// ���� favorite[i] ��ʾ�� i λԱ��ϲ����Ա�������㷵�زμӻ���� ���Ա����Ŀ
// �������� : https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000;

int n;
int indegree[MAXN];
int favorite[MAXN];
int deep[MAXN];
queue<int >q;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>favorite[i];
        indegree[favorite[i]]++;
    }
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        int Next=favorite[cur];
        deep[Next]=max(deep[Next],deep[cur]+1);
        if(--indegree[Next]==0){
            q.push(indegree[Next]);
        }
    }

    // ������1 : ����С��(���ĸ��� == 2)���������ĵ� + ����㣬�ܸ���
    int sumOfSmallRings = 0;
    // ������2 : ���д�(���ĸ��� > 2)��ֻ�����ĵ㣬��󻷵����ĵ����
    int bigRings = 0;
    for (int i = 0; i < n; i++) {
        // ֻ���ĵĻ���
        if (indegree[i] > 0) {
            int ringSize = 1;
            indegree[i] = 0;
            for (int j = favorite[i]; j != i; j = favorite[j]) {
                ringSize++;
                indegree[j] = 0;
            }
            if (ringSize == 2) {
                sumOfSmallRings += 2 + deep[i] + deep[favorite[i]];
            } else {
                bigRings = max(bigRings, ringSize);
            }
        }
    }
    cout<<max(sumOfSmallRings, bigRings);
    return 0;
}
