#pragma once
#include <array>
#include "objects.hpp"
template<std::size_t N>
inline void populate_seen_cards(const std::array<Card, N>& cards, std::array<int, 52>& seen_cards){
    for(std::size_t i = 0; i < N; i++){
        seen_cards[process_cards(cards[i])] = 1;
    }
}
template<std::size_t N>
inline void unpopulate_seen_cards(const std::array<Card, N>& cards, std::array<int, 52>& seen_cards){
    for(std::size_t i = 0; i < N; i++){
        seen_cards[process_cards(cards[i])] = 0;
    }
}