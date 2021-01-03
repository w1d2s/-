#include <stdio.h>
#include <cmath>
#include <cstring>
#include <vector>

typedef unsigned long long ull;

const int N = 1000010;
const int P = 131;

char dna[N]; // index starts from 0
ull P_base[N] = {1};

void PreProcessPrefixHash(const char* str,
                          const int length,
                          std::vector<ull>& prefix_hash) {
  prefix_hash.resize(length + 5, 0);
  for (int i = 1; i <= length; ++i) {
    // Note : deal with start index carefully (0 or 1).
    prefix_hash[i] = prefix_hash[i - 1] * P + static_cast<ull>(str[i - 1] - 'a');
    P_base[i] = P_base[i - 1] * P;
  }
}

ull QuerySubStrHash(const std::vector<ull>& prefix_hash,
                    const int l, const int r) {
  // Note : assume l and r in valid range.
  ull substr_hash = prefix_hash[r] - prefix_hash[l - 1] * P_base[r - l + 1];
  return substr_hash;
}

int main() {
  int m;
  memset(dna, 0, sizeof(dna));
  scanf("%s", dna);
  const int len = strlen(dna);
  scanf("%d", &m);
  std::vector<ull> prefix_hash;
  PreProcessPrefixHash(dna, len, prefix_hash);
  for (int i = 0; i < m; ++i) {
    int l1, r1, l2, r2;
    scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
    ull hash1 = QuerySubStrHash(prefix_hash, l1, r1);
    ull hash2 = QuerySubStrHash(prefix_hash, l2, r2);
    if (hash1 == hash2) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
