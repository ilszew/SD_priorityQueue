#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "arrayList.h"
#include <stdexcept>
#include <algorithm>

template <typename T>
class PriorityQueue {
private:
    struct Entry {
        T element;
        int priority;

        bool operator==(const Entry& other) const {
            return element == other.element;
        }
    };

    ArrayList<Entry> data;

public:
    PriorityQueue() = default;

    void insert(const T& element, int priority) {
        Entry newEntry{ element, priority };
        data.DodajK(newEntry);
    }

    T extract_max() {
        if (data.wielkosc() == 0)
            throw std::out_of_range("Pusta");

        int maxIndex = 0;
        for (int i = 1; i < data.wielkosc(); ++i) {
            if (data.dane[i].priority > data.dane[maxIndex].priority) {
                maxIndex = i;
            }
        }

        T result = data.dane[maxIndex].element;
        data.UsunLos(maxIndex);
        return result;
    }

    T peek() const {
        if (data.wielkosc() == 0)
            throw std::out_of_range("Pusta");

        int maxIndex = 0;
        for (int i = 1; i < data.wielkosc(); ++i) {
            if (data.dane[i].priority > data.dane[maxIndex].priority) {
                maxIndex = i;
            }
        }

        return data.dane[maxIndex].element;
    }

    void modify_key(const T& element, int new_priority) {
        for (int i = 0; i < data.wielkosc(); ++i) {
            if (data.dane[i].element == element) {
                data.dane[i].priority = new_priority;
                return;
            }
        }
        throw std::invalid_argument("Nie znaleziono elementu");
    }

    [[nodiscard]] size_t return_size() const {
        return data.wielkosc();
    }

    [[nodiscard]] bool empty() const {
        return data.wielkosc() == 0;
    }
};

#endif // PRIORITYQUEUE_H
