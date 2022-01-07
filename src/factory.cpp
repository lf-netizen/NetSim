//
// Created by adamf on 01.12.2021.
//

#include "factory.hpp"
#include "nodes.hpp"
#include <map>
#include "stdexcept"


enum class NodeColor {
    UNVISITED,
    VISITED,
    VERIFIED
};
//
//template <typename Node>
//void Factory::remove_receiver(NodeCollection<Node>& collection, ElementID id) {
//
//    typename NodeCollection<Node>::iterator it = collection.find_by_id(id);
//
//
//    for(auto& ramp : ramps_) {
//        ramp.receiver_preferences_.remove_receiver(&(*it));
//    }
//    for(auto& worker : workers_) {
//        worker.receiver_preferences_.remove_receiver(&(*it));
//    }
//
//    collection.remove_by_id(id);
//}
//
//
//template <class Node>
//void NodeCollection<Node>::add(Node&& node) {
//    v_.template emplace_back(std::move(node));
//}
//
//
//template <class Node>
//void NodeCollection<Node>::remove_by_id(ElementID id) {
//    iterator node_to_remove = find_by_id(id);
//
//    if(node_to_remove != v_.end()) {
//        v_.erase(node_to_remove);
//    }
//}


bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors) {

    if(node_colors[sender] == NodeColor::VERIFIED) {
        return true;
    }

    node_colors[sender] = NodeColor::VISITED;

    if(sender->receiver_preferences_.get_preferences().empty()) {
        throw std::logic_error("SENDER HAS NO RECEIVERS");
    }

    bool sender_has_receiver = false;

    for(auto& receiver_with_preferences : sender->receiver_preferences_.get_preferences()) {
        IPackageReceiver* receiver = receiver_with_preferences.first;

        if(receiver->get_receiver_type() == ReceiverType::STOREHOUSE) {
            sender_has_receiver = true;
        }
        else if(receiver->get_receiver_type() == ReceiverType::WORKER) {
            IPackageReceiver* receiver_ptr = receiver;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);

            if(sendrecv_ptr == sender) {
                break;
            }
            sender_has_receiver = true;

            if(node_colors[sendrecv_ptr] == NodeColor::UNVISITED) {
                has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }

    node_colors[sender] = NodeColor::VERIFIED;

    if(sender_has_receiver) {
        return true;
    }
    else {
        throw std::logic_error("if_sender_has_receiver == false");
    }

}


bool Factory::is_consistent() const {
    // sprawdza spójność sieci

    // mapowanie PackageSender do NodeColor
    std::map<const PackageSender*, NodeColor> node_colors;


    for(auto& ramp : ramps_) {
        node_colors.insert(std::pair<const PackageSender*, NodeColor>(&ramp, NodeColor::UNVISITED));
    }

    for(auto& worker : workers_) {
        node_colors.insert(std::pair<const PackageSender*, NodeColor>(&worker, NodeColor::UNVISITED));
    }

    for(auto &ramp : ramps_) {
        try {
            has_reachable_storehouse(&ramp, node_colors);
        }
        catch (std::logic_error) {
            return false;
        }
    }

    return true;
}


void Factory::do_deliveries(Time t) {
    // dokonuje dostawy na rampy
    for(auto& ramp : ramps_) {
        ramp.deliver_goods(t);
    }
}


void Factory::do_package_passing() {
    // dokonuje przekazywanie półproduktów
    for(auto& ramp : ramps_) {
        ramp.send_package();
    }
    for(auto& worker : workers_) {
        worker.send_package();
    }
}


void Factory::do_work(Time t) {
    // dokonuje przetwarzanie półproduktów przez robotników
    for(auto& worker : workers_) {
        worker.do_work(t);
    }
}
