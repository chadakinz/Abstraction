#ifndef CONSTANTS
#define CONSTANTS

inline constexpr char ranks[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
inline constexpr char suits[] = {'c','d','h','s'};
inline const Deck full_deck = [] {
    Deck deck{};

    std::size_t idx = 0;
    for (char r : ranks) {
        for (char s : suits) {
            deck[idx++] = Card{r, s};
        }
    }
    return deck;
}();

#endif