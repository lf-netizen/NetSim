//
// Created by Mateusz on 05.01.2022.
//
#include "reports.hpp"
#include "factory.hpp"
#include "nodes.hpp"
#include "storage_types.hpp"

void generate_structure_report(const Factory& factory, std::ostream& os){
    os << "== LOADING RAMPS ==" << std::endl << std::endl;
    for (auto ramp_it = factory.ramp_cbegin(); ramp_it != factory.ramp_cend(); ramp_it++){
        os << "LOADING RAMP #" << ramp_it->get_id() << std::endl;
        os << "  Delivery interval: " << ramp_it->get_delivery_interval() << std::endl;
        os << "  Receivers: " << std::endl;
        for(auto it = ramp_it->receiver_preferences_.cbegin(); it != ramp_it->receiver_preferences_.cend(); it++) {
            os << " " << it->first << " " << it->second << " " << ramp_it->get_id() << std::endl;
        }
    }
    os << std::endl << std::endl;
    os << "== WORKERS ==" << std::endl << std::endl;

    for (auto worker_it = factory.worker_cbegin(); worker_it != factory.worker_cend(); worker_it++){
        os << "WORKER #" << worker_it->get_id() << std::endl;
        os << "  Processing time: " << worker_it->get_processing_duration() << std::endl;
        os << "  Queue type: " << std::to_string(worker_it->get_worker_queue_type());
//        if(worker_it->get_worker_queue_type() == PackageQueueType::FIFO){
//            os << "FIFO" << std::endl;
//        }
//        else if(worker_it->get_worker_queue_type() == PackageQueueType::LIFO){
//            os << "LIFO" << std::endl;
//        }
        os << "  Receivers: " << std::endl;
        for(auto it = worker_it->receiver_preferences_.cbegin(); it != worker_it->receiver_preferences_.cend(); it++) {
            os << " " << it->first << " " << it->second << " " << worker_it->get_id() << std::endl;
        }
    }
    os << std::endl << std::endl;
    os << "== STOREHOUSES ==" << std::endl << std::endl;
    for(auto storehouse_it = factory.storehouse_cbegin(); storehouse_it != factory.storehouse_cend(); storehouse_it++){
        os << "STOREHOUSE #" << storehouse_it->get_id() << std::endl;
    }
    os << std::endl;
}

void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time t){
    os << "=== [ Turn: " << t << " ] ===" << std::endl << std::endl;
    os << "== WORKERS ==" << std::endl;
    for (auto worker_it = factory.worker_cbegin(); worker_it != factory.worker_cend(); worker_it++){
        os << "WORKER #" << worker_it->get_id() << std::endl;
        os << "  PBuffer: #";
        if(worker_it->get_processing_buffer() != std::nullopt){
            os <<worker_it->get_processing_buffer()->get_id() << " (pt = " << worker_it->get_processing_duration();
        }
        os << "Queue: ";
        for(auto it = worker_it->cbegin(); it != worker_it->cend(); it++){
            os << "#" << it->get_id() << ",";
        }
        os << std::endl;
        os << "SBuffer: #" << worker_it->get_sending_buffer()->get_id();
    }
}

