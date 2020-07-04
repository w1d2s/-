#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <unordered_map>

#define MAX_N 200005

int a[MAX_N], b[MAX_N], c[MAX_N];

struct Movie {
    int idx;
    int cnt_b, cnt_c;
    Movie() {}
    Movie(int _idx, int _cnt_b, int _cnt_c) :
        idx(_idx), cnt_b(_cnt_b), cnt_c(_cnt_c) {}
    bool operator<(const Movie& rhs) {
        if (cnt_b == rhs.cnt_b) {
            return cnt_c >= rhs.cnt_c;
        }
        return cnt_b >= rhs.cnt_b;
    }
};

Movie movies[MAX_N];
std::unordered_map<int, int> lang_cnt;

int main() {
    int n, m;
    while (scanf("%d", &n) != EOF) {
        memset(movies, 0, sizeof(movies));
        lang_cnt.clear();
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            if (lang_cnt.find(a[i]) == lang_cnt.end()) {
                lang_cnt[a[i]] = 1;
            } else {
                ++lang_cnt[a[i]];
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d", &b[i]);
            if (lang_cnt.find(b[i]) == lang_cnt.end()) {
                lang_cnt[b[i]] = 0;
            }
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d", &c[i]);
            if (lang_cnt.find(c[i]) == lang_cnt.end()) {
                lang_cnt[c[i]] = 0;
            }
        }
        for (int i = 0; i < m; ++i) {
            movies[i].idx = i + 1;
            movies[i].cnt_b = lang_cnt[b[i]];
            movies[i].cnt_c = lang_cnt[c[i]];
        }
        std::sort(movies, movies + m);
        printf("%d\n", movies[0].idx);
    }
    return 0;
}
