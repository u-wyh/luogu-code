// ������������С��λ��
// ����һ������k����һ��k����������s��ʹ����ʮ�����£�s����λ�ۼӺ���С
// 2 <= k <= 10^5
// �������� : https://www.luogu.com.cn/problem/AT_arc084_b
// �������� : https://atcoder.jp/contests/abc077/tasks/arc084_b
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//01bfs�������������Բ�������  ʱ�临�Ӷ���һ��log
//������ֻ�����ڱ�ȨΪ0����1��ͼ
#include<bits/stdc++.h>
using namespace std;
const int MAXK = 100001;

int k;
deque<pair<int, int>> dq; // �� deque ������Ϊ dq
bool visit[MAXK];

int bfs() {
    //�����01bfs�õ����·
    dq.clear();
    dq.push_front({1, 1});//��ʼ��ʱ��  1%k=1    ����1�ǳ�ʼֵ
    memset(visit, false, sizeof(visit));

    while (!dq.empty()) {
        auto cur = dq.front();
        dq.pop_front();
        int mod = cur.first;
        int cost = cur.second;

        if (!visit[mod]) {
            //������������ǰû�з��ʹ�  ��ô����
            visit[mod] = true;
            if (mod == 0) {
                //�õ�%k=0����Сֵ
                return cost;
            }
            dq.push_front({(mod * 10) % k, cost});//�����ǳ�10  ��ȨΪ0  ��ͷ����
            dq.push_back({(mod + 1) % k, cost + 1});//����Ǽ�1  ��ȨΪ1  ��β����
        }
    }
    return -1;
}

int main() {
    cin >> k;
    cout << bfs() << endl;
    return 0;
}
