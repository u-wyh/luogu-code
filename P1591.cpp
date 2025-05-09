#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility> // ����pair
using namespace std;

// �Ƴ�ǰ����
void removeLeadingZeros(vector<int>& num) {
    while(num.size()>1&&num.back()==0){
		num.pop_back();
	}
}

// �Ƚ������������Ĵ�С������1��ʾa>b��0��ʾa==b��-1��ʾa<b
int compare(const vector<int>& a, const vector<int>& b) {
    if(a.size()!=b.size()){
		return (a.size()>b.size())?1:-1;
	}
	for(int i=(int)a.size()-1;i>=0;i--){
		if(a[i]!=b[i]){
			return (a[i]>b[i])?1:-1;
		}
	}
	return 0;
}

// �ַ���ת������
//�����е�����  ����û�п��Ǹ���
vector<int> strToNum(const string& s) {
    vector<int>num;
	for(int i=(int)s.size()-1;i>=0;i--){
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


// �������ӷ�
vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry=0;
	for(int i=0;i<(int)a.size()||i<(int)b.size()||carry;i++){
		if(i<(int)a.size()) carry+=a[i];
		if(i<(int)b.size()) carry+=b[i];
		res.push_back(carry%10);
		carry/=10;
	}
    return res;
}

// ���������� (����a >= b)
vector<int> sub(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    for(int i=0;i<a.size();i++){
		carry=a[i]-carry;
		if(i<(int)b.size()) carry-=b[i];
		carry=(carry<0)?1:0;
	}
    removeLeadingZeros(res);
    return res;
}

// ����������С����
vector<int> mul(const vector<int>& a, int b) {
    vector<int> res;
    int carry=0;
	for(int i=0;i<(int)a.size()||carry;i++){
		if(i<(int)a.size()) carry+=b*a[i];
		res.push_back(carry%10);
		carry/=10;
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
	removeLeadingZeros(res);
    return res;
}

// ����������С�����������̺�����
pair<vector<int>, int> div(const vector<int>& a, int b) {
    vector<int> res;
    int remainder = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        remainder = remainder * 10 + a[i];
        res.push_back(remainder / b);
        remainder %= b;
    }
    reverse(res.begin(), res.end());
    removeLeadingZeros(res);
    return make_pair(res, remainder);
}

// ���������Դ����� (��ʵ�֣�Ч�ʲ���)
vector<int> div(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    vector<int> current;
    
    for (int i = a.size() - 1; i >= 0; --i) {
        current.insert(current.begin(), a[i]);
        removeLeadingZeros(current);
        
        int quotient = 0;
        while (compare(current, b) >= 0) {
            current = sub(current, b);
            quotient++;
        }
        res.push_back(quotient);
    }
    
    reverse(res.begin(), res.end());
    removeLeadingZeros(res);
    return res;
}

// ʾ��ʹ��
int main() {
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        vector<int>res;
        res.push_back(1);
        for(int i=2;i<=n;i++){
            res=mul(res,i);
        }
        int ans=0;
        for(int i=0;i<res.size();i++){
            if(res[i]==m){
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}