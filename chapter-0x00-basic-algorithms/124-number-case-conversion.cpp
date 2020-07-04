#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define MAX_N 1010

using namespace std;

unordered_map<char, int> char2val;
vector<char> val2char;

void build_char_val_map() {
    for (int i = 0; i <= 9; ++i) {
        val2char.push_back('0' + i);
        char2val[val2char[i]] = i;
    }

    for (int i = 10; i <= 35; ++i) {
        val2char.push_back('A' + i - 10);
        char2val[val2char[i]] = i;
    }

    for (int i = 36; i <= 61; ++i) {
        val2char.push_back('a' + i - 36);
        char2val[val2char[i]] = i;
    }
}

void print_vec(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 模拟a进制除法，被除数src为a进制数(最高位在index 0)，b为除数
// result为商（a进制），remainder为余数
void divide_in_case_a(const vector<int>& src, const int a,
        const int b, vector<int>& result, int& remainder) {
    int sz = src.size();
    int r = 0;
    bool first_zero = true;
    for (int i = 0; i < sz; ++i) {
        int res = (r * a + src[i]) / b;
        r = r * a + src[i] - res * b;

        if (0 != res || !first_zero) {
            result.push_back(res);
            first_zero = false;
        }
    }
    remainder = r;
}

void convert_a_to_b(const vector<int>& src, const int a,
        const int b, vector<int>& dst) {
    vector<int> tmp_src(src);
    vector<int> tmp_quotient;
    while (tmp_src.size() != 0) {
        int remainder;
        divide_in_case_a(tmp_src, a, b, tmp_quotient, remainder);
        dst.push_back(remainder);
        tmp_src.swap(tmp_quotient);
        tmp_quotient.clear();
    }

    reverse(dst.begin(), dst.end());
}

int main() {
    build_char_val_map();
    
    int n;
    cin >> n;

    while (n--) {
        vector<int> src;
        string src_str;
        int a, b;
        cin >> a >> b >> src_str;
        for (int i = 0; i < src_str.size(); ++i) {
            src.push_back(char2val[src_str[i]]);
        }
        
        vector<int> dst;
        convert_a_to_b(src, a, b, dst);
        string dst_str(dst.size(), '0');
        for (int i = 0; i < dst.size(); ++i) {
            dst_str[i] = val2char[dst[i]];
        }

        cout << a << " " << src_str << endl;
        cout << b << " " << dst_str << endl;
        cout << endl;
    }

    return 0;
}
