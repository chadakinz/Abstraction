//
// Created by Chad Gothelf on 1/3/26.
//

#ifndef POKAH_RIVER_ABSTRACTION_H
#define POKAH_RIVER_ABSTRACTION_H

#endif //POKAH_RIVER_ABSTRACTION_H
#include <array>
#include <string_view>
struct Card {
    char rank;
    char suit;

    constexpr bool operator==(const Card& other) const {
        return rank == other.rank && suit == other.suit;
    }
};
using OCHS = std::array<float, 8>;
using Hand = std::array<Card, 2>
using Deck = std::array<Card, 52>;
using CardSet = std::vector<Card>;

constexpr int card_to_id(const Card& c) {
    constexpr char ranks[] = "23456789TJQKA";
    constexpr char suits[] = "cdhs";

    auto rank_index = std::find(std::begin(ranks), std::end(ranks), c.rank) - std::begin(ranks);
    auto suit_index = std::find(std::begin(suits), std::end(suits), c.suit) - std::begin(suits);

    return suit_index * 13 + rank_index; // 0..51
}

static const Deck full_deck = [] {
    CardSet deck{};
    constexpr char ranks[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
    constexpr char suits[] = {'c','d','h','s'};

    std::size_t idx = 0;
    for (char r : ranks) {
        for (char s : suits) {
            deck[idx++] = Card{r, s};
        }
    }
    return deck;
}();
constexpr std::array<std::string_view, 8> HAND_GROUPS = {
                                                                 "32s, 42s, 52s, 62s, 72s, 43s, 53s, 63s, 73s, 54s, 64s, 32o, 42o, 52o, 62o, 72o, 82o, 43o, 53o, 63o, 73o, 83o, 54o, 64o, 74o, 65o",
                                                                 "82s, 92s, T2s, 83s, 93s, 74s, 84s, 94s, 92o, T2o, J2o, 93o, T3o, J3o, 84o, 94o, T4o, 75o, 85o, 95o, T5o",
                                                                 "T3s, T4s, 65s, 75s, 85s, 95s, T5s, 76s, 86s, 96s, T6s, 87s, 97s, 98s, 76o, 86o, 96o, T6o, 87o, 97o, T7o, 98o, T8o",
                                                                 "22, J2s, Q2s, K2s, J3s, Q3s, J4s, Q4s, J5s, Q5s, J6s, Q2o, K2o, Q3o, K3o, J4o, Q4o, K4o, J5o, Q5o, J6o, Q6o, J7o, Q7o",
                                                                 "Q6s, T7s, J7s, Q7s, T8s, J8s, Q8s, T9s, J9s, Q9s, JTs, J8o, Q8o, T9o, J9o, Q9o, JTo, QTo, QJo",
                                                                 "33, 44, 55, A2s, K3s, A3s, K4s, A4s, K5s, A5s, K6s, A6s, K7s, K8s, A2o, A3o, A4o, K5o, A5o, K6o, A6o, K7o, A7o, K8o, A8o, K9o",
                                                                 "66, 77, A7s, A8s, K9s, A9s, QTs, KTs, ATs, QJs, KJs, AJs, KQs, AQs, AKs, A9o, KTo, ATo, KJo, AJo, KQo, AQo, AKo",
                                                                 "88, 99, TT, JJ, QQ, KK, AA"
                                                         };



