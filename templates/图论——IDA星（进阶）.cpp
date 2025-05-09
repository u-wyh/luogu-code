//https://acm.hdu.edu.cn/showproblem.php?pid=1667
//https://www.cnblogs.com/LuckyGlass-blog/p/9061081.html
// mov[i][0]������������ת��һ�����У�
// mov[i][1]���൱��bool����Ϊ false�������ת�Ƶ���β��Ϊ true ���βת�Ƶ����ף�
// mov[i][2]������Ӱ��ĵ�һ�����б�ţ�
// mov[i][3]������Ӱ�쵽���� mov[i][2] �ĵڼ���Ԫ�أ�
// mov[i][4]������Ӱ�쵽�ĵ�һ�����е�Ԫ�ؽ��в�������Ϊ���� mov[i][0] �еĵڼ���Ԫ�أ�
// mov[i][5]������Ӱ��ĵڶ������б�ţ�
// mov[i][6]������Ӱ�쵽���� mov[i][5] �ĵڼ���Ԫ�أ�
// mov[i][7]������Ӱ�쵽�ĵڶ������е�Ԫ�ؽ��в�������Ϊ���� mov[i][0] �еĵڼ���Ԫ�أ�
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <deque>
using namespace std;

// ��������ת�����ƶ�����
const int initialPositions[][3] = {
    {1, 0}, {1, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 2}, {2, 0, 2}, {1, 2},
    {2, 1, 2}, {1, 2}, {1, 2}, {1, 0}, {1, 1}, {1, 3}, {1, 3}, {2, 0, 3},
    {1, 3}, {2, 1, 3}, {1, 3}, {1, 3}, {1, 0}, {1, 1}, {1, 0}, {1, 1}
};
const int movements[][8] = {
    {0, 0, 2, 2, 2, 3, 2, 4}, {1, 0, 2, 4, 2, 3, 4, 4}, {2, 1, 0, 2, 2, 1, 2, 4},
    {3, 1, 0, 4, 2, 1, 4, 4}, {1, 1, 2, 4, 2, 3, 4, 4}, {0, 1, 2, 2, 2, 3, 2, 4},
    {3, 0, 0, 4, 2, 1, 4, 4}, {2, 0, 0, 2, 2, 1, 2, 4}
};
const int inverseMovements[8] = {5, 4, 7, 6, 1, 0, 3, 2}; // ���ƶ������ڳ�������

deque<int> lines[4]; // �洢���еķ���
int currentDepth; // ��ǰ�������
char solution[107]; // �洢�������

// ��ȡָ��λ�õĵ�����
deque<int>::iterator getPosition(int row, int col) {
    return lines[row].begin() + col;
}

// ���㵱ǰ���õ����ȼ������ķ���ͳһ�̶ȣ�
//����Ԥ�ڵĺ���
int getPriority() {
    int counts[4] = {0};
    counts[*getPosition(0, 2)]++; counts[*getPosition(2, 3)]++; counts[*getPosition(1, 2)]++;
    counts[*getPosition(0, 3)]++; counts[*getPosition(1, 3)]++;
    counts[*getPosition(0, 4)]++; counts[*getPosition(3, 3)]++; counts[*getPosition(1, 4)]++;
    return 8 - max(max(counts[1], counts[2]), counts[3]);
}

// ִ���ƶ�����
void performMove(int moveType) {
    if (movements[moveType][1]) { // ѭ���ƶ�
        //�����һ���Ƶ�ǰ��
        int last = lines[movements[moveType][0]].back();
        lines[movements[moveType][0]].pop_back();
        lines[movements[moveType][0]].push_front(last);
    } else { // ˳���ƶ�
        int first = lines[movements[moveType][0]].front();
        lines[movements[moveType][0]].pop_front();
        lines[movements[moveType][0]].push_back(first);
    }
    *getPosition(movements[moveType][2], movements[moveType][3]) =
        *getPosition(movements[moveType][0], movements[moveType][4]);
    *getPosition(movements[moveType][5], movements[moveType][6]) =
        *getPosition(movements[moveType][0], movements[moveType][7]);
}

// �����ƶ�����
void undoMove(int moveType) {
    performMove(inverseMovements[moveType]);
}

// ʹ��A*�����㷨Ѱ�ҽ������
bool aStarSearch(int depth) {
    int priority = getPriority();
    if (depth + priority > currentDepth)
        return false;
    if (priority == 0)
        return true;

    for (int i = 0; i < 8; i++) {
        solution[depth] = i + 'A';
        performMove(i);

        if (aStarSearch(depth + 1))
            return true;

        undoMove(i);
        solution[depth] = '\0';
    }

    return false;
}

int main() {
    while (true) {
        for (int i = 0; i < 4; i++) lines[i].clear();
        char input[105];
        fgets(input, sizeof(input), stdin);
        if (input[0] == '0') break;

        // �������룬��ʼ������
        for (int i = 0, j = 0; i < 24; i++, j += 2) {
            for (int k = 1; k <= initialPositions[i][0]; k++) {
                lines[initialPositions[i][k]].push_back(input[j] - '0');
            }
        }

        currentDepth = 0;
        memset(solution, '\0', sizeof(solution));

        // �����������
        while (!aStarSearch(0)) {
            currentDepth++;
        }

        if (currentDepth == 0) {
            printf("No moves needed\n");
        } else {
            printf("%s\n", solution);
        }

        // ������ķ���ķ���
        printf("%d\n", *getPosition(0, 2));
    }

    return 0;
}
