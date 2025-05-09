#include<bits/stdc++.h>
using namespace std;

string s;
int k;
vector<int>a,b;

// �Ƴ�ǰ����
void removeLeadingZeros(vector<int>& num) {
    while(num.size()>1&&num.back()==0){
		num.pop_back();
	}
}

// ����������С����
vector<int> mul(const vector<int>& a, int b) {
    vector<int>res;
	int diff=0;
	for(int i=0;i<(int)a.size()||diff;i++){
		if(i<(int)a.size()) diff+=b*a[i];
		res.push_back(diff%10);
		diff/=10;
	}
	removeLeadingZeros(res);
	return res;
}

// ���������Դ�����
vector<int> mul(const vector<int>& a, const vector<int>& b) {
    vector<int>res(a.size()+b.size(),0);
	for(int i=0;i<(int)a.size();i++){
		for(int j=0;j<(int)b.size();j++){
			res[i+j]+=a[i]*b[j];
			res[i+j+1]+=res[i+j]/10;
			res[i+j]%=10;
		}
	}
    while((int)res.size()>k){
        res.pop_back();
    }
	removeLeadingZeros(res);
	return res;
}

// �ַ���ת������
//�����е�����  ����û�п��Ǹ���
vector<int> strToNum(const string& s) {
    vector<int>num;
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]>='0'&&s[i]<='9'){
			num.push_back(s[i]-'0');
		}
	}
	return num;
}

// ������ת�ַ���
string numToStr(const vector<int>& num) {
    string s;
	for(int i=(int)num.size()-1;i>=0;i--){
		s+=to_string(num[i]);
	}
	return s;
}

int main()
{
    cin>>s>>k;
    a=strToNum(s);
    removeLeadingZeros(a);
    while((int)a.size()>k){
        a.pop_back();
    }
    vector<int>tmp=a;
    vector<int>ans;
    ans.push_back(1);
    for(int i=0;i<k;i++){
        b.push_back(a[i]);
        int flag=0;
        vector<int>res=a;
        for(int j=1;j<=10;j++){
            res=mul(res,tmp);
            bool ok=true;
            for(int k=0;k<=i;k++){
                if(b[k]!=res[k]){
                    ok=false;
                    break;
                }
            }
            if(ok){
                flag=j;
                break;
            }
        }
        if(flag==0){
            cout<<"-1"<<endl;
            return 0;
        }
        vector<int>temp=tmp;
        for(int j=1;j<flag;j++){
            tmp=mul(tmp,temp);
        }
        ans=mul(ans,flag);
    }
    cout<<numToStr(ans)<<endl;
    return 0;
}