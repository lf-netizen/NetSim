//
// Created by Mateusz on 05.01.2022.
//
#include "reports.hpp"
#include "factory.hpp"
#include "nodes.hpp"
#include "storage_types.hpp"
//#include <utility>
#include <vector>
//#include <cstdlib>

//bool cmp(std::pair<IPackageReceiver*, double>& a,
//         std::pair<IPackageReceiver*, double>& b)
//{
//    return a.first->get_id() < b.first->get_id();
//}
//
//std::map<IPackageReceiver*, double> sort(const std::map<IPackageReceiver*, double>& M)
//{
//
//    // Declare vector of pairs
//    std::vector<std::pair<IPackageReceiver*, double>> A;
//
//    // Copy key-value pair from Map
//    // to vector of pairs
//    for (auto& it : M) {
//        A.emplace_back(it);
//    }
//
//    // Sort using comparator function
//    sort(A.begin(), A.end(), cmp);
//
//    std::map<IPackageReceiver*, double> m2;
//
//    for(auto& it: A) {
//        m2.insert(it);
//    }
//    return m2;
//}


void generate_structure_report(const Factory& factory, std::ostream& os){


    os << std::endl;
    os << "== LOADING RAMPS ==" << std::endl;

    for (auto ramp_it = factory.ramp_cbegin(); ramp_it != factory.ramp_cend(); ramp_it++){
        os << std::endl;
        os << "LOADING RAMP #" << ramp_it->get_id() << std::endl;
        os << "  Delivery interval: " << ramp_it->get_delivery_interval() << std::endl;
        os << "  Receivers:" << std::endl;


        std::set<ElementID> worker_ids;
        std::set<ElementID> storehouse_ids;


        for(auto receiver_preference : ramp_it->receiver_preferences_.get_preferences()) {
            if(receiver_preference.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
                storehouse_ids.insert(receiver_preference.first->get_id());
//                os << "    storehouse #" << receiver_preference.first->get_id() << std::endl;
            }
            if(receiver_preference.first->get_receiver_type() == ReceiverType::WORKER) {
                worker_ids.insert(receiver_preference.first->get_id());
//                os << "    worker #" << receiver_preference.first->get_id() << std::endl;
            }
        }

        for(auto id: storehouse_ids) {
            os << "    storehouse #" << id << std::endl;
        }
        for(auto id: worker_ids) {
            os << "    worker #" << id << std::endl;
        }

    }
    os << std::endl << std::endl;
    os << "== WORKERS ==" << std::endl;

    for (auto worker_it = factory.worker_begin(); worker_it != factory.worker_end(); worker_it++){
        os << std::endl << "WORKER #" << worker_it->get_id() << std::endl;
        os << "  Processing time: " << worker_it->get_processing_duration() << std::endl;
        os << "  Queue type: "; //<< //std::to_string(worker_it->get_worker_queue_type());
        if(worker_it->get_worker_queue_type() == PackageQueueType::FIFO){
            os << "FIFO" << std::endl;
        }
        else if(worker_it->get_worker_queue_type() == PackageQueueType::LIFO){
            os << "LIFO" << std::endl;
        }
        os << "  Receivers:" << std::endl;


        std::set<ElementID> worker_ids;
        std::set<ElementID> storehouse_ids;


        for(auto receiver_preference : worker_it->receiver_preferences_.get_preferences()) {
            if(receiver_preference.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
                storehouse_ids.insert(receiver_preference.first->get_id());
//                os << "    storehouse #" << receiver_preference.first->get_id() << std::endl;
            }
            if(receiver_preference.first->get_receiver_type() == ReceiverType::WORKER) {
                worker_ids.insert(receiver_preference.first->get_id());
//                os << "    worker #" << receiver_preference.first->get_id() << std::endl;
            }
        }

        for(auto id: storehouse_ids) {
            os << "    storehouse #" << id << std::endl;
        }
        for(auto id: worker_ids) {
            os << "    worker #" << id << std::endl;
        }


    }
    os << std::endl << std::endl;
    os << "== STOREHOUSES ==" << std::endl;
    for(auto storehouse_it = factory.storehouse_cbegin(); storehouse_it != factory.storehouse_cend(); storehouse_it++){
        os << std::endl << "STOREHOUSE #" << storehouse_it->get_id() << std::endl;
    }
    os << std::endl;
}

void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time t){
    os << "=== [ Turn: " << t << " ] ===" << std::endl << std::endl;
    os << "== WORKERS ==" << std::endl;
    for (auto worker_it = factory.worker_cbegin(); worker_it != factory.worker_cend(); worker_it++){
        os << std::endl << "WORKER #" << worker_it->get_id() << std::endl;
        os << "  PBuffer: ";
        if(worker_it->get_processing_buffer() != std::nullopt){
            os << "#" << worker_it->get_processing_buffer()->get_id() << " (pt = " << worker_it->get_package_processing_start_time() << ")" << std::endl;
        }
        else{
            os << "(empty)" << std::endl;
        }
        os << "  Queue: ";
        bool test = true;
        for(auto it = worker_it->cbegin(); it != worker_it->cend(); it++){
            test = false;
            os << "#" << it->get_id();
        }
        if(not test){
            os << std::endl;
        }
        if(test){
            os << "(empty)" << std::endl;
        }
        //os << "  SBuffer: " << worker_it->get_sending_buffer()->get_id();
        os << "  SBuffer: ";
        if(worker_it->get_sending_buffer() != std::nullopt){
            os << "#" << worker_it->get_sending_buffer()->get_id() << std::endl;
        }
        else{
            os << "(empty)" << std::endl;
        }
    }
    os << std::endl << std::endl;
    os << "== STOREHOUSES ==" << std::endl << std::endl;
    for (auto storehouse_it = factory.storehouse_cbegin(); storehouse_it != factory.storehouse_cend(); storehouse_it++){
        os << "STOREHOUSE #" << storehouse_it->get_id() << std::endl;
        os << "  Stock: ";
        if(storehouse_it->is_storehouse_empty()){
            os << "(empty)" << std::endl;
        }
        else{
            os << "#" << storehouse_it->cbegin()->get_id() << std::endl;
        }
        for(auto elem = storehouse_it->cbegin(); elem != storehouse_it->cend(); elem++){
            if(elem == storehouse_it->cbegin()){
                continue;
            }
            os << ", #" << elem->get_id() << std::endl;
        }
    }
    os << std::endl;
}

bool IntervalReportNotifier::should_generate_report(Time t) {
    return t % to_ == 1;
}

bool SpecificTurnsReportNotifier::should_generate_report(Time t) {
    return turns_.find(t) != turns_.end();
}



