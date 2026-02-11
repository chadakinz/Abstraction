//
// Created by Chad Gothelf on 1/3/26.
//

#ifndef OBJECTS
#define OBJECTS


#include <array>
#include <string_view>
#include <unordered_map>
#include <string>
#include <utility>
#include "c_card.h"
#include "common_types.h"
#include "constants.h"
#include "hand_groups.hpp"


inline constexpr int process_cards(const Card& card){
    char rank = card.rank;
    int rank_val;
    char suit = card.suit;
    int suit_val;
    if (rank == 'T') rank_val = 8;
    else if (rank == 'J') rank_val = 9;
    else if (rank == 'Q') rank_val = 10;
    else if (rank == 'K') rank_val = 11;
    else if (rank == 'A') rank_val = 12;
    else{
        rank_val = rank - ('0' + 2);
    }
    if (suit == 'c') suit_val = 0;
    else if (suit == 'd') suit_val = 1;
    else if (suit == 'h') suit_val = 2;
    else if (suit == 's') suit_val = 3;

    return rank_val*4 + suit_val;
}

static constexpr std::array<Hand, 1326> init_all_possible_hands(){
    std::array<Hand, 1326> all_possible_hands{};
    int count = 0;
    for (int i = 0; i < NUM_DECK - 1; i++){
        for(int j = i + 1; j < NUM_DECK; j++){
            all_possible_hands[count ++] = {full_deck[i], full_deck[j]};
        }
    }
    return all_possible_hands;
}

inline constexpr std::array<Hand, 1326> all_possible_hands = init_all_possible_hands();

static constexpr std::array<HandInt, 1326> init_all_possible_hands_int() {
    std::array<HandInt, 1326> all_possible_hands{};
    int count = 0;

    for (int i = 0; i < NUM_DECK - 1; ++i) {
        for (int j = i + 1; j < NUM_DECK; ++j) {
            all_possible_hands[count++] = {
                    process_cards(full_deck[i]),
                    process_cards(full_deck[j])
            };
        }
    }

    return all_possible_hands;
}

// compile-time initialization
inline constexpr std::array<HandInt, 1326> all_possible_hands_int = init_all_possible_hands_int();
#endif
