#include <stdio.h>
#include <stdlib.h>

#define min(x, y) ((x) < (y) ? (x) : (y))

/* 3塔汉诺塔 f_3(n) : 先把上面的n-1片移到中间的塔，
 * 然后把最大片移到目的地塔，然后把n-1片从中间塔移
 * 到目的地塔，f_3(n) = 1 + 2 * f_3(n - 1).
 *
 * 4塔汉诺塔 f_4(n) : 起点A，中间塔为B和C，目的地为D，
 * 首先把前k个片(0 <= k <= n - 1) 用四塔方式移到B，然后
 * 将剩下n-k个片按照三塔方式移到D,然后再把B的k个片按照
 * 四塔方式移到D，
 * f_4(n) = min(2 * f_4(k) + f_3(n - k)) for any 0 <= k <= n - 1
 * 注意四塔方式包含了三塔方式，所以f_4(k) <= f_3(k) for any k.
 */

int main() {
    int f_3[14] = {0, 1}; // 3塔时最小操作数
    int f_4[14] = {0, 1}; // 4塔时最小操作数
    for (int n = 1; n <= 12; ++n) {
        if (n == 1) {
            printf("%d\n", f_4[1]);
        } else {
            f_3[n] = 2 * f_3[n - 1] + 1;
            f_4[n] = 0x3f3f3f3f;
            for (int k = 0; k < n; ++k) {
                int f_first_k = min(f_4[k], f_3[k]) * 2;
                f_4[n] = min(f_4[n], f_first_k + f_3[n - k]);
            }
            printf("%d\n", f_4[n]);
        }
    }
    return 0;
}
