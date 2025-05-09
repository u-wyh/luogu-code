// ��ά�����ϵ������ӡ���Χ��ѯ��ʹ����״�����ģ��
// �������� : https://leetcode.cn/problems/range-sum-query-2d-mutable/
#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[5005][5005],tree[5005][5005];
int materix[5005][5005];

int lowbit(int i) {
    return i & -i;
}

//��������(x,y)λ���ϵ����ּ���v
void add(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= m; j += lowbit(j)) {
            tree[i][j] += v;
        }
    }
}

//��������������Ǽ����(1,1)��(x,y)֮����ۼӺ�
int sum(int x, int y) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ans += tree[i][j];
        }
    }
    return ans;
}

//�������Ŀ��  ��Ŀ����˼�ǽ�(x,y)λ���ϵ����ֱ�Ϊv
//����ʵ�ȼ��ڽ����λ���ϵ����ּ��ϸĺ�����ּ�ȥ��ǰ������
//��ʵ������Ϊ�˽������ʱ������
void update(int x, int y, int v) {
    add(x + 1, y + 1, v - nums[x + 1][y + 1]);
    nums[x + 1][y + 1] = v;
}

// ʵ�ʶ�ά�����λ����(x,y)
// ��״�����ϵ�λ����(x+1, y+1)
int sumRegion(int a, int b, int c, int d) {
	return sum(c + 1, d + 1) - sum(a, d + 1) - sum(c + 1, b) + sum(a, b);
}

int main()
{
    cin>>n>>m;
    int materix[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>materix[i][j];
            update(i,j,materix[i][j]);
        }
    }

    //������������������������Ϻ����µ������ѯ����ֵ
    //��ȻҲ���Ե���update����add�����޸�ֵ
    return 0;
}
