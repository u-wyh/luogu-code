// ���ʽ���
// �ֵ� wordList �дӵ��� beginWord �� endWord �� ת������
// ��һ������������γɵ����� beginWord -> s1 -> s2 -> ... -> sk ��
// ÿһ�����ڵĵ���ֻ��һ����ĸ��
// ���� 1 <= i <= k ʱ��ÿ�� si ���� wordList ��
// ע�⣬ beginWord ����Ҫ�� wordList �С�sk == endWord
// ������������ beginWord �� endWord ��һ���ֵ� wordList
// ���� �� beginWord �� endWord �� ���ת������ �е� ������Ŀ
// ���������������ת�����У����� 0 ��
// �������� : https://leetcode.cn/problems/word-ladder/
//����һ����ͨ���÷�  ���ý�����һ��С�Ż�
//ÿ�δ��������߽�С�ķ���ʼ����
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int ladderLength(string begin, string end, vector<string>& wordList) {
    // �ܴʱ�
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(end) == dict.end()) {
        return 0;
    }

    // ����С��һ��
    unordered_set<string> smallLevel;
    // �������һ��
    unordered_set<string> bigLevel;
    // ������С��һ�࣬����չ������һ���б�
    unordered_set<string> nextLevel;

    smallLevel.insert(begin);
    bigLevel.insert(end);

    for (int len = 2; !smallLevel.empty(); ++len) {
        for (const auto& w : smallLevel) {
            // ��С����չ
            string word = w;
            for (int j = 0; j < word.size(); ++j) {
                // ÿһλ�ַ�����
                char old = word[j];
                for (char change = 'a'; change <= 'z'; ++change) {
                    // ÿһλ�ַ�����a��z��һ��
                    if (change != old) {
                        word[j] = change;
                        string next = word;
                        if (bigLevel.find(next) != bigLevel.end()) {
                            return len;
                        }
                        if (dict.find(next) != dict.end()) {
                            dict.erase(next);
                            nextLevel.insert(next);
                        }
                    }
                }
                word[j] = old;
            }
        }

        if (nextLevel.size() <= bigLevel.size()) {
            swap(smallLevel, nextLevel);
            nextLevel.clear();
        } else {
            swap(smallLevel, bigLevel);
            swap(bigLevel, nextLevel);
            nextLevel.clear();
        }
    }

    return 0;
}

int main() {
    string begin = "hit";
    string end = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log"};

    int result = ladderLength(begin, end, wordList);
    cout << "Minimum number of steps: " << result << endl;

    return 0;
}
