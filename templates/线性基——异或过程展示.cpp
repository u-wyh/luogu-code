#include<bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int BIT = 60;

int n;
vector<long long> arr(MAXN);
vector<long long> basis1(BIT + 1, 0);
bool zero1 = false;

//��������ͨ��Ԫ�����Ǹ�˹��Ԫ��  ֻҪ������������Ŀ��ԭ������Ŀ��һ����  һ������0
//��ͨ��Ԫ���õ������Ի�  ���Ǳ�׼��
//��˹��Ԫ�õ������Ի�  ���Ǳ�׼��
//��׼�� ��˼�����������ֵ�ĳһλ����1  ��ôֻ��һ��������Ԫ  ʣ�µ�ȫ��������Ԫ

//��ͨ��Ԫ��  �ǽ����ֵĶ�����λ�Ƿ���1  ���в�������
//�ӵ�һ�����ֿ�ʼ  �Ӷ��������λ��ʼ
//�����һλ���������� ��ô��Ҫ������������  Ȼ��ȥ��һλ�Ƚ�
//���û������  ��ô������ֲ嵽����ȥ
//Ȼ�����ԭʼ�����ܲ�������0����

// ���Ի������num��������Ի������˷���true�����򷵻�false
// ��������ж��Ƿ���0  ��Ȼ ������Ҳ����  ���Ƚ����������Ԫ�ظ���Ҳ��һ����
bool insert(long long num) {
    for (int i = BIT; i >= 0; i--) {
        if (num >> i & 1) {
            //��ʾ����������λ������1
            if (basis1[i] == 0) {
                //������Ի����λ����û������ ��ôֱ�Ӳ���
                basis1[i] = num;
                return true;
            }
            num ^= basis1[i];
        }
    }
    return false;
}

void compute1() {
    zero1 = false;
    for (int i = 1; i <= n; i++) {
        if (!insert(arr[i])) {
            zero1 = true;
            //����һ������  ���Ի�����û������һ��  ˵��һ���Ǳ���ǰ�����Ϊ0��  ��ôһ����0
        }
    }
}

//��˹��Ԫ
// ��Ϊ����Ҫά����Ԫ������Ԫ��������ϵ
// ���Ը�˹��Ԫ��д�����Եõ���
// ֻ��û����Ԫ���ҵ�ǰ������Ҫ����Ҫ��1����  Ҫ��������ǰ��
vector<long long> basis2(MAXN, 0);
int len = 1;
bool zero2 = false;

void swap(int a, int b) {
    long long tmp = basis2[a];
    basis2[a] = basis2[b];
    basis2[b] = tmp;
}

void compute2() {
    len = 1;//��ʾ�Ѿ���õ�λ��
    for (int i = BIT; i >= 0; i--) {
        //�����λ��ʼö��
        for (int j = len; j <= n; j++) {
            if (basis2[j] & (1LL << i)) {
                //�ҵ�һ�����λ������1 ������
                swap(j, len);//����������һ��
                break;
            }
        }
        if (basis2[len] & (1LL << i)) {
            //��ʾ�����λ����1 ��ô�����������λ����1��ȫ������
            for (int j = 1; j <= n; j++) {
                if (j != len && (basis2[j] & (1LL << i))) {
                    basis2[j] ^= basis2[len];
                }
            }
            len++;
        }
    }
    len--;
    zero2 = len != n;
}

void dfs(const vector<long long>& nums, int n, int i, bool pick, long long path, unordered_set<long long>& set) {
    if (i > n) {
        if (pick) {
            set.insert(path);
        }
    } else {
        dfs(nums, n, i + 1, pick, path, set);
        dfs(nums, n, i + 1, true, path ^ nums[i], set);
    }
}

void printXorResults(const vector<long long>& nums, int n) {
    unordered_set<long long> set;
    dfs(nums, n, 1, false, 0, set);

    // ��unordered_setת��Ϊvector
    vector<long long> sortedResults(set.begin(), set.end());

    // �Խ����������
    sort(sortedResults.begin(), sortedResults.end());

    cout << "����ѡ��һ���������п��ܵ�����:" << endl;
    for (long long s : sortedResults) {
        cout << s << ", ";
    }
    cout << endl;
}

