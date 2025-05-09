// �ڱ����
// ����һ��n * m�Ķ�ά����grid�����е�1������԰ڷ��ڱ���0�������԰ڷ�
// �κ��ڱ�������Χ��һ��"ʮ����"�����򣬾��������������������ӵ�����
// ���Ŀ������gird��ھ�������ڱ�����Ҫ��֤�κ������ڱ�֮���޷����๥��
// ��������ܰڼ����ڱ�
// 1 <= n <= 100
// 1 <= m <= 10
// 0 <= grid[i][j] <= 1
// �������� : https://www.luogu.com.cn/problem/P2704
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//����Ԥ����ʽ�Ǽ��ٲ���Ҫ�����ö�� ֻö�ٿ��ܶԴ��й��׵�״̬
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;
const int MAXM = 10;
const int MAXS = 60;

int grid[MAXN][MAXM];
int dp[MAXN][MAXS][MAXS];//dp[i][j][k]��ʾ���ǵ�i�У���0��ʼ����״̬��sta[j] ��һ�е�״̬��sta[k]�����������������Ƕ���
int sta[MAXS];//sta����洢���Ƕ���һ�ж��� ���е���Ч״̬
int n, m, k;

void prepare(int j, int s) {
    if (j >= m) {
        sta[k++] = s;
    } else {
        prepare(j + 1, s);//��ʾ���λ�ò���  ȥ��һ��λ�ü���
        prepare(j + 3, s | (1 << j));//��ʾ���λ�÷� ȥ������λ�ü���
    }
}

// ��i��ʿ��״̬Ϊs�����grid��i�ŵ�״��
// ���ذڷ�ʿ��������
int onecnt(int i, int s) {
	int ans = 0;
	for (int j = 0; j < m; j++) {
		if (((s >> j) & 1) == 1 && grid[i][j] == 1) {
			ans++;
		}
	}
	return ans;
}

int main()
{
    cin>>n>>m;
    k=0;//��¼���Ƕ���һ�ж��� ��Ч״̬������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin>>c;
            grid[i][j] = c == 'H' ? 0 : 1;
        }
    }
    prepare(0,0);
    for (int a = 0, cnt; a < k; a++) {
        cnt = onecnt(0, sta[a]);
        dp[0][a][0] = cnt;
    }
    for (int i = 1; i < n; i++) {
        for (int a = 0, cnt; a < k; a++) {
            cnt = onecnt(i, sta[a]);//��ʾ��һ�����״̬��sta[a]  ʵ�ʿ��ԷŶ��ٸ�
            for (int b = 0; b < k; b++) {
                if ((sta[a] & sta[b]) == 0) {
                    //����Ҫ�����һ�в��ܳ�ͻ  ��Ȼ����ʵ�����ǲ���ͻ��  ���ǲ���ͻ�����Ҳ���Ա�������״̬����  ��ô�Ҿ�û�б�Ҫ������
                    for (int c = 0; c < k; c++) {
                        if ((sta[b] & sta[c]) == 0 && (sta[a] & sta[c]) == 0) {
                            dp[i][a][b] = max(dp[i][a][b], dp[i - 1][b][c] + cnt);
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int a = 0; a < k; a++) {
        for (int b = 0; b < k; b++) {
            ans = max(ans, dp[n - 1][a][b]);
        }
    }
    cout<<ans;
    return 0;
}
