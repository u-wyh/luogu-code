#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10000;

int n,k;
int arr[MAXN];
struct node{
    int val,cnt;
}cand[100];
//��Ϊk��ֵ���Ǻܴ�  �������ˮ����������ڵ���k
//��ô����ͳ��Ѫ���ͺ�ѡ���ֵ��������ֻ�ÿ���k-1����

void update(int num) {
    //����һ���������ڸ���
    for (int i = 1; i < k; i++) {
        if (cand[i].val == num && cand[i].cnt > 0) {
            cand[i].cnt++;
            return;
        }
    }
    //��������ѡ�����д������ֵ���Ҵ�����Ϊ0  ��ô������������ִ�����1
    for (int i = 1; i < k; i++) {
        if (cand[i].cnt == 0) {
            cand[i].val = num;
            cand[i].cnt = 1;
            return;
        }
    }
    //���������ֻ�û������  ��ô�ͼ����������
    for (int i = 1; i < k; i++) {
        if (cand[i].cnt > 0) {
            cand[i].cnt--;
        }
    }
    //�������е�����ȫ����һ
}

void collect() {
    for (int i = 1, cur, real; i < k; i++) {
        if (cand[i].cnt > 0) {
            cur = cand[i].val;
            real = 0;
            for (int j=1;j<=n;j++) {
                if (cur == arr[j]) {
                    real++;
                }
            }
            if (real <= n / k) {
                cand[i].cnt=0;
            }
        }
    }
}
//�����������ǲ��Ƿ������ǵ�Ҫ��

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        update(arr[i]);
    }
    for(int i=1;i<k;i++){
        printf("%3d %3d\n",cand[i].val,cand[i].cnt);
    }
    collect();
    for(int i=1;i<k;i++){
        if(cand[i].cnt)
            printf("%3d",cand[i].val);
    }
    return 0;
}
