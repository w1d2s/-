#include <stdio.h>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* 每一步有两种选择：把栈顶数字连接到答案上，或是把
 * 下一个要进栈的数字进栈。
 */

void dfs(vector<string>& results, string prefix, 
        stack<int>& stk, vector<int>& arr, int ptr) {
    if (20 == results.size()) {
        return;
    }
    if (stk.empty() && ptr == arr.size()) {
        results.push_back(prefix);
        return;
    }
    if (!stk.empty()) {
        int num = stk.top();
        stk.pop();
        dfs(results, prefix + to_string(num),
                stk, arr, ptr);
        stk.push(num);
    }
    if (ptr < arr.size()) {
        stk.push(arr[ptr]);
        dfs(results, prefix, stk, arr, ptr + 1);
        stk.pop();
    }
}

int main() {
    int n;
    vector<int> arr;
    vector<string> results;
    stack<int> stk;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        arr.push_back(i);
    }
    dfs(results, string(""), stk, arr, 0);
    for (int i = 0; i < results.size(); ++i) {
        printf("%s\n", results[i].c_str());
    }
    return 0;
}
