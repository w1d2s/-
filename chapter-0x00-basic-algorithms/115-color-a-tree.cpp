#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_N 1010

struct Vertex {
    int idx;
    int in_degree;
    int w;
    int max_w_subtree;
    std::vector<int> child;
    Vertex() {}
    void assign(int _idx, int _w) {
        idx = _idx, w = _w, max_w_subtree = _w;
    }
    bool operator<(const Vertex& rhs) const {
        return max_w_subtree < rhs.max_w_subtree;
    }
    bool is_zero_in_degree() const {
        return in_degree == 0;
    }
    void inc_in_degree() {
        ++in_degree;
    }
    void dec_in_degree() {
        --in_degree;
    }
    void add_child(int _idx) {
        child.push_back(_idx);
    }
    int get_child_size() const {
        return child.size();
    }
    int get_ith_child_idx(int i) const {
        return child[i];
    }
};

Vertex v[MAX_N];

struct cmp {
    bool operator()(int a, int b) {
        return v[a].max_w_subtree < v[b].max_w_subtree;
    }
};

void debug_print_vertex(const Vertex& v) {
    printf("idx : %d, w : %d, in_degree : %d, max_w_subtree : %d\n", v.idx, v.w, v.in_degree, v.max_w_subtree);
    printf("  child : ");
    for (int j = 0; j < v.get_child_size(); ++j) {
        printf("%d ", v.get_ith_child_idx(j));
    }
    printf("\n");
}

void dfs(int r) {
    if (v[r].get_child_size() == 0) {
        return;
    }
    int max_w_subtree = v[r].max_w_subtree;
    for (int i = 0; i < v[r].get_child_size(); ++i) {
        int child_idx = v[r].get_ith_child_idx(i); 
        dfs(child_idx);
        v[r].max_w_subtree = std::max(v[r].max_w_subtree, v[child_idx].max_w_subtree);
    }
}

long long topo_sort(int root_idx) {
    printf("==== enter topo sort ====\n");
    int cur_t = 1;
    long long score = 0;
    std::priority_queue<int, std::vector<int>, cmp> vertexes_zero_in_degree;
    vertexes_zero_in_degree.push(root_idx);
    while (!vertexes_zero_in_degree.empty()) {
        int idx = vertexes_zero_in_degree.top();
        //debug_print_vertex(v[idx]);
        vertexes_zero_in_degree.pop();
        score += cur_t * v[idx].w;
        ++cur_t;
        for (int i = 0; i < v[idx].get_child_size(); ++i) {
            int child_idx = v[idx].get_ith_child_idx(i);
            v[child_idx].dec_in_degree();
            if (v[child_idx].is_zero_in_degree()) {
                vertexes_zero_in_degree.push(child_idx);
            }
        }
    }
    return score;
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    memset(v, 0, sizeof(v));
    for (int i = 1; i <= n; ++i) {
        int w;
        scanf("%d", &w);
        v[i].assign(i, w);
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        v[a].add_child(b);
        v[b].inc_in_degree();
    }
    dfs(r);
    //for (int i = 1; i <= n; ++i) {
    //    debug_print_vertex(v[i]);
    //}

    long long score = topo_sort(r);
    printf("%lld\n", score);
    return 0;
}
