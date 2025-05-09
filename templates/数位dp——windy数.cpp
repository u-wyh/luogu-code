// windy��
// ����ǰ������������������֮������Ϊ2������������Ϊwindy��
// windy��֪��[a,b]��Χ���ܹ��ж��ٸ�windy��
// �������� : https://www.luogu.com.cn/problem/P2657
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;

int a,b;
int dp[11][11][2];

void build(int len) {
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= 10; j++) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
}

// offset��ȫ��len������Ϊ�˷�����ȡnum��ĳһλ���֣��Ͻڿ����ݣ�
// ��num�ĸ�λ��ʼ����ʣ��lenλû�о���
// ǰһλ��������pre�����pre == 10����ʾ����û��ѡ�������
// ���֮ǰ��λ�Ѿ�ȷ����numС����ôfree == 1����ʾ���µ����ֿ�������ѡ��
// ���֮ǰ��λ��numһ������ôfree == 0����ʾ���µ����ֲ��ܴ���num��ǰλ������
// ����<=num��windy���ж��ٸ�
int f(int num, int offset, int len, int pre, int free) {
    if (len == 0) {
        return 1;
    }
    if (dp[len][pre][free] != -1) {
        return dp[len][pre][free];
    }
    int cur = num / offset % 10;
    int ans = 0;
    if (free == 0) {
        if (pre == 10) {
            // �ͱ�ʾ�������������λ������λ�ö�û����������
            ans += f(num, offset / 10, len - 1, 10, 1); // һ������Ҳ��Ҫ
            for (int i = 1; i < cur; i++) {
                ans += f(num, offset / 10, len - 1, i, 1);
                //���ϵ����ȵ�ǰ������С
            }
            ans += f(num, offset / 10, len - 1, cur, 0);
            //���ϵ������ڵ�ǰ������
        } else {
            // ֮ǰ��λ��numһ������ʱ��������ѡ�����֣�
            // ֮ǰѡ�������pre
            for (int i = 0; i <= 9; i++) {
                if (i <= pre - 2 || i >= pre + 2) {
                    if (i < cur) {
                        //���ϵ����ȵ�ǰ������С
                        ans += f(num, offset / 10, len - 1, i, 1);
                    } else if (i == cur) {
                        //���ϵ������ڵ�ǰ������
                        ans += f(num, offset / 10, len - 1, cur, 0);
                    }
                }
            }
        }
    } else {
        if (pre == 10) {
            // free == 1����������ѡ�����֣�ǰ���״�� < num
            // ����û��ѡ�������
            ans += f(num, offset / 10, len - 1, 10, 1); // ���ǿ��Բ�ѡ������
            for (int i = 1; i <= 9; i++) {
                ans += f(num, offset / 10, len - 1, i, 1);
                //����ѡ������
            }
        } else {
            // free == 1����������ѡ�����֣�ǰ���״�� < num
            // �Ѿ�ѡ�������pre
            for (int i = 0; i <= 9; i++) {
                if (i <= pre - 2 || i >= pre + 2) {
                    ans += f(num, offset / 10, len - 1, i, 1);
                }
            }
        }
    }
    dp[len][pre][free] = ans;
    return ans;
}


int cnt(int num){
    if(num==0){
        return 1;
    }
    int len = 1;
    int offset = 1;
    int tmp = num / 10;
    while (tmp > 0) {
        len++;
        offset *= 10;
        tmp /= 10;
    }
    build(len);
    //��ʼ��dp��
    return f(num,offset,len,10, 0);
}

int main()
{
    cin>>a>>b;
    cout<<cnt(b)-cnt(a-1)<<endl;
    return 0;
}
