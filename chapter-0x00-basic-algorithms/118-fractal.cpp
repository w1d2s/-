#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 750

char buf[MAX][MAX];

int cal_size(int n) {
    return int(pow(3, n - 1));
}

void draw(int r, int c, int n) {
    if (1 == n) {
        buf[r][c] = 'X';
        return;
    }
    int sz = cal_size(n - 1);
    draw(r, c, n - 1);
    draw(r, c + 2 * sz, n - 1);
    draw(r + sz, c + sz, n - 1);
    draw(r + 2 * sz, c, n - 1);
    draw(r + 2 * sz, c + 2 * sz, n - 1);
    return;
}

int main() {
    int n;
    while (scanf("%d", &n) && -1 != n) {
        memset(buf, ' ', sizeof(buf)); 
        draw(0, 0, n);
        int sz = cal_size(n);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                printf("%c", buf[i][j]);
            }
            printf("\n");
        }
        printf("-\n");
    }
    return 0;
}

