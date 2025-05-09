#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TrieNode {
public:
    int pass;//��ʾ�м������ʾ��������ĸ
    int en;//��ʾ�м��������������β
    vector<TrieNode*> nexts;//��ʾ�Լ�����Ľڵ�

    TrieNode() : pass(0), en(0) {
        nexts.resize(26, nullptr);
    }
    //���캯��
};

class Trie1 {
private:
    TrieNode* root;//���ͷ����������������

public:
    Trie1() {
        root = new TrieNode();
    }//���캯��

    ~Trie1() {
        deleteTrie(root);
    }//��������

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) return;
        for (TrieNode* child : node->nexts) {
            deleteTrie(child);
        }
        delete node;
    }//ɾ��������

    void insert(const string& word) {
        TrieNode* node = root;
        node->pass++;
        for (char ch : word) {
            int path = ch - 'a';//�ҵ�����ַ���Ӧ��·��
            if (node->nexts[path] == nullptr) {
                //������·��û�н�������ôֱ�ӽ���һ��·��
                node->nexts[path] = new TrieNode();
            }
            node = node->nexts[path];//�ڵ�ת�Ƶ���һ���ڵ�
            node->pass++;
        }
        node->en++;//�����һ���ڵ���en++
    }//�����ַ���

    void erase(const string& word) {
        if (countWordsEqualTo(word) > 0) {//�ж���������û���������
            TrieNode* node = root;
            node->pass--;
            for (char ch : word) {
                int path = ch - 'a';
                TrieNode* child = node->nexts[path];
                if (--child->pass == 0) {
                    //�����Ϊ0  ��ôɾ����������
                    delete node->nexts[path];
                    node->nexts[path] = nullptr;
                    return;
                }
                node = child;
            }
            node->en--;
        }
    }
    // ���֮ǰword�����ǰ׺������ô��ʱɾ��һ��
    // ���֮ǰwordû�в����ǰ׺������ôʲôҲ����

    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int path = ch - 'a';
            if (node->nexts[path] == nullptr) {
                //��ʾû�����·�� ����0
                return 0;
            }
            node = node->nexts[path];
        }
        return node->en;
    }
    //��ѯǰ׺����word�����˼���

    int countWordsStartingWith(const string& pre) {
        TrieNode* node = root;
        for (char ch : pre) {
            int path = ch - 'a';
            if (node->nexts[path] == nullptr) {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->pass;
    }
    //��ѯǰ׺������pre��ǰ׺�ĵ����м���
};

int main() {
    Trie1 trie;
    trie.insert("abc");
    trie.insert("abcd");
    trie.insert("abce");
    trie.insert("ab");
    cout << "Count of 'abc': " << trie.countWordsEqualTo("abc") << endl;
    cout << "Count of 'ab': " << trie.countWordsStartingWith("ab") << endl;
    trie.erase("abcd");
    cout << "Count of 'ab' after earse: " << trie.countWordsStartingWith("ab") << endl;

//    Trie1 trie;
//    trie.insert("hello");
//    trie.insert("world");
//    cout << "Count of 'hello': " << trie.countWordsEqualTo("hello") << endl;
//    cout << "Count of 'wor': " << trie.countWordsStartingWith("wor") << endl;
//    trie.erase("hello");
//    cout << "Count of 'hello' after erase: " << trie.countWordsEqualTo("hello") << endl;
    return 0;
}
