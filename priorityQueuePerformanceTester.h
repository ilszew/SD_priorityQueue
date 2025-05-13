#ifndef PRIORITY_QUEUE_PERFORMANCE_TESTER_H
#define PRIORITY_QUEUE_PERFORMANCE_TESTER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>

#include "randomGenerator.h"
#include "timer.h"

struct PerformanceResults {
    double insert_time;
    double extract_max_time;
    double find_max_time;
    double modify_key_time;
    int size;
};

template <typename PQType>
class PriorityQueuePerformanceTester {
private:
    RandomGenerator rng;

public:
    explicit PriorityQueuePerformanceTester(unsigned int seed = 12345) : rng(0, INT_MAX, seed) {}

    PerformanceResults test_performance(int size) {
        PerformanceResults results{};
        results.size = size;
        Timer timer;

        std::vector<std::pair<int, int>> elements(size);
        for (int i = 0; i < size; ++i) {
            elements[i] = {i, rng.generatePriority(size)};
        }

        {
            PQType pq;
            timer.startTimer();
            for (const auto& elem : elements) {
                pq.insert(elem.first, elem.second);
            }
            results.insert_time = timer.stopTimer();
        }

        PQType pq;
        for (const auto& elem : elements) {
            pq.insert(elem.first, elem.second);
        }

        {
            PQType local_pq = pq;
            timer.startTimer();
            for (int i = 0; i < size; ++i) {
                if (!local_pq.empty()) {
                    if constexpr (std::is_same_v<PQType, PriorityQueueHeap<int>>) {
                        local_pq.extract_max();
                    } else {
                        local_pq.extract_max();
                    }
                }
            }
            results.extract_max_time = timer.stopTimer();
        }

        {
            timer.startTimer();
            for (int i = 0; i < size; ++i) {
                if (!pq.empty()) {
                    if constexpr (std::is_same_v<PQType, PriorityQueueHeap<int>>) {
                        volatile auto max_elem = pq.find_max();
                        (void)max_elem;
                    } else {
                        volatile auto max_elem = pq.peek();
                        (void)max_elem;
                    }
                }
            }
            results.find_max_time = timer.stopTimer();
        }

        {
            PQType local_pq = pq;
            timer.startTimer();
            for (int i = 0; i < size / 10; ++i) {
                int index = rng.getRandomIndex(size);
                int new_priority = rng.generatePriority(size);
                try {
                    if constexpr (std::is_same_v<PQType, PriorityQueueHeap<int>>) {
                        local_pq.modify_priority(index, new_priority);
                    } else {
                        local_pq.modify_key(index, new_priority);
                    }
                } catch (const std::exception& e) {
                }
            }
            results.modify_key_time = timer.stopTimer();
        }

        return results;
    }
};

template <typename PQType>
void run_performance_tests(const std::string& queue_name,
                           const std::vector<int>& test_sizes,
                           int num_tests) {
    std::cout << "\nTesty dla " << queue_name << "\n";

    std::vector<PerformanceResults> all_results;
    const auto& default_seeds = RandomGenerator::getDefaultSeeds();

    for (int size : test_sizes) {
        std::vector<PerformanceResults> size_results;

        for (int test = 0; test < num_tests; ++test) {
            unsigned int seed = default_seeds[test % default_seeds.size()];
            PriorityQueuePerformanceTester<PQType> tester(seed);
            size_results.push_back(tester.test_performance(size));
        }

        PerformanceResults avg_result{};
        avg_result.size = size;
        for (const auto& result : size_results) {
            avg_result.insert_time += result.insert_time;
            avg_result.extract_max_time += result.extract_max_time;
            avg_result.find_max_time += result.find_max_time;
            avg_result.modify_key_time += result.modify_key_time;
        }

        avg_result.insert_time /= num_tests;
        avg_result.extract_max_time /= num_tests;
        avg_result.find_max_time /= num_tests;
        avg_result.modify_key_time /= num_tests;

        all_results.push_back(avg_result);

        std::cout << "Size: " << std::setw(7) << size
                  << " | Insert: " << std::setw(10) << std::fixed << std::setprecision(2) << avg_result.insert_time * 1000
                  << " ns | Extract Max: " << std::setw(10) << avg_result.extract_max_time * 1000
                  << " ns | Find Max: " << std::setw(10) << avg_result.find_max_time * 1000
                  << " ns | Modify Key: " << std::setw(10) << avg_result.modify_key_time * 1000 << " ns\n";
    }
}

#endif