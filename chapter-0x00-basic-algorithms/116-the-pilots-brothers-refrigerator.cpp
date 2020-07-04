#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

void print_binary(unsigned int state) {
    printf("state = %d\n", state);
    char n[17];
    for (int i = 15; i >= 0; --i) {
        if (state & (1 << (15 - i))) {
            n[i] = '1';
        } else {
            n[i] = '0';
        }
    }
    n[16] = '\0';
    printf("%s\n", n);
}

int main() {
    // '1' on bit for close, '0' for open
    unsigned int state = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            char tmp;
            scanf("%c", &tmp);
            if (tmp == '+') {
                int pos = i * 4 + j;
                state |= (1 << pos);
            }
            if (j == 3) {
                getchar();
            }
        }
    }
    //print_binary(state);

    int min_op_num = 17;
    unsigned best_op = 0;

    for (unsigned int op = 0; op < 65536; ++op) {
        unsigned int cur_state = state;
        int op_num = 0;
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                int pos = r * 4 + c;
                if (op & (1 << pos)) {
                    ++op_num;
                    for (int cc = 0; cc < 4; ++cc) {
                        int p = r * 4 + cc; 
                        cur_state ^= (1 << p); 
                    }
                    for (int rr = 0; rr < 4; ++rr) {
                        int p = rr * 4 + c;
                        cur_state ^= (1 << p);
                    }
                    int p = r * 4 + c;
                    cur_state ^= (1 << p);
                }
            }
        }
        if (0 == cur_state && op_num < min_op_num) {
            min_op_num = op_num;
            best_op = op;
        }
    }
    printf("%d\n", min_op_num);
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            int pos = r * 4 + c;
            if (best_op & (1 << pos)) {
                printf("%d %d\n", r + 1, c + 1);
            }
        }
    }
    return 0;
}
