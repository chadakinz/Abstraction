#pragma once
#include <cmath>
#include <iostream>
#include "get_equity_distribution.h"

Equity_Distribution get_equity_distribution(const std::array<int, 4>& public_cards,
                                            const Hand& private_cards, std::array<int, 52>& seen_cards) {

    float count = 0.0;
    int our_hand_rating, opp_hand_rating;

    float win = 0.0f, lose = 0.0f, tie = 0.0f;

    int private_card1_id = process_cards(private_cards[0]);
    int private_card2_id = process_cards(private_cards[1]);

    Equity_Distribution equity_histogram = {0.};


    for (int i = 0; i < NUM_DECK; i++) {
        if (seen_cards[i]) continue;
        seen_cards[i] = 1;
        for (const auto& opp_hand : all_possible_hands_int) {

            if (seen_cards[opp_hand[0]] || seen_cards[opp_hand[1]]) continue;

            our_hand_rating = evaluate_7cards(
                    private_card1_id, private_card2_id,
                    public_cards[0], public_cards[1],
                    public_cards[2], public_cards[3],
                    i
            );

            opp_hand_rating = evaluate_7cards(
                    opp_hand[0], opp_hand[1],
                    public_cards[0], public_cards[1],
                    public_cards[2], public_cards[3],
                    i
            );

            if (our_hand_rating < opp_hand_rating) win++;
            else if (our_hand_rating > opp_hand_rating) lose++;
            else tie++;


        }

        float total = win + lose + tie;
        float equity = win / total + 0.5f * (tie / total);

        int bucket = std::min(
                (int)(equity * equity_histogram.size()),
                (int)equity_histogram.size() - 1
        );

        equity_histogram[bucket] += 1;

        seen_cards[i] = 0;
        win = lose = tie = 0.0f;
        count++;
    }

    for (auto& v : equity_histogram) {
        v /= count;
    }

    return equity_histogram;
}

/*
int main(){
    Hand private_cards = {Card{'3', 's'}, Card{'K', 'c'}};
    std::array<Card, 4> public_cards = {Card{'A', 'h'}, Card{'7', 'd'}, Card{'2', 's'}, Card{'8', 'd'}};
    Equity_Distribution ed = get_equity_distribution(public_cards, private_cards);
    for (size_t i = 0; i < ed.size(); ++i) {
        std::cout << "Bucket " << i << ": " << ed[i] << '\n';
    }
    return 0;
    }

*/