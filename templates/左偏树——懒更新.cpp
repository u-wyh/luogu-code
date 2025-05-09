// �ǳع�ռ��C++��
// һ����n�����У�1�ų����ǳ�������ͷ��ÿ�����ж��з���ֵ���ϼ����б�š��������͡�����ֵ
// �����������Ϊ0���κ���ʿ����������к󣬹���������Ͻ���ֵ
// �����������Ϊ1���κ���ʿ����������к󣬹���������Խ���ֵ
// �κγ��е��ϼ���� < �������еı�ţ�1�ų���û���ϼ����б�š��������͡�����ֵ
// һ����m����ʿ��ÿ����ʿ���й���������һ�ι����ĳ���
// �����ʿ������ >= ���з���ֵ����ǰ���лᱻ��ռ����ʿ��ý��������������ϼ�����
// �����ʿ������  < ���з���ֵ����ô��ʿ���ڸó���������û�к���������
// ������ʿ���Ƕ����ģ�����Ӱ��������ʿ���������ǳصĽ��
// ��ӡÿ��������������ʿ��������ӡÿ����ʿ��ռ�ĳ�������
// 1 <= n��m <= 3 * 10^5������ֵ������Ҳ���ᳬ��long���ͷ�Χ
// �������� : https://www.luogu.com.cn/problem/P3261
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300001;
int n, m;
// ���з���ֵ
long long defend[MAXN];
// �ϼ����б��
int belong[MAXN];
// ��������
int type[MAXN];
// ����ֵ
long long gain[MAXN];
long long attack[MAXN];
// ��ʿ��һ�ι����ĳ���
int first[MAXN];
// �����ڳ������е����
int deep[MAXN];
// ����ӵ�е���ʿ�б���С������ƫ����֯����������ʿ��ͷ
int top[MAXN];
// ÿ��������������ͳ��
int sacrifice[MAXN];
// ÿ����ʿ������ʲô����
int die[MAXN];
// ��ƫ����Ҫ   ��ƫ��ά��С����
//�����������ķ�������  ����������Ķ����Գɹ�  ˵�����еĶ��ܳɹ�
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// ��������Ϣ��������Ӧ�ó˶���
long long mul[MAXN];
// ��������Ϣ��������Ӧ�üӶ���
long long add[MAXN];

//��Ϣȫ����ʼ��
void prepare() {
    dist[0] = -1;
    for (int i = 1; i <= m; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        mul[i] = 1;
        add[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        sacrifice[i] = top[i] = 0;
    }
}

//������Ϣ  ��i����ʿ��������Ϊt��ֵΪv�Ľ���
//���ֻ���Ǵ�����ǰĳ�����е�С���ѵ�ͷ�ڵ�
void upgrade(int i, int t, long long v) {
    if (t == 0) {
        //������������
        attack[i] += v;
        add[i] += v;
    } else {
        //������������
        attack[i] *= v;
        mul[i] *= v;
        add[i] *= v;
    }
}

//����Ϣ���´���
void down(int i) {
    if (mul[i] != 1 || add[i] != 0) {
        //��ʾȷʵ��Ҫ���ݵĸ�����Ϣ
        int l = ls[i];
        int r = rs[i];
        if (l != 0) {
            //�������
            attack[l] = attack[l] * mul[i] + add[i];
            //������ӵ�ֵ���¶�  Ȼ�󽫸�����Ϣ����  �������´���
            mul[l] = mul[l] * mul[i];
            add[l] = add[l] * mul[i] + add[i];
        }
        if (r != 0) {
            attack[r] = attack[r] * mul[i] + add[i];
            mul[r] = mul[r] * mul[i];
            add[r] = add[r] * mul[i] + add[i];
        }
        mul[i] = 1;
        add[i] = 0;
        //���Լ��ĸ�����Ϣ�޸�
    }
}

//�ϲ�����  Ψһ��ͬ�ľ����и�down
int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (attack[i] > attack[j]) {
        swap(i, j);
    }
    down(i);
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]]) {
        swap(ls[i], rs[i]);
    }
    dist[i] = dist[rs[i]] + 1;
    return i;
}

//����ͷ���  Ψһ��ͬ�ľ����и�down
int pop(int i) {
    down(i);
    int ans = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return ans;
}

void compute() {
    deep[1] = 1;
    for (int i = 2; i <= n; i++) {
        deep[i] = deep[belong[i]] + 1;
    }
    //���Ƚ������ڵ����ȼ������  ��Ϊ���нڵ�����ȶ���ǰ��  ���Բ�ҪdfsҲ����
    for (int i = 1; i <= m; i++) {
        if (top[first[i]] == 0) {
            //��ʾ�����ʿ��һ��Ҫ�����ĳ��л�û��������ʿ����
            //��ô������е���ʿ�ŵ�һλ������
            top[first[i]] = i;
        } else {
            //��ʾ�����ʿ��һ��Ҫ�����ĳ�����������ʿ����
            //��ô��Ҫ���Ѿ����ڵ���ʿ�źϲ�ΪС����
            top[first[i]] = merge(top[first[i]], i);
        }
    }
    //������ĸ������е���ʿ����Ϣ����ΪС����
    for (int i = n; i >= 1; i--) {
        //�Ӻ���ǰ����  ��Ϊ����ĳ��е���ʿҪ�ǳɹ��� �ͻᵽǰ��ĳ���
        while (top[i] != 0 && attack[top[i]] < defend[i]) {
            //��ʾ����ʿ  ������������ʿʧ����
            die[top[i]] = i;//��¼��������ʿ�����ص������������
            sacrifice[i]++;//��ô���������������ʿ��һ
            top[i] = pop(top[i]);//����������ʿ����
        }
        if (top[i] != 0) {
            //��ʾ������ʿ  ��ô��ý���
            upgrade(top[i], type[i], gain[i]);
            if (top[belong[i]] == 0) {
                //���������е��ϼ�����û����ʿ����
                //��ôֱ�ӽ������ʿ��ȫ��������һ������
                top[belong[i]] = top[i];
            } else {
                //������ĸ����е���ʿ�źϲ�
                top[belong[i]] = merge(top[belong[i]], top[i]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    //��ʼ����Ϣ
    prepare();
    //�����е���Ϣ����
    for (int i = 1; i <= n; i++) {
        cin >> defend[i];
    }
    for (int i = 2; i <= n; i++) {
        cin >> belong[i] >> type[i] >> gain[i];
    }
    //������ʿ��Ϣ
    for (int i = 1; i <= m; i++) {
        cin >> attack[i] >> first[i];
    }
    compute();
    for (int i = 1; i <= n; i++) {
        cout << sacrifice[i] << "\n";
    }
    for (int i = 1; i <= m; i++) {
        //��¼���˵ĳ���
        cout << deep[first[i]] - deep[die[i]] << endl;
    }
    return 0;
}
