// �Ƴ�������Ķ������߶�
// ����һ�� ������ �ĸ��ڵ� root �������� n ���ڵ�
// ÿ���ڵ㶼���Ա�����һ���� 1 �� n �һ�����ͬ��ֵ
// �����һ������Ϊ m ������ queries
// �����������ִ�� m �� ���� �Ĳ�ѯ�����е� i ����ѯ����Ҫִ�����²�����
// ������ �Ƴ� �� queries[i] ��ֵ��Ϊ���ڵ������
// ��Ŀ���ò���������֤ queries[i] �����ڸ��ڵ��ֵ
// ����һ������Ϊ m ������ answer
// ���� answer[i] ��ִ�е� i ����ѯ�����ĸ߶�
// ע�⣺
// ��ѯ֮���Ƕ����ģ�������ÿ����ѯִ�к�����ص����ʼ״̬
// ���ĸ߶��ǴӸ�������ĳ���ڵ�� ���·���еı���
// �������� : https://leetcode.cn/problems/height-of-binary-tree-after-subtree-removal-queries/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100010;

// �±�Ϊ�ڵ��ֵ
int dfn[MAXN];
// �±�Ϊdfn���
int deep[MAXN];
// �±�Ϊdfn���
int sz[MAXN];
int maxl[MAXN];//ͳ��dfn���С��i������߶�
int maxr[MAXN];//ͳ��dfn��Ŵ���i������߶�
int dfnCnt;
// �������ڵ�ṹ
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
int query[MAXN];
int ans[MAXN];
int n;

// ����x�ڵ㣬��ͷ�ڵ㵽x�ڵ㾭����k����
void f(TreeNode* x, int k) {
    int i = ++dfnCnt;
    dfn[x->val] = i;//����ֵ��dfn
    deep[i] = k;//��ͷ�ڵ㵽���ڵ�����������
    sz[i] = 1;
    //����dfn��deep  sz
    if (x->left != nullptr) {
        f(x->left, k + 1);
        sz[i] += sz[dfn[x->left->val]];//sz������dfn�����
    }
    if (x->right != nullptr) {
        f(x->right, k + 1);
        sz[i] += sz[dfn[x->right->val]];
    }
}
//����dfn  sz  deep ����

void treeQueries(TreeNode* root) {
    dfnCnt = 0;
    f(root, 0);
    for (int i = 1; i <= dfnCnt; i++) {
        maxl[i] =max(maxl[i - 1], deep[i]);
    }
    maxr[dfnCnt + 1] = 0;
    for (int i = dfnCnt; i >= 1; i--) {
        maxr[i] =max(maxr[i + 1], deep[i]);
    }
    //���maxl  maxr����
    for (int i = 1; i <= n; i++) {
        int leftMax = maxl[dfn[query[i]] - 1];
        int rightMax = maxr[dfn[query[i]] + sz[dfn[query[i]]]];
        //ÿһ�β�ѯ��ʱ��  ����dfn[query[i]]��dfn[query[i]] + sz[dfn[query[i]]]-1������
        //��ô��ѯһ����ߺ��ұ�
        ans[i] =max(leftMax, rightMax);
    }
}

int main()
{
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(8);
    root->right = new TreeNode(9);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(1);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(7);
    root->left->left->right = new TreeNode(6);
    root->left->left->left = new TreeNode(4);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>query[i];
    }
    treeQueries(root);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}
