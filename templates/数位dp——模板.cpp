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

// offset�Ǹ�����������ȫ��len������ֻ��Ϊ�˷�����ȡn��ĳһλ���֣����ǹؼ�����
// ��ʣ��lenλû�о���
// ���֮ǰ��λ�Ѿ�ȷ����nС����ôfree == 1����ʾ���µ����ֿ�������ѡ��
// ���֮ǰ��λ��nһ������ôfree == 0����ʾ���µ����ֲ��ܴ���num��ǰλ������
// ���֮ǰ��λû��ʹ�ù����֣�fix == 0
// ���֮ǰ��λ�Ѿ�ʹ�ù����֣�fix == 1
// ��������<=num�Ŀ������ж�����
int f1(int offset, int len, int free, int fix) {
	if (len == 0) {
		return fix == 1 ? 1 : 0;
	}
	int ans = 0;
	// num�ڵ�ǰλ������
	int cur = (n / offset) % 10;
	if (fix == 0) {
		// ֮ǰ����û��ѡ�������
		// ��ǰ��Ȼ���Բ�Ҫ�κ����֣��ۼӺ����Ŀ�����
		ans += f1(offset / 10, len - 1, 1, 0);
	}
	if (free == 0) {
		// ��������ѡ������
		for (int i : digits) {
			if (i < cur) {
				ans += f1(offset / 10, len - 1, 1, 1);
			} else if (i == cur) {
				ans += f1(offset / 10, len - 1, 0, 1);
			} else {
				// i > cur
				break;
			}
		}
	} else {
		// ��������ѡ������
		ans += m * f1( offset / 10, len - 1, 1, 1);
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
    cout<<f1(offset, len, 0, 0)<<endl;
    return 0;
}
