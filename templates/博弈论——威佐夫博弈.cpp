// ��������(Wythoff Game)
// ������ʯ�ӣ��������⣬���Բ�ͬ����Ϸ��ʼ������������ȡʯ��
// ��Ϸ�涨��ÿ�������ֲ�ͬ��ȡ��
// 1) �������һ����ȡ��������ʯ��
// 2) ������������ͬʱȡ����ͬ������ʯ��
// ����ʯ��ȫ��ȡ����Ϊʤ��
// ���ڸ�����ʼ������ʯ�ӵ���Ŀ�����������ܲ��ܻ�ʤ
// �������� : https://www.luogu.com.cn/problem/P2252
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// �ƽ�ָ����
const long double split = 1.61803398874989484L;

int a, b;

int compute() {
    int minVal = min(a, b);
    int maxVal = max(a, b);
    // ��������
    // С != (�� - С) * �ƽ�ָ����������Ӯ
    // С == (�� - С) * �ƽ�ָ����������Ӯ
    // ����ȡ��
    if (minVal != static_cast<int>((maxVal - minVal) * split)) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    while (cin >> a >> b) {
        cout << compute() << endl;
    }
    return 0;
}
