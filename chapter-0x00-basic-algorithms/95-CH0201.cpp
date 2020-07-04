#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

char init_state[6][6];
vector<int> state(5);
//用一个数字表示每一行的开关动作，用hash存这个数字代表的开关动作个数
int hash_action[33];
int action_base[33];

void preprocess() {
    for (int i = 0; i < 5; ++i) {
        state[i] = 0;
        for (int j = 0; j < 5; ++j) {
            if (init_state[i][j] == '1') {
                state[i] |= (1 << (4 - j));
            }
        }
    }
}

void calc_action_base() {
    int basis[5] = {3, 7, 14, 28, 24};
    for (int action = 0; action < (1 << 5); ++action) {
        hash_action[action] = 0;
        action_base[action] = 0;
        for (int i = 0; i < 5; ++i) {
            if (action & (1 << i)) {
                ++hash_action[action];
                action_base[action] ^= basis[i];
            }
        }
    }
}

void apply_row(int n_layer, vector<int>& state, int action) {
    if (n_layer - 2 >= 0) {
        state[n_layer - 2] ^= action;
    }
    if (n_layer < 5) {
        state[n_layer] ^= action;
    }
    state[n_layer - 1] ^= action_base[action];
}

int find_solution(int n_layer, vector<int>& current_state,
        int accumulate_action_num, const int max_action_num) {
    if (accumulate_action_num > max_action_num) {
        return INF;
    }
    if (n_layer == 6) {
        if (current_state[4] == (1 << 5) - 1) {
            return accumulate_action_num;
        } else {
            return INF;
        }
    }
    if (n_layer == 1) {
        int min_action_num = INF;
        // enumerate 2^5 possible actions
        for (int action = 0; action < (1 << 5); ++action) {
            vector<int> tmp_state(current_state);
            apply_row(n_layer, tmp_state, action);
            int res = find_solution(n_layer + 1, tmp_state,
                hash_action[action], max_action_num);
            if (res < min_action_num) {
                min_action_num = res;
            }
        }
        return min_action_num;
    }
    // 2~5 layer
    // 注意：取反之后取低5bit!!!
    int action = (~current_state[n_layer - 2]) & ((1 << 5) - 1); 
    apply_row(n_layer, current_state, action);
    return find_solution(n_layer + 1, current_state, 
            accumulate_action_num + hash_action[action], max_action_num); 
}

int main() {
    calc_action_base();
    int n;
    scanf("%d", &n);
    while (n--) {
        for (int i = 0; i < 5; ++i) {
            scanf("%s", init_state[i]);            
        }
        getchar();
        getchar();
        preprocess();
        int ret = find_solution(1, state, 0, 6);
        if (ret <= 6) {
            printf("%d\n", ret);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}
