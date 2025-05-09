//P4160
//�������Ǽ��赱ǰ�ľ��γ�Ϊx����Ϊy��Ҫ�ֳ�k�飬
//��ô�����뵽�ֳ���һ��ĳ�mx���Ϊx/k����my���Ϊy/k��
//����ÿ���еĳ���һ����mx�ı�����my�ı���
//��Ϊÿ��ֻ�ܺͱ���ƽ�е���  ��Ҫ�г�����  ����
#include<bits/stdc++.h>
using namespace std;

int n;
double x, y;

double dfs(double x, double y, int k) {
    //Ŀǰ�ĵ��� ��Ϊx ��Ϊy Ҫ�ֳ�k��
    if (k == 1) {
        //һ�鵰�� ��������
        return max(x, y) / min(x, y);
    }
    double ans = 1e9, mx = x * 1.0 / k, my = y * 1.0 / k, t1, t2;//mx my����С��  ��С��
    for (int i = 1; i <= k / 2; i++) {
        t1 = max(dfs(mx * i, y, i), dfs(x - mx * i, y, k - i));
        t2 = max(dfs(x, my * i, i), dfs(x, y - my * i, k - i));
        ans = min(ans, min(t1, t2));
    }
    return ans;
}

int main() {
    cin >> x >> y >> n;
    // �����������Ϊ6λС��
    cout << fixed << setprecision(6) << dfs(x, y, n) << endl;
    return 0;
}

