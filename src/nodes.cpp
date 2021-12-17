//
// Created by adamf on 01.12.2021.
//
#include "nodes.hpp"
#include "stdexcept"

void ReceiverPreferences::rescale_probabilities() {
    for(auto& [key, val]: preferences) {
        val = 1.0 / double(preferences.size());
    }
}

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    preferences[r] = 0;
    rescale_probabilities();
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    double random_number = pg();
    double sum = 0;
    for (auto& [key, val]: preferences) {
        sum += val;
        if (random_number <= sum)
            return key;
    }
    throw std::invalid_argument("ReceiverPreferences: choose_receiver error");
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    preferences.erase(r);
    rescale_probabilities();
}


void PackageSender::send_package() {
    if (buffer_) {
        receiver_preferences_.choose_receiver() ->receive_package(std::move(buffer_.value()));
        buffer_ = std::nullopt;
    }
}

void Ramp::deliver_goods(Time t) {
    if((t - 1) % di_ == 0) {
        buffer_ = Package();
    }
}

void Worker::do_work(Time t) {
    if (t - pst_ == pd_) {
        send_package();
    }
    if (buffer_ == std::nullopt) {
        pst_ = t;
        push_package(queue_->pop());
    }

}
