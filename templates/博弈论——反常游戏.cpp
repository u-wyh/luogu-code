// ����ķ����(������Ϸ)
// һ����n��ʯͷ����������������Ϸ
// ��ÿ����ҵĻغ��У������Ҫѡ���κ�һ���ǿյ�ʯͷ�ѣ��������ʯͷ���Ƴ�����������ʯͷ����
// ˭����������ʯͷ��ʧ�ܣ���������˭���ʤ
// ���ֻ�ʤ����ӡJohn
// ���ֻ�ʤ����ӡBrother
// �������� : https://www.luogu.com.cn/problem/P4279
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 51;

vector<int> stones(MAXN);

int t, n;

string compute() {
    int eor = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        eor ^= stones[i];
        sum += stones[i] == 1 ? 1 : 0;
    }
    if (sum == n) {
        return (n & 1) == 1 ? "Brother" : "John";
    } else {
        return eor != 0 ? "John" : "Brother";
    }
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> stones[j];
        }
        cout << compute() << endl;
    }
    return 0;
}
