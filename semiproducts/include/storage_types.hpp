//
// Created by adamf on 01.12.2021.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include <list>
#include "package.hpp"

// definicja typu wyliczeniowego PackageQueueType
enum PackageQueueType {
    FIFO,
    LIFO
};

// definicja klasy IPackageStockpile
class IPackageStockpile {
public:
    // alias
    using const_iterator = std::list<Package>::const_iterator;

    void push(Package&& package) { package_queue_.push_back(package); }
    bool empty() const { return package_queue_.empty(); }

    const_iterator cbegin() const { return package_queue_.cbegin(); }
    const_iterator cend() const { return package_queue_.cend(); }
    [[nodiscard]] const_iterator begin() const { return package_queue_.cbegin(); }
    [[nodiscard]] const_iterator end() const { return package_queue_.cend(); }

    [[nodiscard]] std::size_t size() const { return package_queue_.size(); }
    virtual ~IPackageStockpile() = default;


protected:
    std::list<Package> package_queue_;
};

// definicja klasy IPackageQueue
class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;

};



// definicja klasy PackageQueue
class PackageQueue : public IPackageQueue {
public:
    explicit PackageQueue(PackageQueueType p) : queue_type_(p) {}
    Package pop() override;


private:
    PackageQueueType queue_type_;
};



#endif //NETSIM_STORAGE_TYPES_HPP
