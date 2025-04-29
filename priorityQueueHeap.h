#ifndef PRIORITYQUEUEHEAP_H
#define PRIORITYQUEUEHEAP_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>

template <typename T>
struct PQElement {
    T value;
    int priority;

    PQElement(T val, int prio) : value(val), priority(prio) {}

    bool operator==(const PQElement<T>& other) const {
        return value == other.value;
    }
};

template <typename T>
class SortedArrayPriorityQueue {
private:
    std::vector<PQElement<T>> elements;
    std::unordered_map<T, size_t> position_map;

    static bool compare_priority(const PQElement<T>& a, const PQElement<T>& b) {
        return a.priority > b.priority;
    }

    void update_position_map() {
        for (size_t i = 0; i < elements.size(); i++) {
            position_map[elements[i].value] = i;
        }
    }

public:
    SortedArrayPriorityQueue() = default;

    void insert(T element, int priority) {
        if (position_map.find(element) != position_map.end()) {
            throw std::invalid_argument("Element isnieje juz w kolejce");
        }

        elements.push_back(PQElement<T>(element, priority));

        std::sort(elements.begin(), elements.end(), compare_priority);

        update_position_map();
    }

    PQElement<T> extract_max() {
        if (elements.empty()) {
            throw std::out_of_range("Kolejka priorytetowa jest pusta");
        }

        PQElement<T> max_element = elements.front();

        elements.erase(elements.begin());
        position_map.erase(max_element.value);

        update_position_map();

        return max_element;
    }

    PQElement<T> find_max() const {
        if (elements.empty()) {
            throw std::out_of_range("Kolejka priorytetowa jest pusta");
        }

        return elements.front();
    }

    void modify_priority(T element, int new_priority) {
        // Find element's position
        auto it = position_map.find(element);
        if (it == position_map.end()) {
            throw std::invalid_argument("Nie znaleziono elementu");
        }

        size_t index = it->second;
        elements[index].priority = new_priority;

        // Sort to maintain priority order
        std::sort(elements.begin(), elements.end(), compare_priority);

        // Update positions
        update_position_map();
    }

    [[nodiscard]] size_t size() const {
        return elements.size();
    }

    [[nodiscard]] bool empty() const {
        return elements.empty();
    }

    void print() const {
        std::cout << "Queue contents: ";
        for (const auto& elem : elements) {
            std::cout << "(" << elem.value << "," << elem.priority << ") ";
        }
        std::cout << std::endl;
    }
};

#endif //PRIORITYQUEUEHEAP_H
