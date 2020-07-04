#include <stdio.h>
#include <stdlib.h>

long long multiply_mod_int64(long long a, long long b, long long p) {
    long long ans = 0;
    a %= p;
    for (; b; b >>= 1) {
        if (b & 1) {
            ans = (ans + a) % p;
        }
        a = a * 2 % p;
    }
    return ans;
}

int main() {
    long long a, b, p;
    while (scanf("%lld", &a) != EOF) {
        scanf("%lld", &b);
        scanf("%lld", &p);
        printf("%lld\n", multiply_mod_int64(a, b, p));
    }
    return 0;
}
