//
// Created by adamf on 01.12.2021.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include <list>

// definicja klasy IPackageStockpile
class IPackageStockpile {
public:
    // alias
    using const_iterator = std::list<Package>::const_iterator;

    void push(Package&&);
    bool empty();

    typename std::vector<T>::const_iterator cbegin() const { return v_.cbegin(); }
    typename std::vector<T>::const_iterator cend() const { return v_.cend(); }
    typename std::vector<T>::iterator begin() { return v_.begin(); }
    typename std::vector<T>::const_iterator begin() const { return v_.cbegin(); }
    typename std::vector<T>::iterator end() { return v_.end(); }
    typename std::vector<T>::const_iterator end() const { return v_.cend(); }

    size_type size();
    /iteratory/;
    ~IPackageStockpile();


private:

};

// definicja klasy IPackageQueue
class IPackageQueue : public IPackageStockpile {
public:
    Package pop();
    PackageQueueType get_queue_type();

private:

};

// definicja klasy PackageQueue
class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType p = {}) : package_(p) {}
    Package pop();
    void push(Package&&);


private:
    std::list queue_;
};

// definicja typu wyliczeniowego PackageQueueType
enum PackageQueueType {

};

#endif //NETSIM_STORAGE_TYPES_HPP
