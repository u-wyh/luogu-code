#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXL = 20;
//���ֵ��ѡȡ�� 2��MAXL�η� ��  ��ӽ�����MAXN����Сֵ
const int MAXN = 100001;

int cnt;//���ڼ�¼�ڵ��� ��AVLһ��
int key[MAXN];//���ڼ�¼��ǰ�ڵ��Ӧ�ļ�ֵ�Ƕ���
int key_count[MAXN];//���ڼ�¼��ǰֵ�����˶��ٴ�
int level[MAXN];//���ڼ�¼�ýڵ�����ж��ٲ�   ��ʼʱ�������
int next_node[MAXN][MAXL + 1];//���ڼ�¼�ýڵ�ĵ�i��ָ�����һ���ڵ���ʲô
int len[MAXN][MAXL + 1];//��¼�ýڵ�ĵ�i�㵽��һ������֮���ж��ٸ�����  ��Ӧ��һ������ָ���  ���ұ�
int val[MAXN];
int realcnt=0;

void build() {
    cnt = 1;
    key[cnt] = INT_MIN;//��һ���ڵ�ı����Զ��1
    level[cnt] = MAXL;//���Ĳ���ֱ������Ϊ����
    val[1]=0;
}
//��ʼ����ͷ  ���ű� Խ���� ֵԽ��

int randomLevel() {
    //��������½ڵ�Ĳ���ֵ ������Զ�������
    int ans = 1;
    while ((std::rand() / double(RAND_MAX)) < 0.5) {
        ans++;
    }
    return min(ans, MAXL);
}

int find(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        if (next_node[i][h] != 0 && key[next_node[i][h]] == num) {
            return next_node[i][h];
        } else {
            return 0;
        }
    }
    return find(i, h - 1, num);
}

int addNode(int i, int h, int j) {
    int rightCnt = 0;
    //����ͳ��i�ڵ㵽  ��һ���ڵ���ڵ���key[j] �Ľڵ��м����
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        next_node[j][h] = next_node[i][h];
        next_node[i][h] = j;
        len[j][h] = key_count[next_node[j][h]];//ֱ�Ӿ��Ǵ�Ƶ  ��Ϊ������ײ�
        len[i][h] = key_count[next_node[i][h]];//����ط�Ҳ������1   �Ͼ������½��ڵ�  һ����1
        return rightCnt;
    } else {
        int downCnt = addNode(i, h - 1, j);
        if (h > level[j]) {
            len[i][h]++;
        } else {
            next_node[j][h] = next_node[i][h];
            next_node[i][h] = j;
            len[j][h] = len[i][h] + 1 - downCnt - key_count[j];
            len[i][h] = downCnt + key_count[j];
        }
        return rightCnt + downCnt;
    }
}

// ����num���ظ�����������Ƶ
void add(int num,int k) {
    if (find(1, MAXL, num) != 0) {
        return ;
    } else {
        realcnt++;
        key[++cnt] = num;
        key_count[cnt] = 1;
        level[cnt] = randomLevel();
        val[cnt]=k;
        addNode(1, MAXL, cnt);
    }
}

// ��ǰ��i�Žڵ��h�㣬ɾ���ռ���Ϊj�Ľڵ�
void removeNode(int i, int h, int j) {
    if (h < 1) {
        return;
    }
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        i = next_node[i][h];
    }
    if (h > level[j]) {
        len[i][h]--;
    } else {
        next_node[i][h] = next_node[j][h];
        len[i][h] += len[j][h] - 1;
    }
    removeNode(i, h - 1, j);
}

// ɾ��x������ж����ֻɾ��һ��
void remove(int num) {
    int j = find(1, MAXL, num);
    cout<<23<<' '<<num<<endl;
//    if(j!=realcnt&&j!=1){
//        cout<<j<<' '<<num<<endl;
//        system("pause");
//    }
    if (j != 0) {
        removeNode(1, MAXL, j);
        realcnt--;
    }
}

// ��ǰ��i�Žڵ��h�㣬��ѯ������x��key��ʲô
int index(int i, int h, int x) {
    int c = 0;
    while (next_node[i][h] != 0 && c + len[i][h] < x) {
        c += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        return key[next_node[i][h]];
    } else {
        return index(i, h - 1, x - c);
    }
}

// ��ѯ������x��key��ʲô
int index(int x) {
    return index(1, MAXL, x);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    build();
    int op;
    cin>>op;
    while(op!=-1){
        if(op==1){
            int x,k;
            cin>>k>>x;
            add(x,k);
        }
        else if(op==2&&realcnt>0){
            cout<<2<<' '<<index(1)<<endl;
            remove(index(1));
        }
        else if(op==3&&realcnt>0){
            cout<<3<<' '<<index(realcnt)<<endl;
            remove(index(realcnt));
        }
        //cout<<' '<<realcnt<<endl;
        cin>>op;
    }
    int ans1=0,ans2=0;
    for(int i=next_node[1][1];i!=0;i=next_node[i][1]){
        ans1+=val[i];
        ans2+=key[i];
        cout<<key[i]<<' ';
    }
    cout<<endl;
    printf("%lld %lld",ans1,ans2);
    return 0;
}

