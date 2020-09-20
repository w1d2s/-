#include <stdio.h>
#include <vector>
#include <stack>

#define MAX_N 100005
using namespace std;

/* 注意：
 * 单调栈从栈底到栈顶柱子高度递增，保证了每次弹出
 * 栈顶柱子(用B表示，高度h[B])时，向右一直数到待入栈柱子左边一个的范围都是
 * 高度不低于h[B]的柱子，因此构成的高h的大矩形可以一直向右延伸到待入
 * 栈元素的左边一个柱子。
 * 但还需要考虑向左能延伸到哪里，记栈内B柱子下面的柱子为A(高度h[A])，首先
 * 由单调栈性质，h[A] <= h[B]，那么histogram中，A在B左边，A/B之间的柱子高
 * 度一定都高于h[B](如果有比A矮的，那么B入栈时候A肯定已经被弹出了；如果有
 * 高度介于A/B之间的，那么在栈内B下面的柱子肯定不是A而是这个介于A/B之间的
 * 某个柱子)；这些A/B之间的柱子都高于B就保证了以h[B]为高度的大矩形可以一直
 * 向左延伸到A右边一个的位置。那么如何计算向左延伸了多少个柱子？把每次弹出
 * 的柱子宽度累加起来再push回去就好了。
 */

typedef unsigned long long ull;

ull heights[MAX_N];

struct Block {
    ull h;
    int w;
    
    Block(ull _h, int _w): h(_h), w(_w) {}
};

ull solve(const int n) {
    heights[n] = 0;
    stack<Block> stk;
    ull max = 0;
    for (int i = 0; i <= n; ++i) {
        int total_width = 0;
        while (!stk.empty() &&
                stk.top().h > heights[i]) {
            total_width += stk.top().w;
            ull cur_area = stk.top().h * total_width;
            max = cur_area > max ? cur_area : max;
            stk.pop();
        }
        Block cur(heights[i], total_width + 1);
        stk.push(cur);
    }
    return max;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &heights[i]);
        }
        ull max = solve(n);
        printf("%lld\n", max);
    }
    return 0;
}
