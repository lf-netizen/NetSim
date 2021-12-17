//
// Created by adamf on 14.12.2021.
//

// definicje funkcjonalności storage_types.hpp
#include <iostream>
#include <list>
#include "storage_types.hpp"
#include "package.hpp"
#include "stdexcept"

Package PackageQueue::pop() {

    switch (queue_type_) {
        case PackageQueueType::FIFO : {
            Package popped = package_queue_.front();
            package_queue_.pop_front(); // odpowiedni element kolejki
            return popped;
        }
        case PackageQueueType::LIFO : {
            Package popped = package_queue_.back();
            package_queue_.pop_back(); // odpowiedni element kolejk
            return popped;
        }
        default:
            throw std::invalid_argument("POP_ERROR");
    }
}
//
//void PackageQueue::push(Package&&) {
//
//}

