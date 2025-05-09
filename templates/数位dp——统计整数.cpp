// ͳ��������Ŀ
// �������������ַ��� num1 �� num2 ���Լ���������max_sum��min_sum
// ���һ������ x �����������������ǳ�����һ��������
// num1 <= x <= num2
// min_sum <= digit_sum(x) <= max_sum
// ���㷵�غ���������Ŀ
// �𰸿��ܴܺ󣬴𰸶� 1000000007 ȡģ
// ע�⣬digit_sum(x)��ʾx��λ����֮��
// �������� : https://leetcode.cn/problems/count-of-integers/
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

string s1,s2;//���ַ�������ʽ����������Сֵ
int minsum,maxsum;//Ҫ�����λ��ֵ
int dp[25][400][2];//dp[i][j][k]��ʾ�ڵ�iλ��Ŀǰ����j������״̬Ϊk

int len;
char str[30];//������ȫ�ֱ������ں���֮�У����������лᱻ����

void build() {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j <= maxsum; j++) {
			dp[i][j][0] = -1;
			dp[i][j][1] = -1;
		}
	}
}

// ע�⣺
// ���֣�char[] num
// ���ֳ��ȣ�int len
// �ۼӺ���СҪ��int min
// �ۼӺ����Ҫ��int max
// ���ĸ���������ȫ�־�̬���������Բ��ô�������ֱ�ӷ��ʼ���
// �ݹ麬�壺
// ��num�ĸ�λ��������ǰ����iλ��
// ֮ǰ�����������ۼӺ���sum
// ֮ǰ�ľ����Ѿ���numС��������������ѡ�����֣���ôfree == 1
// ֮ǰ�ľ�����numһ������������������ѡ�����֣���ôfree == 0
// �����ж����ֿ�����
int f(int i, int sum, int free) {
	if (sum > maxsum) {
		return 0;
	}
	if (sum + (len - i) * 9 < minsum) {
		return 0;
	}
	if (i == len) {
		return 1;
	}
	if (dp[i][sum][free] != -1) {
		return dp[i][sum][free];
	}
	// cur : num��ǰλ������
	int cur = str[i] - '0';
	int ans = 0;
	if (free == 0) {
		// ����������ѡ��
		for (int pick = 0; pick < cur; pick++) {
			ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
		}
		ans = (ans + f(i + 1, sum + cur, 0)) % MOD;
	} else {
		// ��������ѡ��
		for (int pick = 0; pick <= 9; pick++) {
			ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
		}
	}
	dp[i][sum][free] = ans;
	return ans;
}

bool check() {
	int sum = 0;
	for (char cha : str) {
		sum += cha - '0';
	}
	return sum >= minsum && sum <= maxsum;
}

//���ȣ�����˼·�����0~max�ϵķ���Ҫ������ּ�ȥ0~min-1�ϵķ���Ҫ�������
//���ǣ����������ֺܳ�����ʹ��longҲ�����������ֱ�Ӽ�1Ҳ�Ƚ��鷳
//������Сֵ��100000000000000000000000000000000000  ��Ҫ�ֶ���Ϊ9
//�������ǵ�˼·�����0~max�ϵķ���Ҫ������ּ�ȥ0~min  ��min����
int main()
{
    cin>>s1>>s2>>minsum>>maxsum;

    copy(s1.begin(), s1.end(), str);
    str[s1.length()] = '\0';
    len=s1.length();
    build();
    int ans=f(0,0,0);//���0~max�ϵķ���Ҫ�������
    copy(s2.begin(), s2.end(), str);
    str[s2.length()] = '\0';
    len=s2.length();
    build();//���0~min�ϵķ���Ҫ�������
    if(check()){
        ans=(ans+1)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}
