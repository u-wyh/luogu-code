// �����ַ���ͬ���·��
// ����һ�� ������һ����ͨ�������޻�ͼ�������ڵ��ǽڵ� 0
// ������ɱ�Ŵ� 0 �� n - 1 �� n ���ڵ����
// ���±�� 0 ��ʼ������Ϊ n ������ parent ����ʾ�����
// ���� parent[i] �ǽڵ� i �ĸ��ڵ�
// ���ڽڵ� 0 �Ǹ��ڵ㣬���� parent[0] == -1
// �����һ���ַ��� s ������Ҳ�� n ������ s[i] ��ʾ������ڵ� i ���ַ�
// �����ҳ�·��������һ�����ڽڵ㶼û�з��䵽��ͬ�ַ��� �·��
// �����ظ�·���ĳ���
// �������� : https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

struct Info {
    int maxPathFromHead; // һ��Ҫ��ͷ�ڵ����������£������ַ����ȵ��·������
    int maxPath; // �������ϣ������ַ����ȵ��·������

    Info(int a, int b) {
        maxPathFromHead = a;
        maxPath = b;
    }
};
int parent[MAXN];
char s[MAXN];
int n;
vector<vector<int>>graph;

Info f(int u) {
    if (graph[u].empty()) {
        // u�ڵ���Ҷ
        return Info(1, 1);//���û���ӽڵ�Ļ�  ��ô � �� Ϊ��� ��Ϊ1
    }
    int max1 = 0; // �·����
    int max2 = 0; // �·��γ���
    int maxPath = 1;
    for (int i=0;i<graph[u].size();i++) {
        int v=graph[u][i];//��һ���ӽڵ�
        Info nextInfo = f(v);//��ɵݹ�
        maxPath = max(maxPath, nextInfo.maxPath);
        if (s[u] != s[v]) {
            if (nextInfo.maxPathFromHead > max1) {
                max2 = max1;
                max1 = nextInfo.maxPathFromHead;
            } else if (nextInfo.maxPathFromHead > max2) {
                max2 = nextInfo.maxPathFromHead;
            }
        }
    }
    int maxPathFromHead = max1 + 1;
    maxPath = max(maxPath, max1 + max2 + 1);
    return Info(maxPathFromHead, maxPath);//���ص�ǰֵ
}

int main()
{
    cin>>n;
    graph.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>parent[i];
    }
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    for (int i = 1; i < n; i++) {
        if(parent[i]==-1)
            continue;
        graph[parent[i]].push_back(i);
    }
    //��ͼ
    cout<<f(0).maxPath;
    //��������������ֵ
    return 0;
}
