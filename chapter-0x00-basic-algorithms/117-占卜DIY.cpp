#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

struct Card {
    char val;
    bool is_up;
    int num;
    
    Card(char _v, bool _is_up): val(_v), is_up(_is_up) {
        if ('2' <= _v && _v <= '9') {
            num = _v - '0';
        } else if ('0' == _v) {
            num = 10;
        } else if ('A' == _v) {
            num = 1;
        } else if ('J' == _v) {
            num = 11;
        } else if ('Q' == _v) {
            num = 12;
        } else if ('K' == _v) {
            num = 13;
        } else {
            printf("wrong val!\n");
        }
    }

    Card& operator=(const Card& rhs) {
        if (this != &rhs) {
            val = rhs.val;
            is_up = rhs.is_up;
            num = rhs.num;
        }
        return *this;
    }

    void print_card() {
        if (is_up) {
            printf("card : %c, up, %d\n", val, num);
        } else {
            printf("card : %c, down, %d\n", val, num);
        }
    }
};

bool play_one_life(vector<deque<Card>>& card_piles,
                   unordered_map<char, int>& up_count,
                   int& pair_num) {
    auto& life_pile = card_piles[13];
    
    if (life_pile.empty()) { return false; }
    
    Card cur_card = life_pile.front();
    life_pile.pop_front();
  
    while (cur_card.val != 'K') {
        int pile_id = cur_card.num;
        
        cur_card.is_up = true;
        card_piles[pile_id].push_front(cur_card);
        
        if (up_count.find(cur_card.val) != up_count.end()) {
            ++up_count[cur_card.val];
        } else {
            up_count[cur_card.val] = 1;
        }
        if (up_count[cur_card.val] == 4) {
            ++pair_num;
        }

        cur_card = card_piles[pile_id].back();
        card_piles[pile_id].pop_back();
    }
    return true;
}


int main() {
    vector<deque<Card>> card_piles;
    unordered_map<char, int> up_count;
    int pair_num = 0;

    card_piles.emplace_back(deque<Card>());
    for (int i = 1; i <= 13; ++i) {
        card_piles.emplace_back(deque<Card>());
        auto& cur_pile = card_piles[i];
        char a, b, c, d;
        scanf("%c %c %c %c", &a, &b, &c, &d);
        getchar();
        cur_pile.emplace_back(a, false);
        cur_pile.emplace_back(b, false);
        cur_pile.emplace_back(c, false);
        cur_pile.emplace_back(d, false);
    }
    
    while (true) {
        bool ret = play_one_life(card_piles, up_count, pair_num);
        if (!ret) { break; }
    }

    printf("%d\n", pair_num);

    return 0;
}
