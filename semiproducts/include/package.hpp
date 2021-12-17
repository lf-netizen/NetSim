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
    Package();
    Package(ElementID id): id_(id);
    Package(Package&& other): id_(other.get_id()) {}

    Package& operator= (Package&& other);


    [[nodiscard]] ElementID get_id() const {return id_;}

    ~Package();

private:
    ElementID id_;
    static std::set<ElementID> assigned_IDs_;
    static std::set<ElementID> freed_IDs_;
};



#endif //NETSIM_PACKAGE_HPP
