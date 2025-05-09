// ������������������ֵ��
// ����һ���� root Ϊ���Ķ�����
// ���㷵�� ���� ������������������ֵ��
// �����������Ķ������£�
// ����ڵ���������еļ�ֵ�� С�� �˽ڵ�ļ�ֵ
// ����ڵ���������еļ�ֵ�� ���� �˽ڵ�ļ�ֵ
// ����ڵ�������������������Ƕ���������
// �������� : https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/

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
    int maxans;//�����������ֵ
    int minans;//����������Сֵ
    bool isBst;//�Ե�ǰΪ�׵����Ƿ�ȫ����һ��������������
    int maxBstSum;//���������������������ۼӺ��ж��
    int sum;//���������ۼӺ�

    Info(int a,int b, bool c, int d,int e) : maxans(a), minans(b), isBst(c), maxBstSum(d), sum(e) {}
};

// �ݹ麯����������������Ϣ
Info f(TreeNode* x) {
    if (x == nullptr) {
        return Info(INT_MIN, INT_MAX, true, 0, 0);
    }

    Info infol = f(x->left);//����ȫ����Ϣ
    Info infor = f(x->right);//����ȫ����Ϣ

    int maxVal = max(x->val, max(infol.maxans, infor.maxans));
    int minVal = min(x->val, min(infol.minans, infor.minans));
    bool isBST = infol.isBst && infor.isBst && infol.maxans < x->val && x->val < infor.minans;
    int sumans=infol.sum+infor.sum+x->val;
    //��ǰ�ڵ��ȫ����Ϣ
    int maxBSTSum = max(infol.maxBstSum, infor.maxBstSum);
    if (isBST) {
        maxBSTSum = max(maxBSTSum, sumans);
    }

    return Info(maxVal, minVal, isBST, maxBSTSum, sumans);
}

// �������������ҵ����BST�����Ĵ�С
int largestBSTSubtree(TreeNode* root) {
    return f(root).maxBstSum;
}


int main() {
    // ����һ��ʾ����
    //       10
    //      /  \
    //     5    15
    //    / \    \
    //   1   8    7
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);

    // �ҵ����BST�����Ĵ�С
    cout << "Largest BST Subtree Size: " << largestBSTSubtree(root) << endl;

    return 0;
}

