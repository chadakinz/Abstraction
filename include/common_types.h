
#ifndef COMMON_TYPES
#define COMMON_TYPES

#include "c_card.h"
#include <array>
#include <vector>

using OCHS = std::array<float, 8>;
using Hand = std::array<Card, 2>;
using Deck = std::array<Card, 52>;
using CardSet = std::vector<Card>;
using HandInt = std::array<int, 2>;




#endif