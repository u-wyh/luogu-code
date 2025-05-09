// Bellman-Ford�㷨Ӧ�ã�����ģ�棩
// kվ��ת������˵ĺ���
// �� n ������ͨ��һЩ�������ӡ�����һ������ flights
// ���� flights[i] = [fromi, toi, pricei]
// ��ʾ�ú��඼�ӳ��� fromi ��ʼ���Լ۸� pricei �ִ� toi��
// ���ڸ������еĳ��кͺ��࣬�Լ��������� src ��Ŀ�ĵ� dst������������ҵ���һ����ྭ�� k վ��ת��·��
// ʹ�ô� src �� dst �� �۸������ �������ظü۸� ���������������·�ߣ������ -1��
// �������� : https://leetcode.cn/problems/cheapest-flights-within-k-stops/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 10001;

int n,m,k,st,en;
//һ����n��վ��  ��m��·������   ��������תk��
//��st��en
int cur[MAXN],Next[MAXN];
//Next��һ����������  ��������˵
int edge[MAXM][3];
//��Bellman�㷨��  ���ǲ���Ҫ�����ڽӾ��� �ڽӱ�ȵ�
//�����Ǹ���·�ߵ������������ֵ�

int main()
{
    cin>>n>>m>>k>>st>>en;
    for(int i=1;i<=n;i++){
        cur[i]=INT_MAX;
    }
    cur[st]=0;
    //cur�����¼����ÿ���㵽st�ľ���  ��ʼ��Ϊ������
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
    }
    for(int i=0;i<=k;i++){
        for(int j=1;j<=n;j++){
            Next[j]=cur[j];
        }
        //����Ҫ����Next����  ��Ϊ����һ�ֿ�����  ������һ���Ż���  ͬʱʵ����������  ��������������ͳ��k
        for(int j=1;j<=m;j++){
            if (cur[edge[j][0]] != INT_MAX) {
                //�������������  ˵�����Ե���edge[j][0]  ��ô���Լ��������Ż���һ��edge[j][1]
                Next[edge[j][1]] = min(Next[edge[j][1]], cur[edge[j][0]] + edge[j][2]);
                //��һ�ֵ���edge[j][1] �ľ�����ԭ����ֵ  ��  ����edge[j][0]��ֵ���ϴ�edge[j][0]��edge[j][1]
            }
        }
        //����޸�ֵ�Ļ�����cur������������
        for(int j=1;j<=n;j++){
            cur[j]=Next[j];
        }
        //��cur����ΪNext����
    }
    if(cur[en]==INT_MAX){
        cur[en]=-1;
    }
    cout<<cur[en];
    return 0;
}

