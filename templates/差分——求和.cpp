// ����Ʊ��������ͼ
// ����һ�� m * n �Ķ����ƾ��� grid
// ÿ������ҪôΪ 0 ���գ�ҪôΪ 1 ����ռ�ݣ�
// ������Ʊ�ĳߴ�Ϊ stampHeight * stampWidth
// �����뽫��Ʊ���������ƾ����У����������� ���� �� Ҫ�� ��
// �������пո��ӣ��������κα�ռ�ݵĸ���
// ���Է���������Ŀ����Ʊ����Ʊ�����໥���ص�����
// ��Ʊ��������ת����Ʊ������ȫ�ھ�����
// �������������Ҫ���ǰ���£����Է�����Ʊ���뷵�� true �����򷵻� false
// �������� : https://leetcode.cn/problems/stamping-the-grid/
#include<bits/stdc++.h>
using namespace std;

int m,n,h,w;
int arr[100][100],sum[100][100],nums[100][100];

int fun(int X1,int Y1,int X2,int Y2){
    return sum[X2][Y2]+sum[X1-1][Y1-1]-sum[X2][Y1-1]-sum[X1-1][Y2];
}

void Set(int a,int b,int c,int d,int v){
    nums[a][b]+=v;
    nums[a][d+1]-=v;
    nums[c+1][b]-=v;
    nums[c+1][d+1]+=v;
}

int main()
{
    cin>>n>>m>>h>>w;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+arr[i][j];
        }
    }

    for (int a = 1, c = a + h - 1; c <= n; a++, c++) {
        for (int b = 1, d = b + w - 1; d <= m; b++, d++) {
            // ԭʼ������ (a,b)���Ͻǵ�
            // ������Ʊ���h��w��������½ǵ�(c,d)
            // ������򳹵׶���0����ô:
            // sumRegion(sum, a, b, c, d) == 0
            // ��ô��ʱ��������������Ʊ
            if (fun(a,b,c,d)== 0) {
                Set(a, b, c, d,1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(arr[i][j]==0&&nums[i][j]==0){
                cout<<false;
                return 0;
            }
        }
    }
    cout<<true;
    return 0;
}
