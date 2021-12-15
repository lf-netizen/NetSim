//
// Created by adamf on 14.12.2021.
//

// definicje funkcjonalności storage_types.hpp
#include <iostream>
#include <list>
#include "storage_types.hpp"
#include "package.hpp"

Package PackageQueue::pop() {
    switch (PackageQueueType) {
        case PackageQueueType.FIFO:
            return queue_.pop_first(); // odpowiedni element kolejki
        case PackageQueueType.LIFO:
            return queue_.pop_back(); // odpowiedni element kolejki
        default:
            ; // RaiseError
    }
    return //RaiseError
}

void PackageQueue::push(Package&&) {

}