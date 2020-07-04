#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_X 5002

unsigned int val_square[MAX_X][MAX_X];

int main() {
    int n, r;
    while (scanf("%d %d", &n, &r) != EOF) {
        memset(val_square, 0, sizeof(val_square));
        int max_x = 0, max_y = 0, min_x = MAX_X + 1, min_y = MAX_X + 1;
        while (n--) {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            val_square[x][y] += w;
            max_x = x > max_x ? x : max_x;
            max_y = y > max_y ? y : max_y;
            min_x = x < min_x ? x : min_x;
            min_y = y < min_y ? y : min_y;
        }
        int max_val = 0;
        for (int y = min_y; y <= max_y; ++y) {
            for (int x = min_x; x <= max_x; ++x) {
                if (x > 0) {
                    val_square[x][y] += val_square[x - 1][y];
                }
                if (y > 0) {
                    val_square[x][y] += val_square[x][y -  1];
                }
                if (x > 0 && y > 0) {
                    val_square[x][y] -= val_square[x - 1][y - 1];
                }
                int cur_val = val_square[x][y];
                if (x >= r) {
                    cur_val -= val_square[x - r][y];
                } 
                if (y >= r) {
                    cur_val -= val_square[x][y - r];
                }
                if (x >= r && y >= r) {
                    cur_val += val_square[x - r][y - r];
                }
                max_val = cur_val > max_val ? cur_val : max_val;
            }
        }
        printf("%d\n", max_val);
    }
    return 0;
}
