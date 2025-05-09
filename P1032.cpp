//P1032 �ִ��任
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
typedef long long ll;

string a,b;

struct Node {//����queue�д�ţ�һ�����ִ���һ���������ġ���ȡ�
	string data;
	int step;
	Node(string _data,int _step):data(_data),step(_step) {}
	Node() {}
};
queue<Node>q;
string change[10];//�ĳ��ĸ�
string diff[10];//���ĸ�
/*��
����diff[i]
�ĳ�change[i]
*/

int nxt[10][10000];//kmp��next����
map<string,bool>mp;//�������أ������ظ�����
il void get_next(int x)//��next������Ŀ��Է������ϵ�Blog��
{
	re int i,j=0;
	for (i=2; i<diff[x].length(); i++) {
		while (j&&diff[x][i]!=diff[x][j+1]) j=nxt[x][j];
		if (diff[x][j+1]==diff[x][i]) j++;
		nxt[x][i]=j;
	}
}

il void KMP(string a,int x,int step)//Ѱ��ƥ��Ĵ���˳���޸Ĳ���ӵ�queue��
{
	string z=a;
	a=" "+a;//����Ĳ�����������
	re int i,j=0;
	for (i=1; i<a.length(); i++) {
		while (j>0&&diff[x][j+1]!=a[i])	j=nxt[x][j];
		if (diff[x][j+1]==a[i]) j++;
		if (j==diff[x].length()-1) {//�ҵ���~
			re int t= i-diff[x].length()+1;//��¼λ��
			string tmp=z.substr(0,t)+change[x]+z.substr(t+diff[x].length()-1);//�޸ģ��Ͳ���replace�������㣩��
			q.push(Node(tmp,step+1));
			j=nxt[x][j];//������
/*
��һ�ν��������Ӳ��ã�����һ���return�ˡ�
*/
		}
	}
	return;
}

int cn=0;
int main()
{
	//freopen("in.txt","r",stdin);
	cin >> a >> b;
	string t1,t2;
	while (cin >>t1>>t2) {
		change[++cn]=t2;
		diff[cn]=" "+t1;//��������Ĳ���
		get_next(cn);
	}
	q.push(Node(a,0));
	while (!q.empty()) {
		Node now=q.front();
		q.pop();
		string x=now.data;
		if (mp[x]) continue;//map����
		mp[x]=1;//���
		if (now.step>10) {//�Ҳ�������Ϊbfs�ǰ���step:1,2,3...���ҵģ�����һ������STEP11ʱһ���޽��ˣ�
			puts("NO ANSWER!");
			exit(0);
		}
		if (x==b) {//�ҵ���������������stepһ������С��
			cout << now.step<<endl;
			exit(0);
		}
		for (re int i=1; i<=cn; i++) {//ö������ģʽ����ƥ���ı���
			KMP(x,i,now.step);
		}
	}
	puts("NO ANSWER!");//�������map�����أ����ܵ���queueΪ�գ����ǵ�����������ݿ϶����޽��
	exit(0);
}
