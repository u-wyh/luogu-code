// ��ض�����
// ����һ�������������������Ľڵ��ϰ�װ����ͷ
// �ڵ��ϵ�ÿ����Ӱͷ�����Լ����丸����������ֱ���Ӷ���
// �������������нڵ��������С����ͷ����
// �������� : https://leetcode.cn/problems/binary-tree-cameras/

#include<bits/stdc++.h>
using namespace std;
int ans;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// �ݹ麬��
// ����x�Ϸ�һ���и��׵�����£�����������Ҫ
// xΪͷ���������������붼���ǣ�
// ������ʹ�����ٵ�����ͷ��xӦ����ʲô����״̬
// ����ֵ����
// 0: x���޸��ǵ�״̬��x�·��Ľڵ㶼�Ѿ�������
// 1: x�Ǹ���״̬��x��û����ͷ��x�·��Ľڵ㶼�Ѿ�������
// 2: x�Ǹ���״̬��x��������ͷ��x�·��Ľڵ㶼�Ѿ�������
int f(TreeNode* x) {
    if (x == nullptr) {
        return 1;
    }
    int left = f(x->left);
    int right = f(x->right);
    if (left == 0 || right == 0) {
        ans++;
        return 2;
    }
    if (left == 1 && right == 1) {
        return 0;
    }
    return 1;
}

int minCameraCover(TreeNode* root) {
    ans = 0;
    if (f(root) == 0) {
        //��ʾ���еĶ�������  ���������Ӷ���1  ����root�ڵ�
        ans++;
    }
    return ans;
}

int main()
{
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
//    root->left->left = new TreeNode(1);
//    root->left->right = new TreeNode(8);
//    root->right->right = new TreeNode(7);

    cout << "Largest Root Subtree Size: " << minCameraCover(root) << endl;
    return 0;
}
