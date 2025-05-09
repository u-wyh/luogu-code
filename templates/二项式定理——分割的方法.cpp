// �ָ�ķ�����
// ����һ������Ϊn������A, ����ָ������B������C������A[i] = B[i] + C[i]
// Ҳ����һ�����ֳַ����ݣ�Ȼ����Խ���B��C��Ҫ��B[i], C[i] >= 1
// ͬʱҪ��B��������Ҳ��ܽ���C��������Ҳ�������
// ���磬A = { 5, 4, 5 }��һ����Ч�Ļ��֣�B = { 2, 2, 3 }��C = { 3, 2, 2 }
// �����ж�������Ч�Ļ��ַ�ʽ
// 1 <= n <= 10^7
// 1 <= A[i] <= 10^7
// ���ս�����ܴܺ󣬴𰸶� 1000000007 ȡģ
// ������ʵ�󳧱����⣬��ʵ��Ϊ�������汾
// ��ͬѧ�ҵ��˲������ӣ�����Code04_SplitWays2�ļ�
#include<bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

// �˷�������
long long power(long long x, long long p) {
    long long ans = 1;
    while (p > 0) {
        if ((p & 1) == 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ans;
}

int f(const std::vector<int>& arr, int i, int preb, int prec) {
    if (i == arr.size()) {
        return 1;
    }
    int ans = 0;
    for (int b = 1, c = arr[i] - 1; b < arr[i]; ++b, --c) {
        if (preb <= b && prec >= c) {
            ans += f(arr, i + 1, b, c);
        }
    }
    return ans;
}

// ��Ϲ�ʽ
int c(int n, int k) {
    long long fac = 1;
    long long inv1 = 1;
    long long inv2 = 1;
    for (int i = 1; i <= n; ++i) {
        fac = (fac * i) % MOD;
        if (i == k) {
            inv1 = power(fac, MOD - 2); // ����С��������Ԫ
        }
        if (i == n - k) {
            inv2 = power(fac, MOD - 2); // ����С��������Ԫ
        }
    }
    return (int) ((((fac * inv1) % MOD) * inv2) % MOD);
}

// ��������
int ways1(const std::vector<int>& arr) {
    int ans = 0;
    for (int b = 1, c = arr[0] - 1; b < arr[0]; ++b, --c) {
        ans += f(arr, 1, b, c);
    }
    return ans;
}

// ��ʽ����
// ת�����������
int ways2(const std::vector<int>& arr) {
    int n = arr.size();
    int k = arr[0] - 1;
    for (int i = 1; i < n && k > 0; ++i) {
        if (arr[i - 1] > arr[i]) {
            k -= arr[i - 1] - arr[i];
        }
    }
    if (k <= 0) {
        return 0;
    }
    return c(k + n - 1, n);
}

// Ϊ�˲���
std::vector<int> randomArray(int n, int v) {
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = rand() % v + 1;
    }
    return ans;
}

// ���Ժ���
int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::cout << "���ܲ��Կ�ʼ" << std::endl;
    int N = 10;
    int V = 20;
    int test = 2000;
    for (int i = 0; i < test; ++i) {
        int n = rand() % N + 1;
        std::vector<int> arr = randomArray(n, V);
        int ans1 = ways1(arr);
        int ans2 = ways2(arr);
        if (ans1 != ans2) {
            std::cout << "������!" << std::endl;
        }
        else{
            cout<<"��"<<setw(5)<<i<<"�������ȷ��"<<endl;
        }
    }
    std::cout << "���ܲ��Խ���" << std::endl;

//    std::cout << "==========" << std::endl;
//
//    std::cout << "���ܲ��Կ�ʼ" << std::endl;
//    int n = 10000000;
//    int v = 10000000;
//    auto start, end;
//    std::vector<int> arr(n);
//
//    std::cout << "������ɵ����ݲ���" << std::endl;
//    std::cout << "���鳤�� : " << n << std::endl;
//    std::cout << "��ֵ��Χ : [" << 1 << "," << v << "]" << std::endl;
//    for (int i = 0; i < n; ++i) {
//        arr[i] = rand() % v + 1;
//    }
//    start = std::chrono::high_resolution_clock::now();
//    ways2(arr);
//    end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end - start;
//    std::cout << "����ʱ�� : " << elapsed_seconds.count() * 1000 << " ����" << std::endl;
//
//    std::cout << std::endl;
//
//    std::cout << "�������������ݲ���" << std::endl;
//    std::cout << "���鳤�� : " << n << std::endl;
//    std::cout << "��ֵ���� : " << v << std::endl;
//    std::cout << "���������ʵ�Ǹ��Ӷ���ߵ����" << std::endl;
//    for (int i = 0; i < n; ++i) {
//        arr[i] = v;
//    }
//    start = std::chrono::high_resolution_clock::now();
//    ways2(arr);
//    end = std::chrono::high_resolution_clock::now();
//    elapsed_seconds = end - start;
//    std::cout << "����ʱ�� : " << elapsed_seconds.count() * 1000 << " ����" << std::endl;
//    std::cout << "���ܲ��Խ���" << std::endl;

    return 0;
}
