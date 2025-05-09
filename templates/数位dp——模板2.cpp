// ���ΪN���������
// ����һ���� �ǵݼ�˳�� ���е��������� digits
// ��֪digitsһ��������'0'�����ܰ���'1' ~ '9'�������ظ��ַ�
// �������������� digits[i] ��д������
// ���磬��� digits = ['1','3','5']
// ���ǿ���д���֣��� '13', '551', �� '1351315'
// ���� �������ɵ�С�ڻ���ڸ������� n ���������ĸ���
// �������� : https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/
#include<bits/stdc++.h>
using namespace std;

int n,m;//��ʾ����ܴ���n  һ����m����λ��ѡ��
int digits[10];//��ʾ����ʹ�õ�����
int cnt[15];//��������򻯵ݹ����

// offset�Ǹ�����������lenȷ����������ȡnum��ĳһλ����
// ��ʣ��lenλû�о�����֮ǰ��λ��numһ��
// ��������<=num�Ŀ������ж�����
int f2(int offset, int len) {
	if (len == 0) {
		// num�Լ�
		return 1;
	}
	// cur��num��ǰλ������
	int cur = (n / offset) % 10;
	int ans = 0;
	for (int i : digits) {
		if (i < cur) {
			ans += cnt[len - 1];
		} else if (i == cur) {
			ans += f2(offset / 10, len - 1);
		} else {
			break;
		}
	}
	return ans;
}

int main()
{
    cin>>n>>m;
    int tmp = n/ 10;
    int len = 1;//���ڲⶨn�ĳ���
    int offset = 1;//���ʵ������10��len-1�η�
    while (tmp > 0) {
        tmp /= 10;
        len++;
        offset *= 10;
    }
    for(int i=0;i<m;i++){
        cin>>digits[i];
    }
    // cnt[i] : ��֪ǰ׺��numС��ʣ��iλû��ȷ��������ǰ׺ȷ��������£�һ���ж�������������
    // cnt[0] = 1����ʾ�����Ѿ�û���ˣ�ǰ׺��״������ȷ������ô����1��
    // cnt[1] = m
    // cnt[2] = m * m
    // cnt[3] = m * m * m
    // ...
    cnt[0] = 1;
    int ans = 0;
    for (int i = m, k = 1; k < len; k++, i *= m) {
        cnt[k] = i;
        ans += i;//kС��len����������ط��ӵĶ�����λ����len�ģ�һ����nС
    }
    ans += f2(offset, len);//����f2���ÿ��ǲ�������ֵ��ˣ���Ϊ������λ�����������Ѿ����������
    cout<<ans<<endl;
    return 0;
}
