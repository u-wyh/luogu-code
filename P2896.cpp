#include<iostream>
#include<cmath>
using namespace std;
int n,s,a[30005],f[30005],f1[30005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>0;j--){
			if(a[i]>=a[j])
			f[i]=max(f[i],f[j]);
			if(a[i]==a[j])break;//ǰ���Ѿ����������������
		}//�ڲ㵹��ѭ��
		f[i]++;
	}//����½�����
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>0;j--){
			if(a[i]<=a[j])
			f1[i]=max(f1[i],f1[j]);
			if(a[i]==a[j])break;
		}
		f1[i]++;
	}//�����������
	for(int i=1;i<=n;i++){
		s=max(s,f[i]);
		s=max(s,f1[i]);
	}
	cout<<n-s;
	return 0;
}
