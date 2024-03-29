//
// Created by adamf on 01.12.2021.
//

// definicje funkcjonalności package.hpp

#include "package.hpp"
#include <stdexcept>

std::set<ElementID> Package::freed_IDs_ = {};
std::set<ElementID> Package::assigned_IDs_ = {0};
bool Package::copied_ = false;

Package::Package() {
    if (freed_IDs_.empty())
        id_ = *assigned_IDs_.rbegin() + 1;
    else {
        id_ = *freed_IDs_.begin();
        freed_IDs_.erase(freed_IDs_.begin());
    }
    assigned_IDs_.insert(id_);
}

Package &Package::operator=(Package &&other) {
    assigned_IDs_.erase(id_);
    freed_IDs_.insert(id_);
    copied_ = true;
    id_ = other.id_;
    return *this;
}

Package::~Package() {
    if (not copied_) {
        assigned_IDs_.erase(id_);
        freed_IDs_.insert(id_);
    }
    else {
        copied_ = false;
    }
//        assigned_IDs_.erase(id_);
//        freed_IDs_.insert(id_);
}

Package::Package(ElementID id) {
    if (assigned_IDs_.find(id) != assigned_IDs_.end()) {
        throw std::invalid_argument("This ID is assigned");
    }
    id_ =id;
    assigned_IDs_.insert(id);
}



