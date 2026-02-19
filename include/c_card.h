#ifndef C_CARD
#define C_CARD



struct Card {
    char rank = '?';  // sentinel for “empty card”
    char suit = '?';

    constexpr Card() = default; // allows default construction
    constexpr Card(char r, char s) : rank(r), suit(s) {}

    constexpr bool operator==(const Card& other) const {
        return rank == other.rank && suit == other.suit;
    }
};


inline constexpr Card EMPTY_CARD = Card{'?', '?'};

#endif