void showDetails() {
    // ����1
    cout << "����1" << endl;
    fill(basis1.begin(), basis1.end(), 0);
    arr[1] = 12;
    arr[2] = 9;
    arr[3] = 14;
    arr[4] = 11;
    n = 4;
    cout << "ԭʼ����õ������������" << endl;
    printXorResults(arr, n);

    cout << "===========================" << endl;
    cout << "��ͨ��Ԫ�õ������Ի� : " << endl;
    compute1();
    vector<long long> b1(MAXN, 0);
    int s1 = 0;
    for (int i = BIT; i >= 0; i--) {
        if (basis1[i] != 0) {
            cout << basis1[i] << " ";
            b1[++s1] = basis1[i];
        }
    }
    cout << endl;
    cout << "�Ƿ�������0 : " << (zero1 ? "true" : "false") << endl;
    cout << "��ͨ��Ԫ�õ������������" << endl;
    printXorResults(b1, s1);
    cout << "===========================" << endl << endl;

    // ����2
    cout << "����2" << endl;
    fill(basis1.begin(), basis1.end(), 0);
    arr[1] = 2;
    arr[2] = 5;
    arr[3] = 11;
    arr[4] = 6;
    n = 4;
    cout << "ԭʼ����õ������������" << endl;
    printXorResults(arr, n);
    cout << "===========================" << endl;
    cout << "��ͨ��Ԫ�õ������Ի� : " << endl;
    compute1();
    vector<long long> b2(MAXN, 0);
    int s2 = 0;
    for (int i = BIT; i >= 0; i--) {
        if (basis1[i] != 0) {
            cout << basis1[i] << " ";
            b2[++s2] = basis1[i];
        }
    }
    cout << endl;
    cout << "�Ƿ�������0 : " << (zero1 ? "true" : "false") << endl;
    cout << "��ͨ��Ԫ�õ������������" << endl;
    printXorResults(b2, s2);
    cout << "===========================" << endl << endl;

    // ����3
    cout << "����3" << endl;
    fill(basis2.begin(), basis2.end(), 0);
    arr[1] = basis2[1] = 6;
    arr[2] = basis2[2] = 37;
    arr[3] = basis2[3] = 35;
    arr[4] = basis2[4] = 33;
    n = 4;
    cout << "ԭʼ����õ������������" << endl;
    printXorResults(arr, n);
    cout << "===========================" << endl;
    cout << "��˹��Ԫ�õ������Ի� : " << endl;
    compute2();
    for (int i = 1; i <= len; i++) {
        cout << basis2[i] << " ";
    }
    cout << endl;
    cout << "�Ƿ�������0 : " << (zero2 ? "true" : "false") << endl;
    cout << "��˹��Ԫ�õ������������" << endl;
    printXorResults(vector<long long>(basis2.begin(), basis2.begin() + len), len);
    cout << "===========================" << endl << endl;

    // ����4
    cout << "����4" << endl;
    fill(basis1.begin(), basis1.end(), 0);
    fill(basis2.begin(), basis2.end(), 0);
    arr[1] = basis2[1] = 7;
    arr[2] = basis2[2] = 10;
    arr[3] = basis2[3] = 4;
    n = 3;
    cout << "ԭʼ����õ������������" << endl;
    printXorResults(arr, n);
    cout << "===========================" << endl;
    cout << "��ͨ��Ԫ" << endl;
    compute1();
    for (int i = BIT; i >= 0; i--) {
        if (basis1[i] != 0) {
            cout << basis1[i] << " ";
        }
    }
    cout << endl;
    cout << "�Ƿ�������0 : " << (zero1 ? "true" : "false") << endl;

    cout << "===========================" << endl;

    cout << "��˹��Ԫ" << endl;
    compute2();
    for (int i = 1; i <= len; i++) {
        cout << basis2[i] << " ";
    }
    cout << endl;
    cout << "�Ƿ�������0 : " << (zero2 ? "true" : "false") << endl;
}

int main() {
    showDetails();
    return 0;
}
