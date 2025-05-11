#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class PriorityQueue {
private:
    struct Entry {
        T element;
        int priority;
    };

    std::vector<Entry> data;

public:
    PriorityQueue() = default;

    void insert(const T& element, int priority) {
        data.push_back({ element, priority });
    }

    T extract_max() {
        if (data.empty())
            throw std::out_of_range("Pusta");

        auto it = std::max_element(data.begin(), data.end(),
            [](const Entry& a, const Entry& b) {
                return a.priority < b.priority;
            });

        T result = it->element;
        data.erase(it);
        return result;
    }

    T peek() const {
        if (data.empty())
            throw std::out_of_range("Pusta");

        auto it = std::max_element(data.begin(), data.end(),
            [](const Entry& a, const Entry& b) {
                return a.priority < b.priority;
            });

        return it->element;
    }

    void modify_key(const T& element, int new_priority) {
        for (auto& entry : data) {
            if (entry.element == element) {
                entry.priority = new_priority;
                return;
            }
        }
        throw std::invalid_argument("Pusta");
    }

    size_t return_size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};

#endif //PRIORITYQUEUE_H
