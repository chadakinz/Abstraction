#pragma once
#include "canonical.h"
#include <array>
#include <vector>
#include <set>
#include <iostream>
#include "constants.h"
#include "canonical_hands.hpp"

 uint64_t hash_canonical_hand(const CanonicalHand& hand) {
    uint64_t hash = 0;
    for (const auto& suit_bucket : hand) {
        for (int rank : suit_bucket) {
            hash = hash * 15 + static_cast<uint64_t>(rank);
        }
    }
    return hash;
}
inline void sort_by_largest(std::array<int, 4>& container, int value) {
    for (size_t i = 0; i < container.size(); ++i) {

        // Empty slot → place and return
        if (container[i] == 0) {
            container[i] = value;
            return;
        }

        // Normal sorted insert
        if (value > container[i]) {
            for (size_t j = container.size() - 1; j > i; --j) {
                container[j] = container[j - 1];
            }
            container[i] = value;
            return;
        }
    }
}

std::array<std::array<int, 4>, 4> canonicalize_cards(const std::array<Card,4>& cards){
    std::array<std::array<int, 4>, 4> buckets{};
    for(int i = 0; i < cards.size(); i++){
        sort_by_largest(buckets[suit_index(cards[i].suit)], rank_index(cards[i].rank));
    }

    std::sort(buckets.begin(), buckets.end(),
              [](const std::array<int,4>& a, const std::array<int,4>& b) {
                  for (int i = 0; i < 4; i++) {
                      if (a[i] != b[i])
                          return a[i] > b[i];   // descending
                  }
                  return false; // equal
              }
    );
    return buckets;
}


/*
int main() {
    // stores unique canonical hands
    printf("size of unique canonical hands: %zu", all_canon_4card.size());
    for(int i = 0; i < NUM_UNIQUE_4CARD; i++){
        for (int j = 0; j < 4; j++){
            if(all_canon_4card[i][j].suit == '?'|| all_canon_4card[i][j].rank == '?'){
                printf("EMPTY\n");
            }
            else continue;
        }
    }


    return 0;
}
*/