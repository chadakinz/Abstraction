#include "hand_groups.hpp"
#include <string_view>
#include <utility>
#include <iostream>
//Methods for tabulating handgroups. A handgroup is a group of preflop hands. For example 43s is the group of preflop
//cards including 4h3h, 4c3c, 4s3s, 4d3d


// 6 combinations for pocket pairs
constexpr static std::array<std::pair<char, char>, 6> PAIR_SUITS = {{{'c','d'}, {'c','h'}, {'c','s'}, {'d','h'}, {'d','s'}, {'h','s'}
                                                             }};

// 4 combinations for suited hands
constexpr static std::array<std::pair<char,char>, 4> SUITED_SUITS = {{{'c','c'}, {'d','d'}, {'h','h'}, {'s','s'}
                                                              }};

// 12 combinations for offsuit hands
constexpr static std::array<std::pair<char,char>, 12> OFFSUIT_SUITS = {{
                                                                        {'c','d'}, {'c','h'}, {'c','s'}, {'d','c'}, {'d','h'}, {'d','s'},
                                                                        {'h','c'}, {'h','d'}, {'h','s'}, {'s','c'}, {'s','d'}, {'s','h'}
                                                                }};

constexpr std::array<Hand, 12> process_handgroup(const std::string_view& hand_group){

    std::array<Hand, 12> cardset;
    //Iterate through pair suits
    if(hand_group.size() < 2){
        for(int i = 0; i < 12; i++) {
            cardset[i] = {EMPTY_CARD, EMPTY_CARD};
        }
    }
    else if(hand_group[0] == hand_group[1]) {
        for (int i = 0; i < PAIR_SUITS.size(); i++) {
            cardset[i] = {Card{hand_group[0], PAIR_SUITS[i].first}, Card{hand_group[1], PAIR_SUITS[i].second}};
        }
        //Fill in the rest of the array with the empty hand type
        for (int i = PAIR_SUITS.size(); i < 12; i++) {
            cardset[i] = {EMPTY_CARD, EMPTY_CARD};
        }
    }
    //Iterate through pair of suited cards given the two ranks
    else if(hand_group[2] == 's'){
        for(int i = 0; i < SUITED_SUITS.size(); i++) {
            cardset[i] = {Card{hand_group[0], SUITED_SUITS[i].first}, Card{hand_group[1], SUITED_SUITS[i].second}};
        }
        //fill the rest of the array with the empty hand type
        for(int i = SUITED_SUITS.size(); i < 12; i++) {
            cardset[i] = {EMPTY_CARD, EMPTY_CARD};
        }
    }

    //Finally iterate through all possible offsuit hands given the ranks. We dont need to fill in the rest of the array
    else{
        for(int i = 0; i < OFFSUIT_SUITS.size(); i++) {
            cardset[i] = {Card{hand_group[0], OFFSUIT_SUITS[i].first}, Card{hand_group[1], OFFSUIT_SUITS[i].second}};
        }
    }

    return cardset;
}


constexpr std::array<std::array<Hand, 12>, 169> make_cardsets_for_handgroups(){
    std::array<std::array<Hand, 12>, 169> cardset_for_each_handgroup;

    for(int i = 0; i < HAND_GROUPS.size(); i++){
        cardset_for_each_handgroup[handgroup_to_int(HAND_GROUPS[i])] = process_handgroup(HAND_GROUPS[i]);
        }
    return cardset_for_each_handgroup;
}

constexpr std::array<std::array<Hand, 12>, 169> HANDGROUPS_TO_CARDSETS = make_cardsets_for_handgroups();
/*
int main(){

    for (auto card_set : HANDGROUPS_TO_CARDSETS) {
        for(int i = 0; i < card_set.size(); i++){
            std::cout << card_set[i][0].rank << card_set[i][0].suit << card_set[i][1].rank << card_set[i][1].suit << " ";
        }
        std::cout << "\n";
    }

    /*
    std::array<int, 169> my_array = {0};
    for (int i = 0; i<HAND_GROUPS.size(); i++){

        my_array[handgroup_to_int(HAND_GROUPS[i])] +=1;
        if(handgroup_to_int(HAND_GROUPS[i]) == 15){
            std::cout << HAND_GROUPS[i]<< " ";
        }
    }
    for (int i = 0; i<HAND_GROUPS.size(); i++){
        if (my_array[i] > 1){
            printf(" %d: ABOVE 1\n", i);
        }
        if (my_array[i] < 1){
            printf(" %d: BELOW 1\n", i);
        }

    }

    return 0;
}  */