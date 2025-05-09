// ���BST����
// ����һ�����������ҵ��������Ķ�����������BST�������������ظ������Ĵ�С
// ���У����ָ���������ڵ�������
// ������������BST���е����нڵ㶼�߱��������ԣ�
// ��������ֵС���丸�������ڵ��ֵ
// ��������ֵ�����丸�������ڵ��ֵ
// ע�⣺����������������к��
// BST��һ������Ķ�����������ÿ���ڵ���������е����нڵ㶼С�ڸýڵ��ֵ�����������е����нڵ㶼���ڸýڵ��ֵ��
// �������� : https://leetcode.cn/problems/largest-bst-subtree/
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// �������ڵ�ṹ
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
//������״�ṹ ������ڵ㣬�ҽڵ��Լ�ֵ��С

// ����һ���ṹ�����洢ÿ����������Ϣ
struct Info {
    long long maxans;//�����������ֵ
    long long minans;//����������Сֵ
    bool isBst;//�Ե�ǰΪ�׵����Ƿ�ȫ����һ��������������
    int maxBstSize;//������������������ж��

    Info(long long a, long long b, bool c, int d) : maxans(a), minans(b), isBst(c), maxBstSize(d) {}
};

// �ݹ麯����������������Ϣ
Info f(TreeNode* x) {
    if (x == nullptr) {
        return Info(LLONG_MIN, LLONG_MAX, true, 0);
    }

    Info infol = f(x->left);//����ȫ����Ϣ
    Info infor = f(x->right);//����ȫ����Ϣ

    long long maxVal = max((long long )x->val, max(infol.maxans, infor.maxans));
    long long minVal = min((long long )x->val, min(infol.minans, infor.minans));
    bool isBST = infol.isBst && infor.isBst && infol.maxans < x->val && x->val < infor.minans;
    int maxBSTSize = isBST ? infol.maxBstSize + infor.maxBstSize + 1 : max(infol.maxBstSize, infor.maxBstSize);
    //��ǰ�ڵ��ȫ����Ϣ

    return Info(maxVal, minVal, isBST, maxBSTSize);
}

// �������������ҵ����BST�����Ĵ�С
int largestBSTSubtree(TreeNode* root) {
    return f(root).maxBstSize;
}


int main() {
    // ����һ��ʾ����
    //       10
    //      /  \
    //     5    15
    //    / \    \
    //   1   8    7
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(10);

    // �ҵ����BST�����Ĵ�С
    cout << "Largest BST Subtree Size: " << largestBSTSubtree(root) << endl;

    return 0;
}
