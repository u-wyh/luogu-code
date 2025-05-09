// �������е��ʵ��Ӵ�
// ����һ���ַ���s��һ���ַ�������words
// words�������ַ���������ͬ
// s�еĴ����Ӵ���ָһ������ words�������ַ���������˳�����������������Ӵ�
// ����words = { "ab","cd","ef" }
// ��ô"abcdef"��"abefcd"��"cdabef"��"cdefab"��"efabcd"��"efcdab"���Ǵ����Ӵ���
// "acdbef"���Ǵ����Ӵ�����Ϊ�������κ�words���е�����
// �������д����Ӵ���s�еĿ�ʼ����
// �����������˳�򷵻ش�
// �������� : https://leetcode.cn/problems/substring-with-concatenation-of-all-words/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>

using namespace std;

const int MAXN = 10001;
const int BASE = 499;
long long power[MAXN];
long long hash_val[MAXN];

void build(const string& str) {
    power[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        power[j] = power[j - 1] * BASE;
    }
    hash_val[0] = str[0] - 'a' + 1;
    for (int j = 1; j < str.length(); ++j) {
        hash_val[j] = hash_val[j - 1] * BASE + str[j] - 'a' + 1;
    }
}

// ���´������ַ�����ϣ��ԭ���ģ��
// ���磬base = 499, Ҳ���ǿ���˵��ѡ�����������
// �ٱ����ַ���s����
// " c a b e f "
//   0 1 2 3 4
// hash[0] = 3 * base��0�η�
// hash[1] = 3 * base��1�η� + 1 * base��0�η�
// hash[2] = 3 * base��2�η� + 1 * base��1�η� + 2 * base��0�η�
// hash[3] = 3 * base��3�η� + 1 * base��2�η� + 2 * base��1�η� + 5 * base��0�η�
// hash[4] = 3 * base��4�η� + 1 * base��3�η� + 2 * base��2�η� + 5 * base��1�η� + 6 *
// base��0�η�
// hash[i] = hash[i-1] * base + s[i] - 'a' + 1����������˵����˼
// ������Ӵ�"be"�Ĺ�ϣֵ -> 2 * base��1�η� + 5 * base��0�η�
// �Ӵ�"be"�Ĺ�ϣֵ = hash[3] - hash[1] * base��2�η�(�Ӵ�"be"�ĳ��ȴη�)
// hash[1] = 3 * base��1�η� + 1 * base��0�η�
// hash[1] * base��2�η� = 3 * base��3�η� + 1 * base��2�η�
// hash[3] = 3 * base��3�η� + 1 * base��2�η� + 2 * base��1�η� + 5 * base��0�η�
// hash[3] - hash[1] * base��2�η� = 2 * base��1�η� + 5 * base��0�η�
// �����͵õ��Ӵ�"be"�Ĺ�ϣֵ��
// �Ӵ�s[l...r]�Ĺ�ϣֵ = hash[r] - hash[l-1] * base��(r-l+1)�η�����������˵����˼

// ��Χ��s[l,r)������ҿ�
long long getHash(int l, int r) {
    long long ans = hash_val[r - 1];
    if (l > 0) {
        ans -= hash_val[l - 1] * power[r - l];
    }
    return ans;
}

// ����һ���ַ����Ĺ�ϣֵ
long long hashString(const string& str) {
    if (str.empty()) {
        return 0;
    }
    int n = str.length();
    long long ans = str[0] - 'a' + 1;
    for (int j = 1; j < n; ++j) {
        ans = ans * BASE + str[j] - 'a' + 1;
    }
    return ans;
}

vector<int> findSubstring(const string& s, const vector<string>& words) {
    vector<int> ans;
    if (s.empty() || words.empty()) {
        return ans;
    }
    // words�Ĵ�Ƶ��
    unordered_map<long long, int> map;
    for (const string& key : words) {
        long long v = hashString(key);
        map[v]++;
    }
    build(s);
    int n = s.length();
    int wordLen = words[0].length();
    int wordNum = words.size();
    int allLen = wordLen * wordNum;
    // ���ڵĴ�Ƶ��
    unordered_map<long long, int> window;
    for (int init = 0; init < wordLen && init + allLen <= n; ++init) { // ͬ�����
        // init�ǵ�ǰ����׸���ͷ
        int debt = wordNum;
        // �����𴰿�
        for (int l = init, r = init + wordLen, part = 0; part < wordNum; l += wordLen, r += wordLen, ++part) {
            long long cur = getHash(l, r);
            window[cur]++;
            if (window[cur] <= map[cur]) {
                debt--;
            }
        }
        if (debt == 0) {
            ans.push_back(init);
        }
        // ���������ڽ�һ������һ��
        for (int l1 = init, r1 = init + wordLen, l2 = init + allLen,
             r2 = init + allLen + wordLen; r2 <= n; l1 += wordLen, r1 += wordLen, l2 += wordLen, r2 += wordLen) {
            long long out = getHash(l1, r1);
            long long in = getHash(l2, r2);
            window[out]--;
            if (window[out] < map[out]) {
                debt++;
            }
            window[in]++;
            if (window[in] <= map[in]) {
                debt--;
            }
            if (debt == 0) {
                ans.push_back(r1);
            }
        }
        window.clear();
    }
    return ans;
}

int main() {
    string s ;
    int n;
    cin>>s>>n;
    vector<string> words;
    for(int i=0;i<n;i++){
        string str;
        cin >>str;
        words.push_back(str);
    }
    vector<int> result = findSubstring(s, words);
    for (int index : result) {
        cout << index << " ";
    }
    cout << endl;
    return 0;
}
// ���s�ĳ���Ϊn��words�����е��ʵ��ܳ���Ϊm
// ʱ�临�Ӷ�O(n + m)�����Ž��ʱ�临�Ӷ��뵥�ʸ��������ʳ������޹ص�
// ������ⶼû������������Ӷȵ�
// ��Ȼ���������ܱ���û�е�100%����������Ϊ����������������
// �������Ž��ʱ�临�Ӷ�����û�����ֳ���
// ����������������Ž⣬ֻ��ͬ����� + �ַ�����ϣ��ʱ�临�ӶȲ��ܵ�����
/*
barfoothefoobarman
2
foo
bar

barfoofoobarthefoobarman
3
bar
foo
the

wordgoodgoodgoodbestword
4
word
best
good
word
*/
