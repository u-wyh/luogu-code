//P1032 字串变换
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
typedef long long ll;

string a,b;

struct Node {//用于queue中存放，一个是字串，一个是搜索的“深度”
	string data;
	int step;
	Node(string _data,int _step):data(_data),step(_step) {}
	Node() {}
};
queue<Node>q;
string change[10];//改成哪个
string diff[10];//改哪个
/*即
搜索diff[i]
改成change[i]
*/

int nxt[10][10000];//kmp的next数组
map<string,bool>mp;//用于判重，避免重复搜索
il void get_next(int x)//找next，具体的可以翻翻网上的Blog。
{
	re int i,j=0;
	for (i=2; i<diff[x].length(); i++) {
		while (j&&diff[x][i]!=diff[x][j+1]) j=nxt[x][j];
		if (diff[x][j+1]==diff[x][i]) j++;
		nxt[x][i]=j;
	}
}

il void KMP(string a,int x,int step)//寻找匹配的串，顺便修改并添加到queue中
{
	string z=a;
	a=" "+a;//神奇的操作，。。。
	re int i,j=0;
	for (i=1; i<a.length(); i++) {
		while (j>0&&diff[x][j+1]!=a[i])	j=nxt[x][j];
		if (diff[x][j+1]==a[i]) j++;
		if (j==diff[x].length()-1) {//找到了~
			re int t= i-diff[x].length()+1;//记录位置
			string tmp=z.substr(0,t)+change[x]+z.substr(t+diff[x].length()-1);//修改（就不用replace，（真香））
			q.push(Node(tmp,step+1));
			j=nxt[x][j];//继续找
/*
第一次交由于脑子不好，找了一遍就return了。
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
		diff[cn]=" "+t1;//继续神奇的操作
		get_next(cn);
	}
	q.push(Node(a,0));
	while (!q.empty()) {
		Node now=q.front();
		q.pop();
		string x=now.data;
		if (mp[x]) continue;//map判重
		mp[x]=1;//标记
		if (now.step>10) {//找不到（因为bfs是按照step:1,2,3...来找的，所以一旦到了STEP11时一定无解了）
			puts("NO ANSWER!");
			exit(0);
		}
		if (x==b) {//找到，由于搜索有序，step一定是最小的
			cout << now.step<<endl;
			exit(0);
		}
		for (re int i=1; i<=cn; i++) {//枚举所有模式串，匹配文本串
			KMP(x,i,now.step);
		}
	}
	puts("NO ANSWER!");//最后由于map的判重，可能导致queue为空，于是到达这里的数据肯定是无解的
	exit(0);
}
