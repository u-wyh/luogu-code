// ��С��������·��
// ��׼���μ�һ��Զ��������һ����ά rows x columns �ĵ�ͼ heights
// ���� heights[row][col] ��ʾ���� (row, col) �ĸ߶�
// һ��ʼ���������Ͻǵĸ��� (0, 0) ������ϣ��ȥ�����½ǵĸ��� (rows-1, columns-1)
// ��ע���±�� 0 ��ʼ��ţ�����ÿ�ο����� �ϣ��£����� �ĸ�����֮һ�ƶ�
// ����Ҫ�ҵ��ķ� ���� ��С��һ��·��
// һ��·���ķѵ�����ֵ��·���ϣ����ڸ���֮��߶Ȳ����ֵ�����ֵ
// ���㷵�ش����Ͻ��ߵ����½ǵ���С ��������ֵ
// �������� ��https://leetcode.cn/problems/path-with-minimum-effort/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 105;

struct Range {
    int i,j,val;
};
// �ȽϺ���������С���ѣ��� l ֵ���ʱ������ͨ����Ӷ���ıȽ��������ȶ���
bool compare(const Range& a, const Range& b) {
    return a.val > b.val; // ע�������Ǵ��ںţ���Ϊ����Ҫʹ�� greater<> �����С����
}
priority_queue<Range, vector<Range>, decltype(&compare)> heap(compare);

int n,m;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int height[MAXN][MAXM];
//��¼�����ط��ĺ���
int dis[MAXN][MAXM];
//��¼�ӿ�ʼ����Ŀǰ�������С�����߶Ȳ�
bool visit[MAXN][MAXM];
//��¼������Ƿ񱻷���

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>height[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dis[i][j]=INT_MAX;
        }
    }
    //��ʼ��

    dis[0][0]=0;
    heap.push({0,0,0});
    while(!heap.empty()){
        Range u=heap.top();
        heap.pop();
        int x=u.i;
        int y=u.j;
        int c=u.val;
        if(visit[x][y]){
            continue;
        }
        visit[x][y]=true;
        if(x==n-1&&y==m-1){
            cout<<c;
            return 0;
        }
        //�������Ŀ��ֱ�ӵ���
        for (int i = 0; i < 4; i++) {
            int nx = x + walk[i][0];
            int ny = y + walk[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visit[nx][ny]) {
                int nc = max(c,abs(height[x][y] - height[nx][ny]));
                if (nc < dis[nx][ny]) {
                    dis[nx][ny] = nc;
                    heap.push( { nx, ny, nc });
                }
            }
        }
    }
    return 0;
}
