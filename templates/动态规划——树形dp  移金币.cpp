// �ڶ������з���Ӳ��
// ����һ���� n �����Ķ������ĸ���� root
// ��������ÿ����� node ����Ӧ�� node.val öӲ��
// ��������һ���� n öӲ��
// ��һ���ƶ��У����ǿ���ѡ���������ڵĽ�㣬Ȼ��һöӲ�Ҵ�����һ������ƶ�����һ�����
// �ƶ������ǴӸ���㵽�ӽ�㣬���ߴ��ӽ���ƶ��������
// ����ʹÿ������� ֻ�� һöӲ������� ���� �ƶ�����
// �������� : https://leetcode.cn/problems/distribute-coins-in-binary-tree/
#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct Info {
    int cnt;//�ڵ�
    int moves;
    int sum;//����

    Info(int a,int b,int c) :cnt(a),sum(b),moves(c) {}
};

Info f(TreeNode* x){
    if(x==nullptr){
        return Info(0,0,0);
    }

    Info infol = f(x->left);//����ȫ����Ϣ
    Info infor = f(x->right);//����ȫ����Ϣ

    int sum=infol.sum+infor.sum+x->val;
    int cnt=infol.cnt+infor.cnt+1;
    int moves=infol.moves+infor.moves+abs(infol.sum-infol.cnt)+abs(infor.cnt-infor.sum);

    return Info(cnt,sum,moves);
}

int movestree(TreeNode* root){
    return f(root).moves;
}

int main()
{
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(0);
    root->right = new TreeNode(0);
//    root->left->left = new treenode(1);
//    root->left->right = new treenode(8);
//    root->right->right = new treenode(7);

    cout << "Largest Moves Size: " << movestree(root) << endl;
    return 0;
}

