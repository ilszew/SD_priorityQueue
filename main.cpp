#include <vector>
#include <string>
#include "priorityQueue.h"
#include "priorityQueueHeap.h"
#include "priorityQueuePerformanceTester.h"

int main() {
    std::vector<int> test_sizes = {1000, 5000, 10000, 50000, 100000};

    int num_tests = 30;


    run_performance_tests<PriorityQueue<int>>("Array Priority Queue", test_sizes, num_tests);

    run_performance_tests<PriorityQueueHeap<int>>("Heap Priority Queue", test_sizes, num_tests);

    return 0;
}