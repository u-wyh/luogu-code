#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <cmath>

// ��ϣ������
class Hash {
public:
    // ���캯����ʹ��ָ���Ĺ�ϣ�㷨
    Hash(const std::string& algorithm) {
        if (algorithm == "MD5") {
            md_ctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(md_ctx, EVP_md5(), NULL);
        } else {
            throw std::runtime_error("Unsupported algorithm");
        }
    }

    // �����������ͷ���Դ
    ~Hash() {
        EVP_MD_CTX_free(md_ctx);
    }

    // �����ַ��������ع�ϣֵ
    std::string hashValue(const std::string& input) {
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hash_len;
        EVP_DigestUpdate(md_ctx, input.data(), input.size());
        EVP_DigestFinal_ex(md_ctx, hash, &hash_len);

        std::stringstream ss;
        for (unsigned int i = 0; i < hash_len; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return ss.str();
    }

private:
    EVP_MD_CTX* md_ctx;
};

// �������п��ܵ��ַ���
std::vector<std::string> generateStrings(const std::vector<char>& arr, int n) {
    std::vector<std::string> ans;
    std::string path;
    generateStringsHelper(arr, 0, n, path, ans);
    return ans;
}

void generateStringsHelper(const std::vector<char>& arr, int i, int n, std::string& path, std::vector<std::string>& ans) {
    if (i == n) {
        ans.push_back(path);
    } else {
        for (char cha : arr) {
            path.push_back(cha);
            generateStringsHelper(arr, i + 1, n, path, ans);
            path.pop_back();
        }
    }
}

int main() {
    std::cout << "֧�ֵĹ�ϣ�㷨����MD5�ڴ�ʾ����֧�֣�:" << std::endl;
    // ע�⣺C++��û�����õķ������г�����֧�ֵĹ�ϣ�㷨�������˵��
    std::cout << "MD5" << std::endl << std::endl;

    try {
        Hash hash("MD5");

        std::string str1 = "zuochengyunzuochengyunzuochengyun1";
        std::string str2 = "zuochengyunzuochengyunzuochengyun2";
        std::string str3 = "zuochengyunzuochengyunzuochengyun3";
        std::string str4 = "zuochengyunzuochengyunZuochengyun1";
        std::string str5 = "zuochengyunzuoChengyunzuochengyun2";
        std::string str6 = "zuochengyunzuochengyunzuochengyUn3";
        std::string str7 = "zuochengyunzuochengyunzuochengyun1";

        std::cout << "7���ַ����õ��Ĺ�ϣֵ:" << std::endl;
        std::cout << hash.hashValue(str1) << std::endl;
        std::cout << hash.hashValue(str2) << std::endl;
        std::cout << hash.hashValue(str3) << std::endl;
        std::cout << hash.hashValue(str4) << std::endl;
        std::cout << hash.hashValue(str5) << std::endl;
        std::cout << hash.hashValue(str6) << std::endl;
        std::cout << hash.hashValue(str7) << std::endl << std::endl;

        std::vector<char> arr = {'a', 'b'};
        int n = 20;

        std::cout << "���ɳ���Ϊ" << n << "���ַ�����arr�����п��ܵ��ַ���" << std::endl;
        std::vector<std::string> strs = generateStrings(arr, n);
        std::cout << "��ͬ�ַ���������:" << strs.size() << std::endl;

        std::set<std::string> hashSet;
        for (const std::string& str : strs) {
            hashSet.insert(hash.hashValue(str));
        }

        // ע�⣺������һ������Ӧ��ʹ��hashSet.size()������strs.size()
        std::cout << "��ͬ��ϣֵ������:" << hashSet.size() << std::endl << std::endl;

        int m = 13;
        std::vector<int> cnts(m, 0);

        std::cout << "���ڿ�����Щ��ϣֵ��% " << m << " ֮��������ֲ����" << std::endl;
        for (const std::string& hashCode : hashSet) {
            unsigned long long hashValue = std::stoull(hashCode, nullptr, 16);
            int ans = hashValue % m;
            cnts[ans]++;
        }

        for (int i = 0; i < m; ++i) {
            std::cout << "���� " << i << " ������ " << cnts[i] << " ��" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
