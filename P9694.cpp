#include <bits/stdc++.h>
using namespace std;
#define maxn 1000005

int t;
int ed[maxn], cnt[maxn];
int tr[maxn][27], tot = 1;

void add(char *s, int len) {
    int p = 1;
    ++cnt[p];
    for (int i = 1; i <= len; ++i) {
        int u = s[i] - 'a' + 1;
        if (!tr[p][u]) {
            tr[p][u] = ++tot;
            memset(tr[tot], 0, sizeof tr[tot]); // ����ʱ˳����� trie
        }
        p = tr[p][u];
        ++cnt[p]; // ��¼������ǰλ�õ��ַ�������
    }
    ++ed[p]; // ��¼�ӵ�ǰλ�ý������ַ�������
    return;
}

char s[maxn];

void sol() {
    // ���ǵ����
    tot = 1;
    for (int i = 1; i <= 26; ++i)
        tr[1][i] = 0; // ����ײ�
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        add(s, len);
    }
    int p = 1;
    // ���󲿷�д���� dfs�������ü�ѭ��ʵ��
    while (1) {
        int sum = ed[p];
        for (int i = 1; i <= 26; ++i)
            if (cnt[tr[p][i]])
                ++sum; // ��һλÿ���ַ������ѡһ��
        if (sum >= k) {
            // �ж��𰸺Ϸ�
            for (int i = 1; i <= tot; ++i) {
                ed[i] = 0;
                cnt[i] = 0;
            }
            if (p == 1) // ���ײ㣬����Ϊ���ַ���
                printf("EMPTY");
            putchar('\n');
            // �Ѿ��ҵ����źϷ��𰸣��������򼴿�
            return;
        }
        for (int i = 1; i <= 26; ++i) {
            if (!cnt[tr[p][i]])
                continue;
            sum += cnt[tr[p][i]] - 1;
            // ֮���Լ�һ����Ϊ�����Ѿ�ÿ������һ��
            if (sum >= k) {
                // ȷ����һλ��ĸ
                k -= (sum - cnt[tr[p][i]]);
                // �ѵ�ǰ��ѡ�����ַ������� k �м���
                putchar((char)('a' + i - 1));
                // ��ȷ����ֱ���������
                p = tr[p][i];
                break; // ������һλ��ö��
            }
        }
    }
    return;
}

int main() {
    scanf("%d", &t);
    while (t--)
        sol();
    return 0;
}
