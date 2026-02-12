#include <catch2/catch_test_macros.hpp>
#include "get_equity_distribution.h"
#include "canonical.h"
#include "objects.hpp"
#include "helper_functions.hpp"

TEST_CASE("same equity distributions for canonical hands", "[equity_distribution]"){
    Equity_Distribution eq_dist1;
    std::array<Card, 4> hand1 = {
            Card{'A','s'},
            Card{'K','s'},
            Card{'Q','h'},
            Card{'J','h'}
    };

    std::array<int, 52> seen_cards;
    populate_seen_cards(hand1, seen_cards);

    for(const Hand& hand: all_possible_hands){
        populate_seen_cards(hand, seen_cards);

    }

    std::array<Card, 4> hand2 = {
            Card{'A','d'},
            Card{'K','d'},
            Card{'Q','h'},
            Card{'J','h'}
    };

    std::array<Card, 4> hand1 = {
            Card{'A','c'},
            Card{'K','c'},
            Card{'Q','s'},
            Card{'J','s'}
    };
}