#include <bits/stdc++.h>
using namespace std;

stack <int> st;
int t[300005],m[300005];
long long ans;

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		if(t[i]<i){
			cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>m[i];
	}
	int dw=n;
	for(int i=t[n];i>=1;i--){
		if(t[dw]<i){
        //����һ���˻�û��ȡ��֭ʱ���Ϳ��������������
			if(st.size()){
				ans+=st.top();
				st.pop();
			}
		}else if(t[dw]==i){
        //����һ�����Ѿ���ȡ��֭ʱ����������������
			if(st.size())
                st.push(max(st.top(),m[dw]));
			else
                st.push(m[dw]);
			dw--,i++;
		}else if(t[dw]>i)
            dw--,i++;
      //����һ���˺���һ����ͬʱȡ��֭ʱ��Ҫ�浽ջ����ǰ������
	}

	while(st.size()){
		ans+=st.top();
		st.pop();
	}
	cout<<ans;
	return 0;
}
