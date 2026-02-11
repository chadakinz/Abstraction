#ifndef GET_EQUITY
#define GET_EQUITY

#include "turn_abstraction_types.h"
#include "common_types.h"
#include "objects.hpp"
#include "phevaluator/phevaluator.h"

Equity_Distribution get_equity_distribution(const std::array<int, 4>& public_cards,
                                            const Hand& private_cards, std::array<int, 52>& seen_cards);
#endif