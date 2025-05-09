#include <bits/stdc++.h>
using namespace std;

const int MARX = 2e5 + 10;
const int INF = 2e9;

int N, L, R, A[MARX], ans, f[MARX];//�� f[i]: ����λ�� i ʱ���ļ�ֵ��
int que[MARX], head = 1, tail = 1;//��������, �ڲ�Ԫ��Ϊλ��

inline int read(){
    int s = 1, w = 0; char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') s = -1;
    for(; isdigit(ch); ch = getchar()) w = (w << 1) + (w << 3) + (ch ^ '0');
    return s * w;
}

void Insert(int i){
	while(f[i] >= f[que[tail]] && tail >= head)
        tail --;//����Ȩֵ�ͽ�С�� ��βԪ��
	que[++ tail] = i;//���
}

int query(int x){
	for(; que[head] + R < x; ) head ++;//�������� ���ɵ���xλ�õ� ���Ϸ�Ԫ��
	return que[head];//�ش�ѯ��
}

int main()
{
	memset(f, 128, sizeof(f));//��ʼ����Сֵ (ÿ���ֽڸ�128�ᵼ����Ȼ���
	f[0] = 0, ans = - INF; //��ʼ��, ��0λ��Ȩֵ�� ��Ϊ0
	N = read(), L = read(), R = read();
	for(int i = 0; i <= N; i ++) A[i] = read();

	for(int i = L; i <= N; i ++){
	  Insert(i - L); //�����һ�� �ܹ�ת�Ƶ�i��λ�� ���뵥������
	  int from = query(i);//�ҵ����� Ȩֵ������λ��
	  f[i] = f[from] + A[i];//����ת��
	  if(i + R > N)
            ans = max(ans, f[i]);//�ж�i�ܹ������԰�, �����
	}
	printf("%d", ans);
	return 0;
}
