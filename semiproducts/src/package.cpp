//
// Created by adamf on 01.12.2021.
//

// definicje funkcjonalności package.hpp

#include "package.hpp"


Package & Package::operator=(Package &&other) {
    id_ = other.id_;
    return *this;
}

