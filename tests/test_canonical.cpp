#include <catch2/catch_test_macros.hpp>
#include "canonical.h"
//test on multiple canonical hands
TEST_CASE("test_get_canonical_hand", "[canonical]"){

    std::array<Card, 4> hand1 = {
            Card{'A','s'},
            Card{'K','s'},
            Card{'Q','h'},
            Card{'J','h'}
    };

    std::array<Card, 4> hand2 = {
            Card{'A','d'},
            Card{'K','d'},
            Card{'Q','c'},
            Card{'J','c'}
    };

    REQUIRE(canonicalize_cards(hand1) == canonicalize_cards(hand2));
    std::array<Card, 4> hand3 = {
            Card{'A','s'},
            Card{'K','h'},
            Card{'Q','d'},
            Card{'J','c'}
    };

    REQUIRE(canonicalize_cards(hand3) != canonicalize_cards(hand1));

    std::array<Card, 4> hand4 = {
            Card{'A','c'},
            Card{'K','s'},
            Card{'Q','d'},
            Card{'J','h'}
    };

    REQUIRE(canonicalize_cards(hand3) == canonicalize_cards(hand4));
    std::array<Card, 4> hand5 = {
            Card{'A','c'},
            Card{'K','s'},
            Card{'Q','d'},
            Card{'T','h'}
    };
    REQUIRE(canonicalize_cards(hand5) != canonicalize_cards(hand4));

}
