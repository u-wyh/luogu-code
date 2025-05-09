//�߶���  P4344
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// ��ȡ����
template<typename T>
inline void read(T &FF) {
    T RR = 1; FF = 0; char CH = cin.get();
    for (; !isdigit(CH); CH = cin.get()) if (CH == '-') RR = -1;
    for (; isdigit(CH); CH = cin.get()) FF = (FF << 1) + (FF << 3) + (CH ^ 48);
    FF *= RR;
}

// д������
template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x *= -1;
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}

// д������������
template<typename T>
inline void writen(T x) {
    write(x);
    puts("");
}

const int N = 2e5 + 10;

// �߶����ṹ��
struct Tree {
    int left, right, leftMax, rightMax, sum, tag, length, answer;
};

// �߶�������
vector<Tree> t(N * 4);

// ��ȡ�������
int n, m, l0, r0, l1, r1, f;

// ���µ�ǰ�ڵ����Ϣ
void pushUp(int num) {
    t[num].sum = t[num * 2].sum + t[num * 2 + 1].sum;
    if (t[num * 2].leftMax == t[num * 2].length)
        t[num].leftMax = t[num * 2].length + t[num * 2 + 1].leftMax;
    else
        t[num].leftMax = t[num * 2].leftMax;
    if (t[num * 2 + 1].rightMax == t[num * 2 + 1].length)
        t[num].rightMax = t[num * 2 + 1].length + t[num * 2].rightMax;
    else
        t[num].rightMax = t[num * 2 + 1].rightMax;
    t[num].answer = max(max(t[num * 2].answer, t[num * 2 + 1].answer), t[num * 2].rightMax + t[num * 2 + 1].leftMax);
}

// ���ڵ���Ϊȫ1   ����������������Ӧ��ȫ����Ϊ0
//��ס��
void down1(int num) {
    t[num].answer = t[num].leftMax = t[num].rightMax = t[num].length;
    t[num].sum = 0;
    t[num].tag = 1;
}

// ���ڵ���Ϊȫ2   ����������������Ӧ��ȫ����Ϊ1
//��ס��
void down2(int num) {
    t[num].answer = t[num].leftMax = t[num].rightMax = 0;
    t[num].sum = t[num].length;
    t[num].tag = 2;
}

// ���Ʊ��
void pushDown(int num) {
    if (t[num].tag == 1) {
        down1(num * 2);
        down1(num * 2 + 1);
        t[num].tag = 0;
    }
    if (t[num].tag == 2) {
        down2(num * 2);
        down2(num * 2 + 1);
        t[num].tag = 0;
    }
    //ÿ��ֻ���¸���һ��
}

// �����߶���
void build(int num, int left, int right) {
    t[num].tag = 0;
    t[num].left = left;
    t[num].right = right;
    t[num].length = right - left + 1;
    if (left == right) {
        t[num].sum = 1;
        t[num].answer = t[num].leftMax = t[num].rightMax = 0;
        return;
    }
    int mid = (left + right) / 2;
    build(num * 2, left, mid);
    build(num * 2 + 1, mid + 1, right);
    pushUp(num);
}

// �޸�����  ��xy��������ֽ����޸�  ����z��ָʾ�޸�
void change(int num, int x, int y, int z) {
    if (t[num].left >= x && t[num].right <= y) {
        if (z == 1)
            down1(num);//��ס
        if (z == 2)
            down2(num);//��ס
        return;
    }
    pushDown(num);
    if (t[num * 2].right >= x)
        change(num * 2, x, y, z);
    if (t[num * 2 + 1].left <= y)
        change(num * 2 + 1, x, y, z);
    //�����ǰ����û������Ҫ��  ��ô���´���  Ȼ�����ϻ���
    pushUp(num);
}

// ��ѯ����1������
int query0(int num, int x, int y) {
    if (t[num].left >= x && t[num].right <= y)
        return t[num].sum;
    pushDown(num);
    if (t[num * 2].right < x)
        return query0(num * 2 + 1, x, y);
    if (t[num * 2 + 1].left > y)
        return query0(num * 2, x, y);
    return query0(num * 2, x, y) + query0(num * 2 + 1, x, y);
}

// ��ѯ����0������
int query1(int num, int x, int y) {
    if (t[num].left >= x && t[num].right <= y)
        return t[num].length - t[num].sum;
    pushDown(num);
    if (t[num * 2].right < x)
        return query1(num * 2 + 1, x, y);
    if (t[num * 2 + 1].left > y)
        return query1(num * 2, x, y);
    return query1(num * 2, x, y) + query1(num * 2 + 1, x, y);
}

// ִ�в���1
void performOperation1() {
    read(l1);
    read(r1);
    int x = query0(1, l0, r0);
    if (x == 0)
        return;
    change(1, l0, r0, 1);
    //������������������ȫ����Ϊ0
    int left = l1, right = r1 + 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (query1(1, l1, mid) <= x)
            left = mid;
        else
            right = mid;
    }
    //ͨ���������ж��ĸ������ǿ��������
    //��ôֱ�ӽ���������޸�Ϊ1
    change(1, l1, left, 2);
}

// ��ѯ�����������0�ĳ���
int query2(int num, int x, int y) {
    if (t[num].left >= x && t[num].right <= y)
        //��������  ֱ�ӷ��ش�
        return t[num].answer;
    pushDown(num);
    //������  ����Ϣ���´���
    if (t[num * 2].right < x)
        //����ӵ��ұ߽�û������  ֱ��ȥ�Ҷ��Ӿͺ�
        return query2(num * 2 + 1, x, y);
    if (t[num * 2 + 1].left > y)
        //�Ҷ��ӵ���߽�û������  ֱ��ȥ����Ӿͺ�
        return query2(num * 2, x, y);
    return max(max(query2(num * 2, x, y), query2(num * 2 + 1, x, y)),
               min(t[num * 2].rightMax, t[num * 2 + 1].left - x) + min(t[num * 2 + 1].leftMax, y - t[num * 2].right));
               //�����min��ʾ  Ҫô�����leftmax����rightmax  Ҫô�����ҵ�����xy  ������ȡ��Сֵ����  ��ʾ���Ҷ��ӽ��紦Ѱ�Ҵ�
               //�������ʽ�ӱ�ʾ����
               //Ҫôֱ�Ӿ�������ӵĲ������ұ߽������Ǵ�
               //Ҫô���Ҷ��Ӳ�������߽��Ǵ�
               //Ҫô�����������ӵĽ��紦�Ǵ� Ҳ����min���ʽ��
}

int main() {
    read(n);
    read(m);
    build(1, 1, n);
    while (m--) {
        read(f),read(l0),read(r0);
        switch (f) {
            case 0:
                change(1, l0, r0, 1);
                break;
            case 1:
                performOperation1();
                break;
            case 2:
                writen(query2(1, l0, r0));
                break;
        }
    }
    return 0;
}
