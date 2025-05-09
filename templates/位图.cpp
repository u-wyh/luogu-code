#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

// λͼ��ʵ��
class Bitset {
public:
    std::vector<int> set;

    // n������ : 0~n-1
    Bitset(int n) {
        // a/b������������ȡ��������д�� : (a+b-1)/b
        // ǰ����a��b���ǷǸ���
        set.resize((n + 31) / 32);
    }

    void add(int num) {
        set[num / 32] |= 1 << (num % 32);
    }

    void remove(int num) {
        set[num / 32] &= ~(1 << (num % 32));
    }

    void reverse(int num) {
        set[num / 32] ^= 1 << (num % 32);
    }

    bool contains(int num) const {
        return ((set[num / 32] >> (num % 32)) & 1) == 1;
    }
};

// ����������
int main() {
    srand(time(0)); // ��ʼ�����������

    int n = 1000;
    int testTimes = 10000;
    std::cout << "���Կ�ʼ" << std::endl;

    // ʵ�ֵ�λͼ�ṹ
    Bitset bitSet(n);
    // ֱ����unordered_set���ԱȲ���
    std::unordered_set<int> hashSet;

    std::cout << "���ý׶ο�ʼ" << std::endl;
    for (int i = 0; i < testTimes; i++) {
        double decide = static_cast<double>(rand()) / RAND_MAX;
        // number -> 0 ~ n-1���ȸ��ʵõ�
        int number = rand() % n;
        if (decide < 0.333) {
            bitSet.add(number);
            hashSet.insert(number);
        } else if (decide < 0.666) {
            bitSet.remove(number);
            hashSet.erase(number);
        } else {
            bitSet.reverse(number);
            if (hashSet.find(number) != hashSet.end()) {
                hashSet.erase(number);
            } else {
                hashSet.insert(number);
            }
        }
    }
    std::cout << "���ý׶ν���" << std::endl;
    std::cout << "��֤�׶ο�ʼ" << std::endl;
    for (int i = 0; i < n; i++) {
        if (bitSet.contains(i) != (hashSet.find(i) != hashSet.end())) {
            std::cout << "������!" << std::endl;
            break; // ����ѡ����������ֹ���򣬻��߼����������Ԫ��
        }
        else{
            cout<<"��"<<setw(4)<<i<<"�������ȷ"<<endl;
        }
    }
    std::cout << "��֤�׶ν���" << std::endl;
    std::cout << "���Խ���" << std::endl;

    return 0;
}
