#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300005

typedef long long ll;

int a[MAX_N];
ll ans;

// ʹ�ýṹ��ģ��map
typedef struct {
    int key;
    int value;
    struct Node* next;
} Node;

Node* head[MAX_N];

// �����ֵ�Ե�ģ���map��
void insert(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = head[key];
    head[key] = newNode;
}

// ��ģ���map�л�ȡֵ
int get(int key) {
    Node* current = head[key];
    if (current == NULL) return 0;
    int value = current->value;
    // �����Ҫɾ��������Խ�current->next����head[key]
    // ����������ֻ��Ҫ��ȡֵ���������ﲻɾ��
    return value;
}

// ���ģ���map�е�ĳ��������ѡ�������Ҫ�ظ�ʹ�ã�
void clear(int key) {
    Node* prev = NULL;
    Node* current = head[key];
    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }
    head[key] = NULL;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        insert(a[i], 1);  // ��ʼ����Ϊ1
    }

    // ����C���Բ�֧��ֱ�Ӷ���������ĺ���������ʡ�������裬
    // ���������Ѿ�������ģ��������ǿ���ʹ��qsort�Ⱥ�����������
    // qsort(a, n, sizeof(int), compare); // ��Ҫ����compare����

    // ����a�Ѿ�������ģ�����ִ�к����߼�
    for (int i = 0; i < n; i++) {
        ll tmp = a[i], cnt = 0;
        int value = get(tmp);
        while (value > 0) {
            cnt += tmp * value;
            value--;  // �൱��mp[tmp]--
            if (tmp % 2 == 0) tmp = tmp / 2 * 3;
            else break;
        }
        // �������ǵ�ģ��map��֧��һ���������ֵ�����ﲻֱ�����
        // �������Ҫ�ٴ�ʹ�ã��������ⲿ����clear����
        ans = (ans > cnt) ? ans : cnt;
    }

    printf("%lld\n", ans);

    // ����ģ��map�������Ҫ��
    // ע�⣺����Ϊ�˼������û��ʵ�������߼�

    return 0;
}
