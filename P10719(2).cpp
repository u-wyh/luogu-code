#include<iostream>
using namespace std;
bool a[114][514];// �洢����
int b[1919][810];// �洢��άǰ׺��
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m,k;cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;cin>>c;
			a[i][j]=c-'0';
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];// �����ݳ�ԭ������ b[i][j]
		}
	}
	int mn=0xcff0102;// һ���㹻�����
	for(int x1=0;x1<n;x1++){// ע������ķ�Χ
		for(int y1=0;y1<m;y1++){// ע������ķ�Χ
			for(int x2=x1;x2<=n;x2++){
				for(int y2=y1;y2<=m;y2++){
					int tmp=b[x2][y2]-b[x2][y1]-b[x1][y2]+b[x1][y1];// ���϶˵�Ϊ (x1+1,y1+1)�����϶˵�Ϊ (x2+1,y2+1) �ľ����� 1 ������
					if(tmp>=k)mn=min(mn,(x2-x1)*(y2-y1));
				}
			}
		}
	}
	cout<<((mn==0xcff0102)?0:mn);// ע���ж��޽�
	return 0;
}
