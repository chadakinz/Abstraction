#include <array>
#include <unordered_map>
#include "c_card.h"
#include <string>
#include "types.h"
#include "constants.h"
#include <stdexcept>


constexpr static int NUM_HAND_GROUPS = 8;

constexpr std::array<int, 8> NUM_ELEMENTS_EACH_HANDGROUP = {26, 21, 23, 24, 19, 26, 23, 7};



constexpr std::array<std::array<std::string_view, 26>, 8> OCHS_HAND_GROUPS = {{
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

constexpr std::array<std::string_view, 169> HAND_GROUPS = {
        // Group 1
        "32s","42s","52s","62s","72s","43s","53s","63s","73s","54s","64s",
        "32o","42o","52o","62o","72o","82o","43o","53o","63o","73o","83o",
        "54o","64o","74o","65o",

        // Group 2
        "82s","92s","T2s","83s","93s","74s","84s","94s",
        "92o","T2o","J2o","93o","T3o","J3o","84o","94o","T4o",
        "75o","85o","95o","T5o",

        // Group 3
        "T3s","T4s","65s","75s","85s","95s","T5s","76s","86s","96s","T6s",
        "87s","97s","98s",
        "76o","86o","96o","T6o","87o","97o","T7o","98o","T8o",

        // Group 4
        "22","J2s","Q2s","K2s","J3s","Q3s","J4s","Q4s","J5s","Q5s","J6s",
        "Q2o","K2o","Q3o","K3o","J4o","Q4o","K4o","J5o","Q5o",
        "J6o","Q6o","J7o","Q7o",

        // Group 5
        "Q6s","T7s","J7s","Q7s","T8s","J8s","Q8s","T9s","J9s","Q9s","JTs",
        "J8o","Q8o","T9o","J9o","Q9o","JTo","QTo","QJo",

        // Group 6
        "33","44","55",
        "A2s","K3s","A3s","K4s","A4s","K5s","A5s","K6s","A6s","K7s","K8s",
        "A2o","A3o","A4o","K5o","A5o","K6o","A6o","K7o","A7o",
        "K8o","A8o","K9o",

        // Group 7
        "66","77",
        "A7s","A8s","K9s","A9s","QTs","KTs","ATs","QJs","KJs","AJs",
        "KQs","AQs","AKs",
        "A9o","KTo","ATo","KJo","AJo","KQo","AQo","AKo",

        // Group 8
        "88","99","TT","JJ","QQ","KK","AA"
};

constexpr int handgroup_to_int(const std::string_view& handgroup){

    char rank1 = handgroup[0];
    char rank2 = handgroup[1];

    int rank1_id = 14;
    int rank2_id = 14;

    for (int i = 0; i < NUM_RANKS; i++){
        if(rank1 == ranks[i]) rank1_id = i;
        if(rank2 == ranks[i])  rank2_id = i;
    }
    if(rank1_id < rank2_id) std::swap(rank1_id, rank2_id);

    if(rank1 == rank2) return rank1_id;
    else if(handgroup[2] == 'o'){
        return 13 + (((rank1_id) * (rank1_id - 1))/2) + rank2_id;
    }
    else return 91 + ((rank1_id * (rank1_id- 1))/2) + rank2_id;
}

constexpr std::array<std::string_view, 169> init_handgroup_to_number(){
    std::array<std::string_view, 169> init_array;
    for(int i = 0; i < HAND_GROUPS.size(); i++) init_array[handgroup_to_int(HAND_GROUPS[i])] = HAND_GROUPS[i];
    return init_array;
}

constexpr std::array<std::string_view, 169> hand_group_to_number = init_handgroup_to_number();

extern const std::array<std::array<Hand, 12>, 169> HANDGROUPS_TO_CARDSETS;


