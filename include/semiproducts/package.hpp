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
    Package(ElementID id);
    Package(Package&& other) : id_(other.id_) { copied_ = true; }
    //Package(Package& other) : id_(other.get_id()) { std::cout << "Package&" << std::endl; }


    Package& operator = (Package&& other);


    ElementID get_id() const { return id_; }

    ~Package();

private:
    ElementID id_;
    static std::set<ElementID> assigned_IDs_;
    static std::set<ElementID> freed_IDs_;
    static bool copied_;
};



#endif //NETSIM_PACKAGE_HPP
