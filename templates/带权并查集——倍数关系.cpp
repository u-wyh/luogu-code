// ������ֵ
// ���б��������ַ�����ʾ�����Ҹ����������ʽ
// �����ʽ
// ["ab", "ef"] = 8������ab / ef = 8
// ["ct", "ef"] = 2������ct / ef = 2
// ���е�ʽ������ȷ�Ĳ��ҿ��Խ����ƶϣ��������е�ʽ֮�󣬻������������ѯ
// �����ѯ��["ab", "ct"]����������ĵ�ʽ�ƶϣ�ab / ct = 4
// ���ĳ����ѯ�еı���������û�ڵ�ʽ�г��ֹ�����Ϊ����-1.0
// ���ĳ����ѯ�Ĵ𰸸����ƶϲ���������Ϊ����-1.0
// �������в�ѯ�Ĵ�
// �������� : https://leetcode.cn/problems/evaluate-division/
#include <bits/stdc++.h>

using namespace std;

unordered_map<string, string> father;
unordered_map<string, double> dist;

void prepare(const vector<vector<string>>& equations) {
    father.clear();
    dist.clear();
    for (const auto& list : equations) {
        for (const auto& key : list) {
            father[key] = key;
            dist[key] = 1.0;
        }
    }
}

string find(const string& x) {
    //��ʾ������ʴ���û�г��ֹ�
    if (father.find(x) == father.end()) {
        return "";
    }
    string tmp, fa = x;
    if (x != father[x]) {
        tmp = father[x];
        fa = find(tmp);
        dist[x] *= dist[tmp];
        father[x] = fa;
    }
    return fa;
}

void union_sets(const string& l, const string& r, double v) {
    string lf = find(l), rf = find(r);
    if (lf != rf) {
        father[lf] = rf;
        dist[lf] = dist[r] / dist[l] * v;
    }
}

double query(const string& l, const string& r) {
    string lf = find(l), rf = find(r);
    if (lf.empty() || rf.empty() || lf != rf) {
        return -1.0;
    }
    return dist[l] / dist[r];
}

vector<double> calcEquation(const vector<vector<string>>& equations, const vector<double>& values, const vector<vector<string>>& queries) {
    prepare(equations);
    for (size_t i = 0; i < values.size(); ++i) {
        union_sets(equations[i][0], equations[i][1], values[i]);
    }
    vector<double> ans;
    for (const auto& query : queries) {
        ans.push_back(::query(query[0], query[1]));
    }
    return ans;
}

int main() {
    // Example usage:
    vector<vector<string>> equations = {{"a","b"},{"b","c"},{"bc","cd"}};
    vector<double> values = {1.5,2.5,5.0};
    vector<vector<string>> queries = {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}};

    vector<double> results = calcEquation(equations, values, queries);

    for (double result : results) {
        printf("%.5lf ",result);
    }

    return 0;
}
