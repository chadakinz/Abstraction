#ifndef C_CARD
#define C_CARD
struct Card {
    char rank;
    char suit;

    constexpr bool operator==(const Card& other) const {
        return rank == other.rank && suit == other.suit;
    }
};
#endif