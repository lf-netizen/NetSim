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
    using const_iterator = std::list<Package>::const_iterator;

    virtual void push(Package&& package) = 0;
    virtual bool empty() const = 0;

    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const= 0;

    virtual std::size_t size() const = 0;

    virtual ~IPackageStockpile() = default;
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
    PackageQueue(PackageQueueType p) : queue_type_(p) {}
    Package pop() override;
    PackageQueueType get_queue_type() override { return queue_type_; }

    void push(Package&& package) override { package_queue_.emplace_back(std::move(package)); }
    bool empty() const override { return package_queue_.empty(); }

    const_iterator cbegin() const override { return package_queue_.cbegin(); }
    const_iterator cend() const override{ return package_queue_.cend(); }
    const_iterator begin() const override { return package_queue_.cbegin(); }
    const_iterator end() const override { return package_queue_.cend(); }

    std::size_t size() const override { return package_queue_.size(); }
private:
    PackageQueueType queue_type_;
    std::list<Package> package_queue_;
};



#endif //NETSIM_STORAGE_TYPES_HPP