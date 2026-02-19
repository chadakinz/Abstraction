#include <catch2/catch_test_macros.hpp>
#include "get_equity_distribution.h"
#include "canonical.h"
#include "objects.hpp"
#include "helper_functions.hpp"
#include <unordered_set>
#include <iostream>
#include <iomanip>
#include "c_card.h"
#include "constants.h"

void printCards(const Hand& cards) {
    for (const auto& card : cards) {
        std::cout << card.rank << card.suit << " ";
    }
    std::cout << std::endl;
}

void printArray(const std::array<float,10>& a) {
    std::cout << "[ ";
    for (float v : a) std::cout << std::fixed << std::setprecision(3) << v << " ";
    std::cout << "]";
}

struct EquityDistributionHash {
    std::size_t operator()(const std::array<float,10>& a) const {
        std::size_t h = 0;
        for (float v : a)
            h ^= std::hash<float>{}(v) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};


TEST_CASE("equity_distribtion", "[equity_distribution]"){
    std::array<int, 52> seen_cards = {0};
    Hand private_cards = {Card{'2', 'c'}, Card('2', 'h')};

    populate_seen_cards(private_cards, seen_cards);
    std::array<Card, 4> hand1 = {
            Card{'A','s'},
            Card{'K','s'},
            Card{'Q','h'},
            Card{'J','h'}
    };
    populate_seen_cards(hand1, seen_cards);
    std::array<int, 4> int_hand1;
    for (int i = 0; i < 4; i ++){
    int_hand1[i] = process_cards(hand1[i]);
    }
    Equity_Distribution eq_dist1 = get_equity_distribution(int_hand1, private_cards, seen_cards);
    unpopulate_seen_cards(hand1, seen_cards);


    std::array<Card, 4> hand2 = {
            Card{'A','d'},
            Card{'K','d'},
            Card{'Q','h'},
            Card{'J','h'}
    };
    populate_seen_cards(hand2, seen_cards);



    std::array<int, 4> int_hand2;
    for (int i = 0; i < 4; i ++){
    int_hand2[i] = process_cards(hand2[i]);
    }
    Equity_Distribution eq_dist2 = get_equity_distribution(int_hand2, private_cards, seen_cards);
    printArray(eq_dist1);
    REQUIRE(eq_dist1 == eq_dist2);
}
TEST_CASE("same equity distributions for canonical hands", "[equity_distribution]"){
    Equity_Distribution eq_dist1;
    std::array<Card, 4> hand1 = {
            Card{'A','s'},
            Card{'K','s'},
            Card{'Q','h'},
            Card{'J','h'}
    };
    std::array<int, 4> int_hand1;
    for (int i = 0; i < 4; i ++){
        int_hand1[i] = process_cards(hand1[i]);
    }
    std::unordered_set<Equity_Distribution, EquityDistributionHash> test_set1;
    std::array<int, 52> seen_cards = {0};
    populate_seen_cards(hand1, seen_cards);

    for(const Hand& hand: all_possible_hands){
        populate_seen_cards(hand, seen_cards);
        Equity_Distribution eq_dist = get_equity_distribution(int_hand1, hand, seen_cards);
        test_set1.insert(eq_dist);
        unpopulate_seen_cards(hand, seen_cards);
    }

    unpopulate_seen_cards(hand1, seen_cards);

    std::array<Card, 4> hand2 = {
            Card{'A','d'},
            Card{'K','d'},
            Card{'Q','h'},
            Card{'J','h'}
    };

    std::array<int, 4> int_hand2;
    for (int i = 0; i < 4; i ++){
        int_hand2[i] = process_cards(hand2[i]);
    }
    std::unordered_set<Equity_Distribution, EquityDistributionHash> test_set2;
    populate_seen_cards(hand2, seen_cards);

    for(const Hand& hand: all_possible_hands){
        populate_seen_cards(hand, seen_cards);
        Equity_Distribution eq_dist = get_equity_distribution(int_hand2, hand, seen_cards);
        test_set2.insert(eq_dist);
        if (test_set1.find(eq_dist) == test_set1.end()) {
            printCards(hand);
        }

        unpopulate_seen_cards(hand, seen_cards);
    }

    unpopulate_seen_cards(hand2, seen_cards);

    REQUIRE(test_set1 == test_set2);

}