//
// Created by Chad Gothelf on 1/3/26.
//

#ifndef POKAH_RIVER_ABSTRACTION_H
#define POKAH_RIVER_ABSTRACTION_H


#include <array>
#include <string_view>
#include <unordered_map>
#include <string>
#include <utility>
#include "c_card.h"
#include "types.h"
#include "constants.h"
#include "hand_groups.hpp"



int card_to_id(const Card& c) {
    char ranks[] = "23456789TJQKA";
    char suits[] = "cdhs";

    auto rank_index = std::find(std::begin(ranks), std::end(ranks), c.rank) - std::begin(ranks);
    auto suit_index = std::find(std::begin(suits), std::end(suits), c.suit) - std::begin(suits);

    return suit_index * 13 + rank_index; // 0..51
}

int process_cards(const Card& card){
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
#endif //POKAH_RIVER_ABSTRACTION_H
