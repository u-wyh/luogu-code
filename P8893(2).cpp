#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,k,r,day,vis[N],t[N];
//vis ��¼ĳ���Ƿ�������t ��¼��ĳ������Ҫ��������
int w,nw,ok[N],nok[N];
//�ֱ��¼�����Ƽ���Ŀ�������Ƽ���Ŀ
vector <int> relat[N];
//relat ��¼ĳ������Щ�����Ŀ������
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k>>nw;
	for(int i=1;i<=nw;i++) cin>>nok[i];
	cin>>r;
	for(int i=1,x,y;i<=r;i++){
		cin>>x>>t[x];
		for(int j=1;j<=t[x];j++){
			cin>>y;
			relat[y].push_back(x);
		}
	}
	while(1){
		//�����Ƽ���Ŀ���Ƶ������Ƽ���Ŀ��
		w=nw;nw=0;
		for(int i=1;i<=w;i++)
			ok[i]=nok[i];
		//�������û���κ��Ƽ���Ŀ���޽�
		if(!w){
			cout<<"-1\n";
			return 0;
		}
		for(int i=1;i<=w;i++){
			//��¼����
			vis[ok[i]]=1;
			//���������������Ŀ����
			for(int j=0,l=relat[ok[i]].size();j<l;j++){
				t[relat[ok[i]][j]]--;
				//�����������Ϊ�㣬���������������
				if(!t[relat[ok[i]][j]]){
					nok[++nw]=relat[ok[i]][j];
				}
			}
		}
		//�����˵�k���⣬�˳�ѭ��
		if(vis[k]) break;
		day++;
 	}
	cout<<day<<'\n';
	return 0;
}
