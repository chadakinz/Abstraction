#include <objects.hpp>
#include <phevaluator/phevaluator.h>
#include <iostream>

static inline std::array<int, 52> populate_array_for_public_cards(const std::array<Card, 4>& public_turn_cards){
    std::array<int, 52> deck{};
    for (const auto &c: public_turn_cards) {
        int id = process_cards(c);
        deck[id] = 1; // used
    }
    return deck;
}

//todo: rename deck
std::array<Hand, 1326> remove_impossible_hands(const std::array<Card, 4>& cards, const std::array<int, 52>& deck) {
    std::array<Hand, 1326> possible_hands{};
     // all initialized to 0
    int count = 0;
    // mark turn cards as used


    // iterate over all possible pairs of remaining cards
    for (size_t i = 0; i < NUM_DECK - 1; i++) {
        int id_i = process_cards(full_deck[i]);
        if (deck[id_i] == 1) continue; // skip used
        for (size_t j = i + 1; j < NUM_DECK; j++) {
            int id_j = process_cards(full_deck[j]);
            if (deck[id_j] == 1) continue; // skip used
            possible_hands[count++] = {full_deck[i], full_deck[j]};
        }
    }
    return possible_hands;
}
std::vector<OCHS> get_turn_data(const std::array<Card, 4>& turn_cards){
    std::array<int, 52> deck = populate_array_for_public_cards(turn_cards);
    std::array<Hand, 1326> possible_hands = remove_impossible_hands(turn_cards, deck);
    std::array<int, 5> processed_river{};
    std::vector<OCHS> storage;
    OCHS OCHS_placeholder;

    int our_hand_val, range_hand_val;
    float win = 0.;
    float total = 0.;
    int OCHS_index = 0;

    //todo: when iterating through handgroups i need to make sure i am skipping impossible hand combos based off of out
    // hand and the cards on the table
    for(int j = 0; j < NUM_DECK; j++){
        if (deck[process_cards(full_deck[j])] == 1) continue;
        for (auto const& possible_hand : possible_hands) {
            if(possible_hand[0].rank == '?') continue;
            for (auto const &group: HAND_GROUPS) {
                for (auto const &hand: HANDGROUPS_TO_CARDSETS[handgroup_to_int(group)]) {
                    processed_river = {process_cards(turn_cards[0]),
                                       process_cards(turn_cards[1]), process_cards(turn_cards[2]), process_cards(turn_cards[3]),
                                       process_cards(full_deck[j])};
                    our_hand_val = evaluate_7cards(process_cards(possible_hand[0]), process_cards(possible_hand[1]), processed_river[0],
                                    processed_river[1],
                                    processed_river[2], processed_river[3], processed_river[4]);
                    range_hand_val = evaluate_7cards(process_cards(hand[0]), process_cards(hand[1]), processed_river[0],
                                    processed_river[1],
                                    processed_river[2], processed_river[3], processed_river[4]);
                    if (range_hand_val > our_hand_val){
                        win += 1.;
                    }
                    total += 1.;
                }
                //printf("win: %d, total %d\n", win, total);

                OCHS_placeholder[OCHS_index] = (float)win/total;
                OCHS_index += 1;
                total = 0;
                win = 0;

            }
            OCHS_index = 0;
            storage.emplace_back(OCHS_placeholder);
        }
    }
    return storage;
}

int main(){
    std::array<Card, 4> turn_cards = {Card{'T', 's'}, Card{'K', 's'}, Card{'T', 'd'}, Card{'3', 'h'}};
    std::vector<OCHS> turn_data_abstraction = get_turn_data(turn_cards);
    for(int i = 0; i < turn_data_abstraction.size(); i++){
        std::cout << "[ ";
        for(int j = 0; j < 8; j++){
            std::cout << turn_data_abstraction[i][j] << ", ";
        }
        std::cout << " ]\n";
    }
    printf("Data size: %zu\n", turn_data_abstraction.size());

    return 0;
}
