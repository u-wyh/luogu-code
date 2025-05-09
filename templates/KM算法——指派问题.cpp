#include <bits/stdc++.h>
using namespace std;

// ����һ���ǳ��������Ϊ�����
const int INF = 1e9;

// ����ȫ�ֱ���
int n; // ����Ĵ�С�������Ƿ���
int cost[22][22]; // �ɱ�����
int matchX[22], matchY[22]; // ��¼ƥ���ϵ
int lx[22], ly[22]; // ����ı��
bool visX[22], visY[22]; // ���ʱ��
int slack[22]; // ��¼�ɳ���

// ���������������������Ѱ������·��
bool dfs(int x) {
    visX[x] = true; // ���X�����еĶ���xΪ�ѷ���
    for (int y = 0; y < n; ++y) { // ����Y�����е�ÿ������y
        if (visY[y]) continue; // ���y�Ѿ������ʹ���������
        int tmp = lx[x] + ly[y] - cost[x][y]; // ������֮�����Ȩ֮��
        if (tmp == 0) { // ����ҵ�һ�����б�
            visY[y] = true; // ���yΪ�ѷ���
            // ���y��δƥ��㣬���߿��Դ�y��ƥ�������ҵ�һ������·��
            if (matchY[y] == -1 || dfs(matchY[y])) {
                matchX[x] = y; // ��¼ƥ���ϵ
                matchY[y] = x;
                return true; // �ҵ�����·��������true
            }
        } else {
            // ������ǿ��бߣ������y���ɳ���
            slack[y] = min(slack[y], tmp);
        }
    }
    return false; // û���ҵ�����·��������false
}

// ���¶����ź���
void updateLabels() {
    int delta = INF;
    for (int y = 0; y < n; ++y) {
        if (!visY[y]) { // ��������δ���ʵ�Y�����еĶ���y
            delta = min(delta, slack[y]); // �ҵ���С���ɳ�����Ϊdelta
        }
    }
    for (int x = 0; x < n; ++x) {
        if (visX[x]) lx[x] -= delta; // ����X�������ѷ��ʶ���ı��
    }
    for (int y = 0; y < n; ++y) {
        if (visY[y]) ly[y] += delta; // ����Y�������ѷ��ʶ���ı��
        else slack[y] -= delta; // ����δ���ʶ�����ɳ���
    }
    // ע�⣺���ﲻӦ���ж�visX��visY���κν�һ�����û��޸�
    // ��Ϊ��������DFS�����й���ģ�updateLabels����ֻ������±��
}

// �������㷨�����СȨ������ƥ��
int hungarian() {
    memset(matchX, -1, sizeof(matchX)); // ��ʼ��ƥ���ϵΪδƥ��
    memset(matchY, -1, sizeof(matchY));
    memset(lx, 0, sizeof(lx)); // ��ʼ��X���϶���ı��Ϊ0
    memset(ly, 0, sizeof(ly)); // ��ʼ��Y���϶���ı��Ϊ0

    // ����ÿ��X���϶���ĳ�ʼ���lx[x]Ϊ�������������бߵ����Ȩ��
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            lx[x] = max(lx[x], cost[x][y]);
        }
    }

    // ����ÿ��X�����еĶ���x�������ҵ�һ������·��
    for (int x = 0; x < n; ++x) {
        fill(slack, slack + n, INF); // ��ʼ���ɳ���Ϊ�����
        while (true) { // ѭ��ֱ���ҵ�����·�����޷��ٸ��±��
            memset(visX, 0, sizeof(visX)); // ����X���϶���ķ��ʱ��
            memset(visY, 0, sizeof(visY)); // ����Y���϶���ķ��ʱ��
            if (dfs(x)) break; // ����Ѱ������·��
            updateLabels(); // ���¶�����
        }
    }

    // ������СȨ��ƥ�����Ȩ��
    int result = 0;
    for (int x = 0; x < n; ++x) {
        result += cost[x][matchX[x]]; // �ۼ�ÿ��ƥ��ߵ�Ȩ��
    }
    return result; // ������СȨ��ƥ�����Ȩ��
}

int main() {
    cin >> n; // �������Ĵ�С
    vector<vector<int>> a(n, vector<int>(n)), b(n, vector<int>(n)); // ������������a��b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j]; // �������a��Ԫ��
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> b[i][j]; // �������b��Ԫ��
        }
    }

    // ����ɱ�����cost������cost[i][j] = a[i][j] * b[j][i]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cost[i][j] = a[i][j] * b[j][i];
        }
    }

    // �����������㷨�����СȨ������ƥ��
    int minCost = hungarian();
    cout << minCost << endl; // �����СȨ��ƥ�����Ȩ��

    return 0;
}
