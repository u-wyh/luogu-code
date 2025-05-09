// ��������ֱ��
// ����һ�ö������ĸ��ڵ㣬���ظ�����ֱ��
// �������� ֱ�� ��ָ�������������ڵ�֮���·���ĳ���
// ����·�����ܾ���Ҳ���ܲ��������ڵ� root
// ���ڵ�֮��·���� ���� ������֮�������ʾ
// �������� : https://leetcode.cn/problems/diameter-of-binary-tree/

#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct Info {
    int diameter;
    int height;

    Info(int a,int b) :diameter(a),height(b) {}
};

Info f(TreeNode* x){
    if(x==nullptr){
        return Info(0,0);
    }

    Info infol = f(x->left);//����ȫ����Ϣ
    Info infor = f(x->right);//����ȫ����Ϣ

    int height=max(infol.height,infor.height)+1;
    int diameter=max(infol.diameter,infor.diameter);
    diameter=max(diameter,infol.height+infor.height);

    return Info(diameter,height);
}

int diametertree(TreeNode* root){
    return f(root).diameter;
}

int main()
{
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);

    cout << "Largest Diameter Size: " << diametertree(root) << endl;
    return 0;
}
