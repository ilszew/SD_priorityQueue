cmake_minimum_required(VERSION 3.30)
project(SD_kolejkaPriorytetowa)

set(CMAKE_CXX_STANDARD 20)

add_executable(SD_kolejkaPriorytetowa main.cpp
        priorityQueue.h
        priorityQueueHeap.h
        timer.h
        randomGenerator.h
        priorityQueuePerformanceTester.h "arrayList.h")
