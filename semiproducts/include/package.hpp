//
// Created by adamf on 01.12.2021.
//

#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <set>
#include "types.hpp"

// definicja klasy Package
class Package {
public:
    Package() {}
    Package(ElementID id): id_(id) {}
    Package(Package&& other) = default;
    Package& operator= (Package&& other);

    [[nodiscard]] ElementID get_id() const {return id_;}

private:
    ElementID id_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};



#endif //NETSIM_PACKAGE_HPP
