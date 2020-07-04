#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cal_power_mod(int a, int b, int p) {
    int ans = 1 % p;
    for (; b; b >>= 1) {
        if (b & 1) {
            ans = (long long)ans * a % p;
        }
        a = (long long)a * a % p; 
    }
    return ans;
}

int main() {
    int a, b, p;
    while (scanf("%d %d %d", &a, &b, &p) != EOF) {
        printf("%d\n", cal_power_mod(a, b, p));
    }
    return 0;
}
