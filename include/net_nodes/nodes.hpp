//
// Created by adamf on 01.12.2021.
//

//  typ wyliczeniowy ReceiverType
//  klasy IPackageReceiver, Storehouse, ReceiverPreferences, PackageSender, Ramp, Worker

#include "package.hpp"
#include "storage_types.hpp"
#include <memory>
#include <utility>
#include "map"
#include "helpers.hpp"

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

class IPackageReceiver {
public:
    virtual void receive_package (Package&& p) = 0;
    virtual ElementID get_id() const = 0;

    using const_iterator = IPackageStockpile::const_iterator;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const= 0;

    virtual ~IPackageReceiver() = default;
};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> p) : id_(id) { stockpile_ = std::move(p); }

    ElementID get_id() const override { return id_; }
    void receive_package(Package&& p) override {stockpile_->push(std::move(p)); }

    const_iterator cbegin() const override {return stockpile_ -> cbegin(); }
    const_iterator cend() const override {return stockpile_ -> cend(); }
    const_iterator begin() const override {return stockpile_ -> begin(); }
    const_iterator end() const override {return stockpile_ -> end(); }

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> stockpile_;
};


class  ReceiverPreferences {
public:

    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = default_probability_generator) : pg(std::move(pg)) {}

    ProbabilityGenerator pg;
    preferences_t preferences;

    const_iterator cbegin() const {return preferences.cbegin(); }
    const_iterator cend() const {return preferences.cend(); }
    const_iterator begin() const {return preferences.begin(); }
    const_iterator end() const {return preferences.end(); }

    void add_receiver (IPackageReceiver* r);
    void remove_receiver (IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const { return preferences; }

private:
    void rescale_probabilities();

};





#endif //NETSIM_NODES_HPP
