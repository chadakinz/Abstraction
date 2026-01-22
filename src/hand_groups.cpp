#include <hand_groups.hpp>
#include <string_view>
#include <utility>
//Methods for tabulating handgroups. A handgroup is a group of preflop hands. For example 43s is the group of preflop
//cards including 4h3h, 4c3c, 4s3s, 4d3d

constexpr static int NUM_HAND_GROUPS = 8;

constexpr std::array<std::array<std::string_view, 26>, 8> HAND_GROUPS = {{
        { "32s", "42s", "52s", "62s", "72s", "43s", "53s", "63s", "73s",
        "54s", "64s", "32o", "42o", "52o", "62o", "72o", "82o", "43o",
        "53o", "63o", "73o", "83o", "54o", "64o", "74o", "65o" },
        { "82s", "92s", "T2s", "83s", "93s", "74s", "84s", "94s",
        "92o", "T2o", "J2o", "93o", "T3o", "J3o", "84o", "94o",
        "T4o", "75o", "85o", "95o", "T5o", "", "", "", "", "" },

        { "T3s", "T4s", "65s", "75s", "85s", "95s", "T5s", "76s", "86s",
        "96s", "T6s", "87s", "97s", "98s", "76o", "86o", "96o",
        "T6o", "87o", "97o", "T7o", "98o", "T8o", "", "", "" },

        { "22", "J2s", "Q2s", "K2s", "J3s", "Q3s", "J4s", "Q4s", "J5s",
        "Q5s", "J6s", "Q2o", "K2o", "Q3o", "K3o", "J4o", "Q4o", "K4o",
        "J5o", "Q5o", "J6o", "Q6o", "J7o", "Q7o", "", "" },

        { "Q6s", "T7s", "J7s", "Q7s", "T8s", "J8s", "Q8s", "T9s", "J9s",
        "Q9s", "JTs", "J8o", "Q8o", "T9o", "J9o", "Q9o", "JTo",
        "QTo", "QJo", "", "", "", "", "", "", "" },

        { "33", "44", "55", "A2s", "K3s", "A3s", "K4s", "A4s", "K5s",
        "A5s", "K6s", "A6s", "K7s", "K8s", "A2o", "A3o", "A4o",
        "K5o", "A5o", "K6o", "A6o", "K7o", "A7o", "K8o", "A8o", "K9o" },

        { "66", "77", "A7s", "A8s", "K9s", "A9s", "QTs", "KTs", "ATs",
        "QJs", "KJs", "AJs", "KQs", "AQs", "AKs", "A9o", "KTo",
        "ATo", "KJo", "AJo", "KQo", "AQo", "AKo", "", "", "" },

        { "88", "99", "TT", "JJ", "QQ", "KK", "AA", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }
}};

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

constexpr std::array<Card, 12> process_handgroup(const std::string_view& hand_group){
    std::array<Card, 12> cardset;
    if(hand_group[0] == hand_group[1]){}
    return cardset;
}


constexpr std::array<std::array<Card, 12>, 169> make_cardsets_for_handgroups(){
    std::array<std::array<Card, 12>, 169> cardset_for_each_handgroup;

    int count = 0;
    for(int i = 0; i < NUM_HAND_GROUPS; i++){
        for(const auto& hand_group: HAND_GROUPS[i]){
            cardset_for_each_handgroup[count] = process_handgroup(hand_group);


            }
        }
    return cardset_for_each_handgroup;
}

constexpr std::array<std::array<Card, 12>, 169> HANDGROUPS_TO_CARDSETS = make_cardsets_for_handgroups();
