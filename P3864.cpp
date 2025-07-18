#include<bits/stdc++.h>
using namespace std;
vector<string> Dict; //用Dict存放所有字典中的名字
string str; //给定的编号
const char * str_trans = "2223334445556667 77888999"; //使用该C-风格字符串来存放A-Z(除去Q和Z这24个字母所对应的数字)
int main(){
    ios::sync_with_stdio(false); //只用cin/cout加快IO速度
    cin >> str;
    string tmp;
    while (cin >> tmp){ //将后面所有的字符串循环读入到tmp中，再放到Vector尾，(cin>>tmp)即可以起到读入字符串的作用，也可以起到判断文件是否到达末尾。详情请阅读C++ Primer Plus。
        Dict.push_back(tmp);
    }
    int len = str.length();
    bool global_flag = false;
    for (int i = 0; i < Dict.size(); i++){ //遍历所有字典元素，因为字典元素少
        if (len != Dict[i].length())continue; //剪枝，如果字符串位数不一样就没有必要比较。
        bool flag = true;
        for (int j = 0; j < len; j++){
            if (str_trans[Dict[i][j] - 'A'] != str[j]){ //比对字典中每个字符对应的数字是否与输入的每个数字相同
                flag = false; //不相同直接跳出循环
                break;
            }
        }
        if (flag){ //相同则输出该单词
            cout << Dict[i] << endl;
            global_flag = true;
        }
    }
    if (!global_flag){ //如果没有一个单词符合要求，就输出NONE。
        cout << "NONE" << endl;
    }
}
