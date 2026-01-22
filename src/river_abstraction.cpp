#include <objects.hpp>


std::vector<Hand> remove_impossible_hands(CardSet cards) {
    CardSet possible_hands;
    possible_hands.reserve(1326);
    std::array<int, 52> deck{}; // all initialized to 0

    // mark turn cards as used
    for (const auto &c: turn_cards) {
        int id = card_to_id(c);
        deck[id] = 1; // used
    }

    // iterate over all possible pairs of remaining cards
    for (size_t i = 0; i < all_cards.size(); ++i) {
        int id_i = card_to_id(all_cards[i]);
        if (deck[id_i] == 1) continue; // skip used

        for (size_t j = i + 1; j < all_cards.size(); ++j) {
            int id_j = card_to_id(all_cards[j]);
            if (deck[id_j] == 1) continue; // skip used
            possible_hands.push_back({all_cards[i], all_cards[j]})
        }

    }
    return possible_hands;
}
std::vector<OCHS> get_turn_data(const CardSet& turn_cards){
    std::vector<Card> layout;
    std::vector<Hand> possible_hands = remove_impossible_hands(turn_cards);
    std::vector<int> processed_river;
    std::vector<OCHS> storage;
    OCHS OCHS_placeholder;
    CardSet river;

    int our_hand_val, range_hand_val;
    int win = 0;
    int total = 0;
    int OCHS_index = 0;
    for (int i = 0; i < turn_cards.size(); i++){
        for(int j = 0; j<full_deck.size(); j++){
            if (turn_cards[i] == full_deck[j]){
                continue;
            }
            river = turn_cards + full_deck[j];
            for (auto const& possible_hand : possible_hands) {
                for (auto const &group: HAND_GROUPS) {
                    for (auto const &hand: group) {
                        processed_river = {process_cards(river[0]),
                                           process_cards(river[1]), process_cards(river[2]), process_cards(river[3]),
                                           process_cards(river[4])};
                        our_hand_val = evaluate_7cards(process_cards(possible_hand[0]), process_cards(possible_hand[1]), processed_river[0],
                                        processed_river[1],
                                        processed_river[2], processed_river[3], processed_river[4]);
                        range_hand_val = evaluate_7cards(process_cards(hand[0]), process_cards(hand[1]), processed_river[0],
                                        processed_river[1],
                                        processed_river[2], processed_river[3], processed_river[4]);
                        if (range_hand_val > our_hand_val){
                            win += 1;
                        }
                        total += 1;
                    }

                    OCHS_placeholder[OCHS_index] = (float)win/total;
                    OCHS_index += 1;
                    total = 0;
                    win = 0;

                }
                OCHS_index = 0;
                storage.emplace_back(OCHS_placeholder);


            }

        }
    }
    return storage;


}