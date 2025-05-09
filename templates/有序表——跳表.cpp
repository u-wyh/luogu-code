// �����ʵ��(C++��)
// ʵ��һ�ֽṹ��֧�����²�����Ҫ�󵥴ε��õ�ʱ�临�Ӷ�O(log n)
// 1������x���ظ�����������Ƶ
// 2��ɾ��x������ж����ֻɾ��һ��
// 3����ѯx��������x������Ϊ����xС�����ĸ���+1
// 4����ѯ����������Ϊx����
// 5����ѯx��ǰ����x��ǰ��Ϊ��С��x�������������������ڷ���������Сֵ
// 6����ѯx�ĺ�̣�x�ĺ��Ϊ������x��������С�����������ڷ����������ֵ
// ���в����Ĵ��� <= 10^5
// -10^7 <= x <= +10^7
// �������� : https://www.luogu.com.cn/problem/P3369
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>

using namespace std;

const int MAXL = 20;
//���ֵ��ѡȡ�� 2��MAXL�η� ��  ��ӽ�����MAXN����Сֵ
const int MAXN = 100001;

int cnt;//���ڼ�¼�ڵ��� ��AVLһ��
int key[MAXN];//���ڼ�¼��ǰ�ڵ��Ӧ�ļ�ֵ�Ƕ���
int key_count[MAXN];//���ڼ�¼��ǰֵ�����˶��ٴ�
int level[MAXN];//���ڼ�¼�ýڵ�����ж��ٲ�   ��ʼʱ�������
int next_node[MAXN][MAXL + 1];//���ڼ�¼�ýڵ�ĵ�i��ָ�����һ���ڵ���ʲô
int len[MAXN][MAXL + 1];//��¼�ýڵ�ĵ�i�㵽��һ������֮���ж��ٸ�����  ��Ӧ��һ������ָ���  ���ұ�

void build() {
    cnt = 1;
    key[cnt] = INT_MIN;//��һ���ڵ�ı����Զ��1
    level[cnt] = MAXL;//���Ĳ���ֱ������Ϊ����
}
//��ʼ����ͷ  ���ű� Խ���� ֵԽ��

void clear() {
    memset(key + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(level + 1, 0, cnt * sizeof(int));
    for (int i = 1; i <= cnt; i++) {
        memset(next_node[i], 0, (MAXL + 1) * sizeof(int));
        memset(len[i], 0, (MAXL + 1) * sizeof(int));
    }
    cnt = 0;
}

int randomLevel() {
    //��������½ڵ�Ĳ���ֵ ������Զ�������
    int ans = 1;
    while ((std::rand() / double(RAND_MAX)) < 0.5) {
        ans++;
    }
    return min(ans, MAXL);
}

// ��ǰ��i�Žڵ��h�㣬����keyΪnum�Ľڵ㣬�ռ����Ƕ���
int find(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        //�Լ�����һ���ڵ㲻��0  ˵������ָ��Ķ���
        //����ָ�����һ��ֵС��num ˵������������һ���ϼ�������Ѱ��
        //��������Щ����
        i = next_node[i][h];
    }
    //���while������ ��һ���ڵ�Ҫô��0 ����
    //Ҫô�Ǵ��ڵ���num������
    //�����һ�����ִ���num  ��ô˵����Ҫȥ��һ��Ѱ��
    //��ʹ��һ�����־���num  �����ڲ�����ײ� �����ǵ�һ��
    //��ô���ǻ�������  ��Ϊ�����϶�����  ����ֻ��Ҫ�ڵ�һ���ҵ��ڵ�
    //���Ҽ�ʹ��һ���ڵ���ǿ�  ����Ҳ���ڵ�һ���ʱ�������
    if (h == 1) {
        if (next_node[i][h] != 0 && key[next_node[i][h]] == num) {
            //next_node[i][h]��ʾ�ڵ�i�ĵ�h�����һ���ڵ�
            return next_node[i][h];
        } else {
            //������Ӧ���ҵ�����λ��ȴ����û���ҵ�  ��ô���ǲ�����  ����0
            return 0;
        }
    }
    return find(i, h - 1, num);
    //��ǰ�ڵ�һ����С��num��  ��һ��һ���Ǵ��ڵ���num��
    //�ڵ�ǰ�ڵ�����һ�������
}

// ��ǰ��i�Žڵ��h�㣬num����һ����Ƶ
void addCount(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        key_count[next_node[i][h]]++;
    } else {
        //ֻҪ���ǵ�һ�� ��ô��Ҫ�ݹ�
        //���Ӵ�Ƶ������ϵ��м�������������Ӱ��
        addCount(i, h - 1, num);
    }
    len[i][h]++;
    //��һ��ʼi�Ѿ�����һ���ڵ���Ǵ��ڵ���num����
    //��num�ڵ�һ������  ��������Ǵ������� ��ô˵�����ǲ���̫����
    //���ܲ�����ô�� i��h��������һ���ᾭ��num  ��Ϊ���ұ�
}

