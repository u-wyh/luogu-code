// ·���ܺ� III
// ����һ���������ĸ��ڵ� root ����һ������ targetSum
// ��ö�������ڵ�ֵ֮�͵��� targetSum �� ·�� ����Ŀ
// ·�� ����Ҫ�Ӹ��ڵ㿪ʼ��Ҳ����Ҫ��Ҷ�ӽڵ����
// ����·��������������µģ�ֻ�ܴӸ��ڵ㵽�ӽڵ㣩
// �������� : https://leetcode.cn/problems/path-sum-iii/

#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
unordered_map<long, int> presum;//����ǰ׺�͵Ĺ�ϣ��
int target,ans;

void f(TreeNode* x, long sum) {
    if (x != nullptr) {
        sum += x->val; // ��ͷ�ڵ����һ·�ߵ�x�������ۼӺ�
        ans += presum.find(sum-target)!=presum.end()?presum[sum-target]:0;
        presum[sum]= (presum.find(sum)!=presum.end()?presum[sum]:0) + 1;
        f(x->left, sum);
        f(x->right, sum);
        presum[sum]-=1;
    }
}
//�����ͨ����ĳ�����β���
//ans��һ�ο�ʼ++ʵ�������ں���ڵ�  Ȼ�������Լ���Ӱ�켴presum[sum]-=1;

int pathSum(TreeNode* root) {
    presum[0]=1;
    f(root, 0);
    return ans;
}

int main()
{
    cin>>target;
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->right->right = new TreeNode(11);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right->right = new TreeNode(1);
    cout<<pathSum(root);
    return 0;
}
