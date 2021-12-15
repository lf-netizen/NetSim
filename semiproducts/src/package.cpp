//
// Created by adamf on 01.12.2021.
//

// definicje funkcjonalności package.hpp

#include "package.hpp"

std::set<ElementID> Package::freed_IDs_ = {};
std::set<ElementID> Package::assigned_IDs_ = {0};

Package::Package() {
    if (freed_IDs_.empty())
        id_ = *assigned_IDs_.rbegin() + 1;
    else {
        id_ = *freed_IDs_.begin();
        freed_IDs_.erase(freed_IDs_.begin());
    }
    assigned_IDs_.insert(id_);
}

Package & Package::operator=(Package &&other) {
    id_ = other.id_;
    return *this;
}

Package::~Package() {
    assigned_IDs_.erase(id_);
    freed_IDs_.insert(id_);
}



