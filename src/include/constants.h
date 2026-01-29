
#ifndef CONSTANTS
#define CONSTANTS

#include "c_card.h"
#include "types.h"


inline constexpr char ranks[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
inline constexpr char suits[] = {'c','d','h','s'};
inline constexpr int NUM_RANKS = 13;
inline constexpr int NUM_SUITS = 4;
inline constexpr int NUM_DECK = 52;
inline constexpr int NUM_TURN_CARDS = 4;
inline constexpr int NUM_RIVER_CARDS = 5;
static constexpr Deck init_deck(){
    Deck deck{};
    int idx = 0;
    for(int i = 0; i < NUM_RANKS; i++){
        for(int j = 0; j < NUM_SUITS; j++){
            deck[idx++] = Card{ranks[i], suits[j]};
        }
    }
    return deck;
}
inline constexpr Deck full_deck = init_deck();

#endif