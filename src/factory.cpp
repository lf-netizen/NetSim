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
        catch (std::logic_error const&) {
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

std::map<std::string, ElementType> str_to_el_type = {
        {"LOADING_RAMP", ElementType::LOADING_RAMP},
        {"WORKER", ElementType::WORKER},
        {"STOREHOUSE", ElementType::STOREHOUSE},
        {"LINK", ElementType::LINK}
};

std::map<std::string, PackageQueueType> str_to_pq_type = {
        {"FIFO", PackageQueueType::FIFO},
        {"LIFO", PackageQueueType::LIFO}
};

std::pair<std::string, std::string> make_pair(std::string& s, char delimiter) {
    std::size_t delimiter_pos = s.find(delimiter);
    std::string first = s.substr(0, delimiter_pos);
    s.erase(0, delimiter_pos+1);
    return std::make_pair(first, s);
}

ParsedLineData parse_line(std::string line) {

    ParsedLineData line_data;
    std::list<std::string> kv_tokens;
    std::string token;
    std::string id_str;

    std::istringstream token_stream(line);
    char delimiter = ' ';

    std::getline(token_stream, id_str, delimiter);
    line_data.element_type = str_to_el_type[id_str];

    while (std::getline(token_stream, token, delimiter)) {
        kv_tokens.push_back(token);
    }



    for(auto& kv_token: kv_tokens) {
        line_data.parameters.insert(make_pair(kv_token, '='));
    }
    return line_data;
}
PackageSender* str_to_src(std::pair<std::string, std::string> src, Factory& factory) {
    if (src.first == "ramp") {
        return &(*factory.find_ramp_by_id(std::stoi(src.second)));
    }
    else if (src.first == "worker") {
        return &(*factory.find_worker_by_id(std::stoi(src.second)));
    }
    else {
        throw std::logic_error("unknown link source");
    }
}
IPackageReceiver* str_to_dest(std::pair<std::string, std::string> dest, Factory& factory) {
    if (dest.first == "store") {
        return &(*factory.find_storehouse_by_id(std::stoi(dest.second)));
    }
    else if (dest.first == "worker") {
        return &(*factory.find_worker_by_id(std::stoi(dest.second)));
    }
    else {
        throw std::logic_error("unknown link dest");
    }
}


Factory load_factory_structure(std::istream& is) {
    Factory factory;
    std::string line;
    while (std::getline(is, line)) {
        if(line.empty() or line[0] == ';') {
            continue;
        }
        ParsedLineData data = parse_line(line);
        switch(data.element_type) {
            case ElementType::LOADING_RAMP:
                factory.add_ramp(Ramp(std::stoi(data.parameters["id"]), std::stoi(data.parameters["delivery-interval"])));
                break;
            case ElementType::WORKER:
                factory.add_worker(Worker(std::stoi(data.parameters["id"]), std::stoi(data.parameters["processing-time"]), std::make_unique<PackageQueue>(str_to_pq_type[data.parameters["queue-type"]])));
                break;
            case ElementType::STOREHOUSE:
                factory.add_storehouse(std::stoi(data.parameters["id"]));
                break;
            case ElementType::LINK:
                std::pair<std::string, std::string> src = make_pair(data.parameters["src"], '-');
                std::pair<std::string, std::string> dest = make_pair(data.parameters["dest"], '-');
                str_to_src(src, factory)->receiver_preferences_.add_receiver(str_to_dest(dest, factory));
        }
    }
    return factory;
}


void save_factory_structure(Factory& factory, std::ostream& os) {
    for (auto ramp_it = factory.ramp_cbegin(); ramp_it != factory.ramp_cend(); ramp_it++) {
        os << "LOADING_RAMP id=" << ramp_it->get_id() << " delivery-interval=" << ramp_it->get_delivery_interval() << std::endl;
    }

    for (auto worker_it = factory.worker_begin(); worker_it != factory.worker_end(); worker_it++) {
        os << "WORKER id=" << worker_it->get_id() << " processing-time=" << worker_it->get_processing_duration() << " queue-type=";
        if(worker_it->get_worker_queue_type() == PackageQueueType::FIFO){
            os << "FIFO" << std::endl;
        }
        if(worker_it->get_worker_queue_type() == PackageQueueType::LIFO){
            os << "LIFO" << std::endl;
        }
    }
    for (auto store_it = factory.storehouse_begin(); store_it != factory.storehouse_end(); store_it++) {
        os << "STOREHOUSE id=" << store_it->get_id() << std::endl;
    }
    for (auto ramp_it = factory.ramp_cbegin(); ramp_it != factory.ramp_cend(); ramp_it++) {
        for (auto it: ramp_it->receiver_preferences_) {
            os << "LINK src=ramp-" << ramp_it->get_id() << " dest=worker-" << it.first->get_id() << std::endl;
        }
    }
    for (auto worker_it = factory.worker_cbegin(); worker_it != factory.worker_cend(); worker_it++) {
        for (auto it: worker_it->receiver_preferences_) {
            os << "LINK src=worker-" << worker_it->get_id();
            if(it.first->get_receiver_type() == ReceiverType::WORKER) {
                os << " dest=worker-" << it.first->get_id() << std::endl;
            }
            if(it.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
                os << " dest=store-" << it.first->get_id() << std::endl;
            }
        }
    }


    /// TO IMPLEMENT
}