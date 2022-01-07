//
// Created by Mateusz on 05.01.2022.
//
#include "reports.hpp"
#include "factory.hpp"
#include "nodes.hpp"
#include "storage_types.hpp"
//void gener_net_structure_report(const Factory& factory, std::ostringstream& os){
//    os << "== LOADING RAMPS ==" << std::endl << std::endl;
//    for (auto ramp_it = factory.ramp_cbegin(); ramp_it != factory.ramp_cend(); ramp_it++){
//        os << "LOADING RAMP #" << ramp_it->get_id() << std::endl;
//        os << "  Delivery interval: " << ramp_it->get_delivery_interval() << std::endl;
//        os << "  Receivers: " << std::endl;
//        os << "  " << get_receiver_type() << " #" << ramp_it->get_id();
//    }
//    os << std::endl << std::endl;
//    os << "== WORKERS ==" << std::endl << std::endl;
//
//    for (auto worker_it = factory.worker_cbegin(); worker_it != factory.worker_cend(); worker_it++){
//        os << "WORKER #" << worker_it->get_id() << std::endl;
//        os << "  Processing time: " << worker_it->get_processing_duration() << std::endl;
//        os << "  Queue type: ";
//        if(worker_it->get_queue_type() == PackageQueueType::FIFO){
//            os << "FIFO" << std::endl;
//        }
//        else if(worker_it->get_queue_type() == PackageQueueType::LIFO){
//            os << "LIFO" << std::endl;
//        }
//        os << "  Receivers: " << std::endl;
//        os << "    " << get_receiver_type() << " #" << worker_it->get_id() << std::endl;
//    }
//    os << std::endl << std::endl;
//    os << "== STOREHOUSES ==" << std::endl << std::endl;
//    for(auto storehouse_it = factory.storehouse_cbegin(); storehouse_it != factory.storehouse_cend(); storehouse_it++){
//        os << "STOREHOUSE #" << storehouse_it->get_id() << std::endl;
//    }
//    os << std::endl;



//}

