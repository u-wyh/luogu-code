// �����˵��ƶ�����
// ��ά������ֻ��x��y��ֵ��Ϊ���������꣬�Žи��
// ĳ�������˴Ӹ��(0,0)������ÿ�λ����˶���ֱ�ߵ���(x + dx, y + dy)�ĸ��
// һ���ƶ�n�Σ�ÿ�ε�(dx, dy)��������;��·�߲��ύ�棬���뱣֤���������ջص�(0,0)
// �������ߵ�·����Χ�ɵ�����һ���Ƕ���Σ����뱣֤������һ��������ʱ�뷽���ж�
// ���ض���ε��ڲ�һ��������㣬����εı���һ��������㣬����ε����
// 3 <= n <= 100
// -100 <= dx��dy <= 100
// �������� : http://poj.org/problem?id=1265
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;

long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int cases;
    cin>>cases;
    for (int t = 1; t <= cases; t++) {
        int n;
        cin>>n;
        int edges = 0;
        double area = 0;
        for (int i = 1, x = 0, y = 0, dx, dy; i <= n; i++) {
            cin>>dx>>dy;
            edges += gcd(abs(dx), abs(dy));
            // ��ʱ�뷽��ת����Ь����ʽ
            area += x * (y + dy) - (x + dx) * y;
            x += dx;
            y += dy;
        }
        // Ь����ʽ���Ҫ/2
        area /= 2;
        // pick����
        // �������� = �߽��ϸ����/2 + �ڲ������ - 1
        // �ڲ������ = �������� - �߽��ϸ����/2 + 1
        int inners = (int) (area) - edges / 2 + 1;
        cout<<"Scenario #" << t << ":"<<endl<<inners << " "<<edges << " ";
        printf("%.1f\n", area);
    }
    return 0;
}
