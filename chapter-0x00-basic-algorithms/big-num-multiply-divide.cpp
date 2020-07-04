#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>


std::vector<int> mul(const std::vector<int>& a, int b) {
    std::vector<int> r;
    int t = 0;
    for (int i = 0; i < a.size(); ++i) {
        t += a[i] * b;
        r.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        r.push_back(t % 10);
        t /= 10;
    }
    return r;
}

std::vector<int> div(const std::vector<int>& a, int b) {
    std::vector<int> r;
    int t = 0;
    bool is_first = true;
    for (int i = a.size() - 1; i >= 0; --i) {
        t = t * 10 + a[i];
        int x = t / b;
        if (!is_first || x) {
            r.push_back(x);
            is_first = false;
        }
        t %= b;
    }
    if (is_first) {
        r.push_back(0);
    }
    std::reverse(r.begin(), r.end());
    return r;
}

void print_big_num(const std::vector<int>& a) {
    for (int i = a.size() - 1; i >= 0; --i) {
        printf("%d", a[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage : exe op_type[m/d] num1 num2\n");
        return -1;
    }
    int b = std::stoi(std::string(argv[3]));
    std::vector<int> a;
    std::string b_str(argv[2]);
    for (int i = b_str.size() - 1; i >= 0; --i) {
        a.push_back(b_str[i] - '0');
    }
    if (argv[1][0] == 'm') {
        auto r = mul(a, b);
        print_big_num(r);        
    } else if (argv[1][0] == 'd') {
        auto r = div(a, b);
        print_big_num(r);
    } else {
        printf("op_type not supported : %s\n", argv[1]);
    }
    return 0;
}
