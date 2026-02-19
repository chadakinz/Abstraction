#pragma once
#include <unordered_set>
#include "c_card.h"
#include "turn_abstraction_constants.hpp"
#include <algorithm>
#include "turn_abstraction_types.h"


uint64_t hash_canonical_hand(const CanonicalHand& hand);

inline void sort_by_largest(std::array<int, 4>& container, int value);

CanonicalHand canonicalize_cards(const std::array<Card,4>& cards);

struct CanonicalHandHash{
    std::size_t operator()(const CanonicalHand& hand) const noexcept{
        return hash_canonical_hand(hand);
    }
};

inline std::unordered_set<CanonicalHand,CanonicalHandHash> canonical_hands_set;
int canonical_hand_weight(const CanonicalHand& canonical_hand);