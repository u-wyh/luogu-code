#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;

const int MAX_PRIME = 31;
const ll N_LIMIT = 1e18; // ���� n �����ޣ�����ȷ������Χ�ڵ���
vector<ll> primes = {0,2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127};

struct Node {
    ll value;
    ll prime;
    ll power;
    int limit; // ��һ����������������

    bool operator<(const Node& other) const {
        return value < other.value;
    }
};

priority_queue<Node> pq;

ll read() {
    ll ret = 0, sign = 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') {
        if (ch == '-') sign = -1;
    }
    while (ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    return ret * sign;
}

void write(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

void writeln(ll x) {
    write(x);
    putchar('\n');
}

int main() {
    ll n, k;
    n = read();
    k = read();

    // ��ʼ�����ȶ���
    for (int i = 1; i <= MAX_PRIME; ++i) {
        ll now = primes[i];
        for (int j = 1; now <= n; ++j, now *= primes[i]) {
            pq.push({now, primes[i], j, i - 1});
        }
    }

    // ȡ��ǰ k �����
    while (k--) {
        Node top = pq.top();
        pq.pop();
        if (k == 0) {
            writeln(top.value);
            break;
        }
        if (top.power > 1) {
            for (int i = 1; i <= top.limit; ++i) {
                pq.push({top.value / top.prime * primes[i], top.prime, top.power - 1, i});
            }
        }
    }

    return 0;
}