// ��ǰ��i�Žڵ��h�㣬����ռ���Ϊj�Ľڵ�
// ����ֵ����i�Žڵ������ֱ���ѿռ���Ϊj�Ľڵ���룬�ײ��ܹ��ж������ֱ�key[j]С
// ����ֵ����Ҫ����Ϊ������Ҫ�����Ϣ���Ķ�ָ��ĳ�����Ϣ
int addNode(int i, int h, int j) {
    int rightCnt = 0;
    //����ͳ��i�ڵ㵽  ��һ���ڵ���ڵ���key[j] �Ľڵ��м����
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        next_node[j][h] = next_node[i][h];
        next_node[i][h] = j;
        len[j][h] = key_count[next_node[j][h]];//ֱ�Ӿ��Ǵ�Ƶ  ��Ϊ������ײ�
        len[i][h] = key_count[next_node[i][h]];//����ط�Ҳ������1   �Ͼ������½��ڵ�  һ����1
        return rightCnt;
    } else {
        int downCnt = addNode(i, h - 1, j);
        if (h > level[j]) {
            len[i][h]++;
        } else {
            next_node[j][h] = next_node[i][h];
            next_node[i][h] = j;
            len[j][h] = len[i][h] + 1 - downCnt - key_count[j];
            len[i][h] = downCnt + key_count[j];
        }
        return rightCnt + downCnt;
    }
}

// ����num���ظ�����������Ƶ
void add(int num) {
    if (find(1, MAXL, num) != 0) {
        addCount(1, MAXL, num);
    } else {
        key[++cnt] = num;
        key_count[cnt] = 1;
        level[cnt] = randomLevel();
        addNode(1, MAXL, cnt);
    }
}

// ��ǰ��i�Žڵ��h�㣬num����һ����Ƶ
void removeCount(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        key_count[next_node[i][h]]--;
    } else {
        removeCount(i, h - 1, num);
    }
    len[i][h]--;
}

// ��ǰ��i�Žڵ��h�㣬ɾ���ռ���Ϊj�Ľڵ�
void removeNode(int i, int h, int j) {
    if (h < 1) {
        return;
    }
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        i = next_node[i][h];
    }
    if (h > level[j]) {
        len[i][h]--;
    } else {
        next_node[i][h] = next_node[j][h];
        len[i][h] += len[j][h] - 1;
    }
    removeNode(i, h - 1, j);
}

// ɾ��x������ж����ֻɾ��һ��
void remove(int num) {
    int j = find(1, MAXL, num);
    if (j != 0) {
        //�ڵ����
        if (key_count[j] > 1) {
            removeCount(1, MAXL, num);
        } else {
            removeNode(1, MAXL, j);
        }
    }
}

// ��ǰ��i�Žڵ��h�㣬��ѯ�ж��ٸ����ֱ�numС
int small(int i, int h, int num) {
    int rightCnt = 0;
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        return rightCnt;
    } else {
        return rightCnt + small(i, h - 1, num);
    }
}

// ��ѯnum������
int getRank(int num) {
    return small(1, MAXL, num) + 1;
}

// ��ǰ��i�Žڵ��h�㣬��ѯ������x��key��ʲô
int index(int i, int h, int x) {
    int c = 0;
    while (next_node[i][h] != 0 && c + len[i][h] < x) {
        c += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        return key[next_node[i][h]];
    } else {
        return index(i, h - 1, x - c);
    }
}

// ��ѯ������x��key��ʲô
int index(int x) {
    return index(1, MAXL, x);
}

int pre(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        return i == 1 ? INT_MIN : key[i];
    } else {
        return pre(i, h - 1, num);
    }
}

// ��ѯnum��ǰ��
int pre(int num) {
    return pre(1, MAXL, num);
}

int post(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        if (next_node[i][h] == 0) {
            return INT_MAX;
        }
        if (key[next_node[i][h]] > num) {
            return key[next_node[i][h]];
        }
        i = next_node[i][h];
        if (next_node[i][h] == 0) {
            return INT_MAX;
        } else {
            return key[next_node[i][h]];
        }
    } else {
        return post(i, h - 1, num);
    }
}

// ��ѯnum�ĺ��
int post(int num) {
    return post(1, MAXL, num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    build();
    int n;
    cin >> n;
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << endl;
        } else if (op == 4) {
            cout << index(x) << endl;
        } else if (op == 5) {
            cout << pre(x) << endl;
        } else {
            cout << post(x) << endl;
        }
    }
    clear();
    return 0;
}
