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
#include <optional>

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP


// typ wyliczeniowy do IPackageReceiver
enum class ReceiverType {
    WORKER,
    STOREHOUSE
};

class IPackageReceiver {
public:
    virtual void receive_package (Package&& p) = 0;
    virtual ElementID get_id() const = 0;

    using const_iterator = IPackageStockpile::const_iterator;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const= 0;

    virtual ReceiverType get_receiver_type() const = 0;

    virtual ~IPackageReceiver() = default;
};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> p) : id_(id) { stockpile_ = std::move(p); }

    ElementID get_id() const override { return id_; }
    void receive_package(Package&& p) override {stockpile_->push(std::move(p)); }

    const_iterator cbegin() const override {return stockpile_->cbegin(); }
    const_iterator cend() const override {return stockpile_->cend(); }
    const_iterator begin() const override {return stockpile_->begin(); }
    const_iterator end() const override {return stockpile_->end(); }

    ReceiverType get_receiver_type() const override { return ReceiverType::STOREHOUSE; }

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> stockpile_;
};


class ReceiverPreferences {
public:

    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg(std::move(pg)) {}

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

class PackageSender {
public:

    PackageSender(): to_send_buffer_(std::nullopt) {}
    ReceiverPreferences receiver_preferences_ = ReceiverPreferences();

    PackageSender(PackageSender&& other) = default;

    void send_package();

    const std::optional<Package>& get_sending_buffer() const { return to_send_buffer_; }

protected:
    std::optional<Package> to_send_buffer_;
    void push_package(Package&& p) {to_send_buffer_ = std::move(p); }

};

class Ramp : public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di) : PackageSender(), id_(id), di_(di) {}

    ElementID get_id() const { return id_; }
    TimeOffset get_delivery_interval() const { return di_; }

    void deliver_goods(Time t);

private:
    ElementID id_;
    TimeOffset di_;
};

class Worker : public PackageSender, public IPackageReceiver {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : PackageSender(), id_(id), pd_(pd),
                                                                            queue_(std::move(q)), work_buffer_(std::nullopt) {}

    void do_work(Time t);

    TimeOffset get_processing_duration() const { return pd_; }
    Time get_package_processing_start_time() const { return pst_; }

    const_iterator cbegin() const override { return queue_->cbegin(); }
    const_iterator cend() const override { return queue_->cend(); }
    const_iterator begin() const override { return queue_->begin(); }
    const_iterator end() const override{ return queue_->end(); }

    ElementID get_id() const override { return id_; }
    void receive_package (Package&& p) override { queue_->push(std::move(p)); }

    ReceiverType get_receiver_type() const override { return ReceiverType::WORKER; }


private:
    ElementID id_;
    TimeOffset pd_;
    TimeOffset pst_ = 0;
    std::unique_ptr<IPackageQueue> queue_;
    std::optional<Package> work_buffer_;
};



#endif //NETSIM_NODES_HPP