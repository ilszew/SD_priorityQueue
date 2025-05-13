#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>
#include <vector>

class RandomGenerator {
private:
    std::mt19937 rng;
    unsigned int current_seed;

    int priority_multiplier;

public:
    explicit RandomGenerator(int min = 0, int max = INT_MAX,
                             unsigned int seed = std::random_device()(),
                             int priority_mult = 5)
        : rng(seed),
          current_seed(seed),
          priority_multiplier(priority_mult) {}

    void setSeed(unsigned int seed) {
        current_seed = seed;
        rng.seed(seed);
    }

    unsigned int getCurrentSeed() const {
        return current_seed;
    }

    int generatePriority(int structure_size) {
        int min_priority = structure_size;
        int max_priority = structure_size * priority_multiplier;
        std::uniform_int_distribution<int> dist(min_priority, max_priority);
        return dist(rng);
    }

    int getRandomInt(int min = 0, int max = INT_MAX) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    int getRandomIndex(int size) {
        if (size <= 0) return 0;
        std::uniform_int_distribution<int> dist(0, size - 1);
        return dist(rng);
    }

    static const std::vector<unsigned int>& getDefaultSeeds() {
        static const std::vector<unsigned int> DEFAULT_SEEDS = {12345, 67890, 24680};
        return DEFAULT_SEEDS;
    }
};

#endif //RANDOMGENERATOR_H