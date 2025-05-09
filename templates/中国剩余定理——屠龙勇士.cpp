// ������ʿ
// һ��nֻ������ÿֻ�������г�ʼѪ��hp[i]��ÿֻ�������лָ�����recovery[i]
// ÿֻ���������ڹ���������ʼ�ָ�����ʼһ��m�ѽ���ÿ�ѽ�������init[i]
// ÿֻ����ֻ�е�Ѫ��ǡ��Ϊ0ʱ�����ܱ�ɱ�������ĳֻ���������ֻ���ù̶��Ľ����������涨���£�
// �����������ڵ�ǰ������Ѫ�������ҹ���������һ�ѽ������û�������Ľ�����ѡ�񹥻�����͵�һ�ѽ�
// ��Ҫ��1~n��˳�������ַ�������i�ž�����ɱ���ǰѹ����Ľ�����ʧ��ͬʱ����������reward[i]�Ľ�
// ��ʿ�ƶ��Ĳ������£��������ʲô��������������ֻ���ans�£��õ�ǰ������Ѫ��<=0
// Ȼ���ڵ�ǰ�����ָ��Ĺ����У����Ѫ��ǡ��Ϊ0����ô��ǰ������ɱ������ʿ�����ַ���һֻ
// ��������������С��ans������ʿ�����ڸò�����ɱ�����о���
// ����ڹ̶���������Ĳ����£������޷�ɱ�����о���������-1
// �鿴���ݷ�Χ���Դ򿪲������� : https://www.luogu.com.cn/problem/P4774
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100001;

ll hp[MAXN];
ll recovery[MAXN];
ll reward[MAXN];
ll init[MAXN];
ll attack[MAXN];
map<ll, int> sorted;

long long d, x, y, px, py;

// ԭ�����ԣ�����033��λ����ʵ�ֳ˷�
// a * b�Ĺ����Լ�ʵ�֣�ÿһ���м���̶�%mod
// ��ôдĿ���Ƿ�ֹ�����Ҳ�й��ٳ�
long long multiply(long long a, long long b, long long mod) {
	// ��Ȼ����%mod�������£���ôa��b���Զ�ת���ɷǸ���
	// ���ⲻת������ν������������Ŀ������Ҫת��
	// ������b��Ҫת��������whileѭ�����ܲ���
	a = (a % mod + mod) % mod;
	b = (b % mod + mod) % mod;
	long long ans = 0;
	while (b != 0) {
		if ((b & 1) != 0) {
			ans = (ans + a) % mod;
		}
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}

void exgcd(long long a, long long b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// ÿֻ�������Ѫ���ҵ������Ľ�
ll allocate(int n, int m) {
    sorted.clear();
    for (int i = 1; i <= m; i++) {
        sorted[init[i]]++;
    }
    ll max_attacks = 0;
    for (int i = 1; i <= n; i++) {
        auto it = sorted.lower_bound(hp[i]);
        if (it == sorted.end()) {
            it = sorted.begin();
        }
        attack[i] = it->first;
        sorted[it->first]--;
        if (sorted[it->first] == 0) {
            sorted.erase(it);
        }
        sorted[reward[i]]++;
        max_attacks = max(max_attacks, (hp[i] + attack[i] - 1) / attack[i]);
        hp[i] %= recovery[i];
    }
    return max_attacks;
}

// bi * ans �� ri(% mi)��������� + ����Խ�����⴦��
ll compute(int n, int m) {
    // max�����ܹؼ��������߼���Ҫ�õ�
    // ��ֻ����Ҫ�����Σ���������Ѫ��<=0��������Ĵ�������max
    ll max = allocate(n, m);
    ll tail = 0, lcm = 1, tmp, a, b, c, x0;
    // ans = lcm * x + tail
    for (int i = 1; i <= n; i++) {
        // ai * ans = ai * lcm * x + tail * ai  1�ŷ���
        // ai * ans = ri * y + hi               2�ŷ���
        // ai * lcm * x + ri * y = hi - tail * ai
        a = multiply(attack[i], lcm, recovery[i]);
        b = recovery[i];
        c = ((hp[i] - attack[i] * tail) % b + b) % b;
        exgcd(a, b);
        if (c % d != 0) {
            return -1;
        }
        x0 = multiply(x, c / d, b / d);
        tmp = lcm * (b / d);
        tail = (tail + multiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }
    // ͨ�� ans = ? * lcm + tail
    // �������ڱ�������⴦��ע��max�����ĺ���
    // ����Ĵ�˼·�ǣ���ÿֻ���ޣ��������µĹ�ʽ�������ͬ��ʽ
    // ans * a[i] = h[i] + ÿֻ�������ɻָ����� * r[i]
    // ͬ��ʽΪ��ans * a[i] �� h[i] (% r[i])
    // ע�⣡�ܽ������ͬ��ʽ����ҪĬ��"ÿֻ�������ɻָ�����"�ķ�Χ������
    // ���ս����ans = k * lcm + tail��tail����С������
    // ��ʵ������ǣ�"ÿֻ�������ɻָ�����"���������ǷǸ��ģ�����������������
    // Ҳ����˵����Ҫȷ����ÿֻ���޵�Ѫ������<=0��Ȼ����ܱ�֤��ÿֻ�������ɻָ�����>=0
    // Ҳ����˵��ans = k * lcm + tail����Ҫȷ����ans >= max��ע��max�����ĺ��壡
    // ���tail >= max����ô�𰸾���tail����ʱk==0
    // ���tail < max���뱣֤ans >= max����ʵ����tail + k * lcm >= max
    // k = (max - tail) / lcm������ȡ����Ҳ����k = (max - tail + lcm - 1) / lcm
    // ���ԣ�ans = (max - tail + lcm - 1) / lcm * lcm + tail
    ll ans;
    if (tail >= max) {
        ans = tail;
    } else {
        ans = (max - tail + lcm - 1) / lcm * lcm + tail;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int cases;
    cin >> cases;
    for (int t = 1; t <= cases; t++) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> hp[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> recovery[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> reward[i];
        }
        for (int i = 1; i <= m; i++) {
            cin >> init[i];
        }
        cout << compute(n, m) << endl;
    }
    return 0;
}
