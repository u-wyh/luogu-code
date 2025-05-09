//p4667
#include<bits/stdc++.h>
using namespace std;
const int dx[4]={1,-1,-1,1}; //�������飬������
const int dy[4]={1,1,-1,-1};
const char a[5]="\\/\\/";
const int ix[4]={0,-1,-1,0};
const int iy[4]={0,0,-1,-1};
deque <int> x;  //˫�˶��У�
deque <int> y;
char map[505][505]; //�洢��ͼ
int vis [505][505]; //vis���飬��¼��̲���
int l,c;  //l����line����������c����column��������

void bfs(){  //���Ѻ���
	memset(vis,0x3f,sizeof(vis)); //��ΪҪ����Сֵ����vis�����ʼ����0x3f������һ���ܴ��������
	x.push_back(0);  //��㣨0��0����ӣ�������0
	y.push_back(0);
	vis[0][0]=0;
	while(!x.empty()){  //��һ���־��ǰѹ��ѵİ�����
		int xx=x.front();  //��get������
		int yy=y.front();
		x.pop_front();  //һ��Ҫget����֮����pop��ȥ
		y.pop_front();
		for(int i=0;i<4;i++){  //4������һ��һ����
			int dnx=xx+dx[i]; //dnx��dxy������ĺ�������
			int dny=yy+dy[i];
			int inx=xx+ix[i];//inx��iny�������ӵĺ�������
			int iny=yy+iy[i];
			if(dnx>=0&&dnx<=l&&dny>=0&&dny<=c){  //���û����Ļ��Ϳ����벻���
				if(a[i]!=map[inx][iny]){ //������ͼ�ĵ���״̬������������ߵĵ���״̬�Ƿ�һ��
					int t=vis[xx][yy]+1;  //��һ�¾�Ҫת�򣬲���+1
					if(t<vis[dnx][dny]){ //�����ԭ���Ĳ���С������ӣ����
						x.push_back(dnx); //ת��϶����粻ת��ã�����Ҫ���ѣ��Ӷ�β���
						y.push_back(dny);
						vis[dnx][dny]=t;
					}
				}
				else{//Ҫ���Ͳ���ת��
					int t=vis[xx][yy]; //����ת�򣬲������ñ�;
					if(t<vis[dnx][dny]){ //������ԭ����С�������
						x.push_front(dnx); //����ת��϶����ã�Ҫ���ѣ��Ӷ������
						y.push_front(dny);
						vis[dnx][dny]=t;
					}
				}
			}
		}
	}
	cout<<vis[l][c]<<endl; //������Ĳ���
}

int main(){
		cin>>l>>c; //����
		for(int i=0;i<l;i++)
			cin>>map[i];
		if((l+c)%2) //����յ���������������
		cout<<"NO SOLUTION\n";//�Ǿ������޽�
		else bfs(); //���޽��Ǿ͹���
	return 0;
}
