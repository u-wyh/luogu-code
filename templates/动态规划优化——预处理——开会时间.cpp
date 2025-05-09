// ��Ϣk�����������
// ����һ������Ϊn������arr����ʾ���絽�����Ļ��飬�����ٿ��ķ�����
// ��ѡ��һ�����鲢�μ�֮�󣬱�����Ϣk����
// �����ܲμӵĻ���ʱ������ۼӺ�
// ���磬arr = { 200, 5, 6, 14, 7, 300 }��k = 15
// ��õ�ѡ��Ϊ��ѡ��200���ӵĻ��飬Ȼ�������Ϣ15����
// ��ô��������5���ӡ�6���ӡ�14���ӵĻ���ע�����
// Ȼ�����7���ӵĻ��飬��ѡ��μ�300���ӵĻ���
// ���շ���500
// 1 <= n��arr[i]��k <= 10^6
// ������ʵ�󳧱��ԣ���������֤
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

// ������ö�ٵĿ�����
// ʱ�临�Ӷ�O(n^2)
long long best1(const vector<int>& arr, int k) {
    int n = arr.size();
    vector<long long> dp(n + 1, 0);
    for (int i = n - 1, j, sum = 0; i >= 0; i--) {
        for (j = i + 1, sum = 0; j < n && sum < k; j++) {
            sum += arr[j];
        }
        dp[i] = max(dp[i + 1], dp[j] + arr[i]);
    }
    return dp[0];
}

// ����Ԥ����ṹ����ö�ٵĿ�����
// ʱ�临�Ӷ�O(n)
long long best2(const vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> jump(n, 0);
    // ����[l...r)������ҿ���sum�Ǵ����ۼӺ�
    for (int i = 0, l = 1, r = 1, sum = 0; i < n - 1; i++, l++) {
        while (r < n && sum < k) {
            sum += arr[r++];
        }
        jump[i] = r;
        sum -= arr[l];
    }
    jump[n - 1] = n;
    vector<long long> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = max(dp[i + 1], dp[jump[i]] + arr[i]);
    }
    return dp[0];
}

// Ϊ�˲���
vector<int> randomArray(int n, int v) {
    vector<int> arr(n);
    srand(time(0));  // ��ʼ�����������
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % v + 1;
    }
    return arr;
}

// Ϊ�˲���
int main() {
    int n = 1000;
    int v = 3000;
    int testTime = 5000;
    cout << "���Կ�ʼ" << endl;
    for (int i = 1; i <= testTime; i++) {
        int size = rand() % n + 1;
        vector<int> arr = randomArray(size, v);
        int k = rand() % v + 1;
        long long ans1 = best1(arr, k);
        long long ans2 = best2(arr, k);
        if (ans1 != ans2) {
            cout << "������!" << endl;
        }else{
            cout<<"��"<<setw(5)<<i<<"�������ȷ��"<<endl;
        }
    }
    cout << "���Խ���" << endl;
    return 0;
}
