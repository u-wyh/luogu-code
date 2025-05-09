// ������ɾ���ߵ���С����
// ����һ��������ͨ���������б�Ŵ�0��n-1��n���ڵ㣬�Լ�n-1����
// ����һ���±��0��ʼ����������nums����Ϊn������nums[i]��ʾ��i���ڵ��ֵ
// �����һ����ά��������edges����Ϊn-1
// ���� edges[i] = [ai, bi] ��ʾ���д���һ��λ�ڽڵ� ai �� bi ֮��ı�
// ɾ������������ͬ�ı����γ�������ͨ���������һ��ɾ���߷������������²����Լ����������
// �ֱ��ȡ�������ÿ����������нڵ�ֵ�����ֵ
// ��� ���ֵ�� ��С ���ֵ�� ��ֵ ��������ɾ���߷����ķ���
// ���ؿ��ܵ���С����
// �������� : https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;

// �±�Ϊԭʼ�ڵ���
int dfn[MAXN];
// �±�Ϊdfn���
int eor[MAXN];
// �±�Ϊdfn���
int sz[MAXN];
int dfnCnt=0;
int edges[MAXN][2];
vector<vector<int>>graph;
int nums[MAXN];
int n;

void f(int u) {
    int i = ++dfnCnt;
    dfn[u] = i;
    eor[i] = nums[u];
    sz[i] = 1;
    for (int j=0;j<graph[u].size();j++) {
        int v=graph[u][j];
        if (dfn[v] == 0) {
            //��ʾ���������ǰû�з��ʹ���  ����Ҫ׼��һ�����ڵ�
            f(v);
            eor[i] ^= eor[dfn[v]];
            sz[i] += sz[dfn[v]];
        }
    }
}
//����dfn  sz  deep ����

int main()
{
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    graph.resize(n+1);
    for(int i=1;i<n;i++){
        cin>>edges[i][0]>>edges[i][1];
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    //����˫��ͼ
    //ע����������ʹ�õĶ��Ǵ��±�1��ʼ  û���±�0

    f(1);//���ǵ�һ����ֱ��ǿ�ƶ���Ϊ1
    int ans = INT_MAX;
    for (int i = 1, a, b, pre, pos, sum1, sum2, sum3; i < n-1; i++) {
        a = max(dfn[edges[i][0]], dfn[edges[i][1]]);//��һ���ߵĶ˵�dfn���ֵ
        for (int j = i + 1; j < n; j++) {
            //ö��ÿ������
            b = max(dfn[edges[j][0]], dfn[edges[j][1]]);//�ڶ����ߵĶ˵�dfn���ֵ
            if (a < b) {
                pre = a;
                pos = b;
            } else {
                pre = b;
                pos = a;
            }
            //����С���Ǹ�����Ϊpre
            sum1 = eor[pos];
            // xor[1] : ������������
            // ��Ϊͷ�ڵ���0��һ��ӵ����С��dfn���1
            // f�������õ�ʱ��Ҳ�Ǵ�0�ڵ㿪ʼ��
            if (pos < pre + sz[pre]) {
                //������������ǰ�����ϵ
                sum2 = eor[pre] ^ eor[pos];
                sum3 = eor[1] ^ eor[pre];
            } else {
                sum2 = eor[pre];
                sum3 = eor[1] ^ sum1 ^ sum2;
            }
            ans = min(ans, max(max(sum1, sum2), sum3) - min(min(sum1, sum2), sum3));
        }
    }
    cout<<ans;
    return 0;
}
