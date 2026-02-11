#include "turn_abstraction_types.h"
#include "common_types.h"
#include "objects.hpp"
#include "helper_functions.hpp"
#include "get_equity_distribution.h"
#include <vector>
#include <fstream>   // std::ofstream
#include <iostream>  // std::cerr, std::cout
#include <iomanip>   // std::fixed, std::setprecision
#include <string>
#include "canonical_hands.hpp"
#include "canonical.h"
#include <chrono>
#include <thread>


constexpr static int NUM_THREADS = 8;
inline bool are_cards_seen(const std::array<int, 4>& cards, const std::array<int, 52>& seen_cards){
    if (seen_cards[cards[0]] == 1 || seen_cards[cards[1]] == 1 || seen_cards[cards[2]] == 1
    || seen_cards[cards[3]] == 1){
        return true;
    }else return false;
}
void save_equity_vector_to_csv(
        const std::vector<Equity_Distribution>& vec,
        const std::string& filename
) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    out << std::fixed << std::setprecision(6);

    // Write all elements
    for (size_t row = 0; row < vec.size(); ++row) {
        const auto& values = vec[row];
        for (size_t i = 0; i < values.size(); ++i) {
            out << values[i];
            if (i != values.size() - 1)
                out << ",";  // comma between columns
        }
        out << "\n";  // new line for next row
    }

    out.close();
}

int main() {

    printf("TEST\n");
    std::mutex print_mutex;
    // Global result container (merged after threads finish)
    std::vector<Equity_Distribution> global_eq_dist_list;
    global_eq_dist_list.reserve(HANDS_TOTAL * all_canon_4card.size());

    // Worker function
    auto worker = [&](int thread_id, int start_idx, int end_idx)
    {
        std::array<int, 52> seen_cards{};
        std::vector<Equity_Distribution> local_eq_dist_list;

        for (int h = start_idx; h < end_idx; ++h)
        {
            auto hand_start = std::chrono::high_resolution_clock::now();
            const Hand& hand = all_possible_hands[h];

            populate_seen_cards(hand, seen_cards);

            for (const std::array<int, 4>& public_cards : all_canon_4card)
            {
                if (are_cards_seen(public_cards, seen_cards))
                    continue;

                for (int i = 0; i < NUM_TURN_CARDS; i++)
                    seen_cards[public_cards[i]] = 1;

                local_eq_dist_list.push_back(
                        get_equity_distribution(public_cards, hand, seen_cards)
                );

                for (int i = 0; i < NUM_TURN_CARDS; i++)
                    seen_cards[public_cards[i]] = 0;
            }
            auto hand_end = std::chrono::high_resolution_clock::now();
            double hand_duration =
                    std::chrono::duration<double>(hand_end - hand_start).count();

            {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "Thread " << thread_id
                          << " | Hand index " << h
                          << " took " << hand_duration
                          << " seconds\n";
            }

            unpopulate_seen_cards(hand, seen_cards);
        }

        // Merge results once (outside hot loop)
        static std::mutex merge_mutex;
        std::lock_guard<std::mutex> lock(merge_mutex);
        global_eq_dist_list.insert(
                global_eq_dist_list.end(),
                local_eq_dist_list.begin(),
                local_eq_dist_list.end()
        );
    };

    std::vector<std::thread> threads;
    threads.reserve(NUM_THREADS);

    // Hand distribution:
    // First 6 threads → 166 hands
    // Last 2 threads → 165 hands

    int index = 0;
    for (int t = 0; t < NUM_THREADS; ++t)
    {
        int chunk_size = (t < 6) ? 166 : 165;
        int start = index;
        int end = index + chunk_size;
        index = end;

        threads.emplace_back(worker, t, start, end);
    }

    for (auto& t : threads)
        t.join();

    std::cout << "Length of eq_dist_list: "
              << global_eq_dist_list.size()
              << "\n";
    printf("Saving to file\n");
    save_equity_vector_to_csv(global_eq_dist_list, "equity_results.csv");

    return 0;
}