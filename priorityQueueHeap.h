#ifndef PRIORITYQUEUEHEAP_H
#define PRIORITYQUEUEHEAP_H

#include <iostream>
#include <vector>
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
class PriorityQueueHeap {
private:
    std::vector<PQElement<T>> heap;
    std::unordered_map<T, size_t> position_map;

    [[nodiscard]] size_t parent(size_t i) const { return (i - 1) / 2; }
    [[nodiscard]] size_t left_child(size_t i) const { return 2 * i + 1; }
    [[nodiscard]] size_t right_child(size_t i) const { return 2 * i + 2; }

    void sift_up(size_t index) {
        while (index > 0) {
            size_t p = parent(index);
            if (heap[index].priority <= heap[p].priority) {
                break;
            }
            std::swap(heap[index], heap[p]);
            position_map[heap[index].value] = index;
            position_map[heap[p].value] = p;
            index = p;
        }
    }

    void sift_down(size_t index) {
        size_t size = heap.size();
        while (true) {
            size_t left = left_child(index);
            size_t right = right_child(index);
            size_t largest = index;

            if (left < size && heap[left].priority > heap[largest].priority) {
                largest = left;
            }

            if (right < size && heap[right].priority > heap[largest].priority) {
                largest = right;
            }

            if (largest == index) {
                break;
            }

            std::swap(heap[index], heap[largest]);
            position_map[heap[index].value] = index;
            position_map[heap[largest].value] = largest;
            index = largest;
        }
    }

public:
    PriorityQueueHeap() = default;

    void insert(T element, int priority) {
        if (position_map.find(element) != position_map.end()) {
            throw std::invalid_argument("Element isnieje juz w kolejce");
        }

        heap.push_back(PQElement<T>(element, priority));
        size_t index = heap.size() - 1;
        position_map[element] = index;

        sift_up(index);
    }

    PQElement<T> extract_max() {
        if (heap.empty()) {
            throw std::out_of_range("Kolejka priorytetowa jest pusta");
        }

        PQElement<T> max_element = heap[0];

        heap[0] = heap.back();
        position_map[heap[0].value] = 0;
        heap.pop_back();

        position_map.erase(max_element.value);

        if (!heap.empty()) {
            sift_down(0);
        }

        return max_element;
    }

    PQElement<T> find_max() const {
        if (heap.empty()) {
            throw std::out_of_range("Kolejka priorytetowa jest pusta");
        }
        return heap[0];
    }

    void modify_priority(T element, int new_priority) {
        auto it = position_map.find(element);
        if (it == position_map.end()) {
            throw std::invalid_argument("Nie znaleziono elementu");
        }

        size_t index = it->second;
        int old_priority = heap[index].priority;
        heap[index].priority = new_priority;

        if (new_priority > old_priority) {
            sift_up(index);
        } else if (new_priority < old_priority) {
            sift_down(index);
        }
    }

    [[nodiscard]] size_t size() const {
        return heap.size();
    }

    [[nodiscard]] bool empty() const {
        return heap.empty();
    }

    void print() const {
        std::cout << "Zawartosc kolejki: ";
        for (const auto& elem : heap) {
            std::cout << "(" << elem.value << "," << elem.priority << ") ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    PQElement<T> peek() const {
        return find_max();
    }

    void modify_key(T element, int new_priority) {
        modify_priority(element, new_priority);
    }
};

#endif //PRIORITYQUEUEHEAP_H