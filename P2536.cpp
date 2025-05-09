#include <bits/stdc++.h>
using namespace std;
const int MAX = 1007;
bitset<1007> vis[500007];
//���仯��Ҫ��bitset��Ϊ��ʡ�ռ�

struct Trie//Trie���ṹ���װʽд��
//��ϲ���������Ϊ�������ͺ�STLһ��
{
     int ch[500007][5], sz = 0, val[500007];
     //valָ�����λ��Ϊ��β�ĵ�������

     void clear()//��ʼ��
     {
          memset(ch, 0, sizeof(ch));
          sz = 0;
     }

     int idx(char c)//��ȡÿ���ַ���Ӧ������
     //�ܲ��ܰ�char���������±�ɣ�map���ɵ���û˵
     {
          if (c == 'A')
          {
               return 1;
          }
          if (c == 'G')
          {
               return 2;
          }
          if (c == 'T')
          {
               return 3;
          }
          if (c == 'C')
          {
               return 4;
          }
          if (c == '?')
          {
               return 5;
          }
          if (c == '*')
          {
               return 6;
          }
     }

     void insert(char s[])//�������
     {
          int u = 0, len = strlen(s + 1);
          for (int i = 1; i <= len; i++)
          {
               int x = idx(s[i]);
               if (ch[u][x] == 0)
               {
                    ch[u][x] = ++sz;
               }
               u = ch[u][x];
          }
          val[u]++;
     }
} Tree;

char vir[1007];//������
int N, L;//�ֱ�ΪRNA�����������������ĳ���
int ans = 0;//���ԺͲ�����ƥ���RNA������

void dfs(int stp, int now) //ģʽ���ĵ�stpλ����trie���ϵ�λ��Ϊnow
{
     if (stp == L + 1)//�������ѵ�����
     {
          ans += Tree.val[now];//���´�
          Tree.val[now] = 0;//�޸�valֵ��������
          return;
     }
     if (vis[now][stp])//���仯
     {
          return;
     }

     int x = Tree.idx(vir[stp]);
     vis[now][stp] = 1;

     if (x >= 1 && x <= 4)//��stpλ��������ĸ
     {
          if (Tree.ch[now][x])
               dfs(stp + 1, Tree.ch[now][x]);
     }

     if (x == 5)//����'?'
     {
          for (int i = 1; i <= 4; i++)
          //���ĸ����򶼿�����
          {
               if (Tree.ch[now][i])
                    dfs(stp + 1, Tree.ch[now][i]);
          }
     }

     if (x == 6)//����*
     {
          dfs(stp + 1, now);//��һ��������մ�
          for (int i = 1; i <= 4; i++)
          //�ڶ��������'*'='?'+'*'
          {
               if (Tree.ch[now][i])
               {
                    dfs(stp + 1, Tree.ch[now][i]);
                    //����'?'
                    dfs(stp, Tree.ch[now][i]);
                    //����'*'
               }
          }
     }
}
int main()
{
     cin >> vir + 1;
     L = strlen(vir + 1);

     cin >> N;
     Tree.clear();

     for (int i = 1; i <= N; i++)
     {
          char RNA[1007];
          cin >> RNA + 1;
          Tree.insert(RNA);
     }
     dfs(1, 0);
     cout << N - ans << endl;//ans��ƥ���ϵ�RNA����
     //��ĿҪ�����ƥ�䲻�ϵĴ�������Ϊ N-ans
}
