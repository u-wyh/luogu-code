#include<bits/stdc++.h>
using namespace std;
vector<string> Dict; //��Dict��������ֵ��е�����
string str; //�����ı��
const char * str_trans = "2223334445556667 77888999"; //ʹ�ø�C-����ַ��������A-Z(��ȥQ��Z��24����ĸ����Ӧ������)
int main(){
    ios::sync_with_stdio(false); //ֻ��cin/cout�ӿ�IO�ٶ�
    cin >> str;
    string tmp;
    while (cin >> tmp){ //���������е��ַ���ѭ�����뵽tmp�У��ٷŵ�Vectorβ��(cin>>tmp)�������𵽶����ַ��������ã�Ҳ�������ж��ļ��Ƿ񵽴�ĩβ���������Ķ�C++ Primer Plus��
        Dict.push_back(tmp);
    }
    int len = str.length();
    bool global_flag = false;
    for (int i = 0; i < Dict.size(); i++){ //���������ֵ�Ԫ�أ���Ϊ�ֵ�Ԫ����
        if (len != Dict[i].length())continue; //��֦������ַ���λ����һ����û�б�Ҫ�Ƚϡ�
        bool flag = true;
        for (int j = 0; j < len; j++){
            if (str_trans[Dict[i][j] - 'A'] != str[j]){ //�ȶ��ֵ���ÿ���ַ���Ӧ�������Ƿ��������ÿ��������ͬ
                flag = false; //����ֱͬ������ѭ��
                break;
            }
        }
        if (flag){ //��ͬ������õ���
            cout << Dict[i] << endl;
            global_flag = true;
        }
    }
    if (!global_flag){ //���û��һ�����ʷ���Ҫ�󣬾����NONE��
        cout << "NONE" << endl;
    }
}
