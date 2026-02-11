//
// Created by Chad Gothelf on 2/10/26.
//

#ifndef POKAH_CANONICAL_HANDS_H
#define POKAH_CANONICAL_HANDS_H
#include <algorithm>
#include "canonical.h"
#include "objects.hpp"
#include "constants.h"


inline constexpr int NUM_UNIQUE_4CARD = 16432;

static std::array<std::array<int, 4>, NUM_UNIQUE_4CARD>
generate_all_canonical_4card_hands()
{
    std::array<std::array<int, 4>, NUM_UNIQUE_4CARD> all_unique_four_cards;
    int count = 0;
    const int N = full_deck.size();

    for (int i = 0; i < NUM_DECK; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            for (int k = j + 1; k < N; ++k)
            {
                for (int l = k + 1; l < N; ++l)
                {
                    std::array<Card, 4> hand = {
                            full_deck[i],
                            full_deck[j],
                            full_deck[k],
                            full_deck[l]
                    };
                    std::array<int, 4> int_hand = {
                            process_cards(full_deck[i]),
                            process_cards(full_deck[j]),
                            process_cards(full_deck[k]),
                            process_cards(full_deck[l])
                    };
                    CanonicalHand canonical = canonicalize_cards(hand);
                    if (canonical_hands_set.find(canonical) == canonical_hands_set.end()) {
                        // Not found → insert it
                        canonical_hands_set.insert(canonical);
                        all_unique_four_cards[count++] = int_hand;

                    } else continue;

                }
                }
            }
        }
    return all_unique_four_cards;
}

inline const std::array<std::array<int, 4>, NUM_UNIQUE_4CARD> all_canon_4card = generate_all_canonical_4card_hands();
#endif //POKAH_CANONICAL_HANDS_H
