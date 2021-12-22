//
// Created by adamf on 01.12.2021.
//
//    szablon klasy NodeCollection
//    klasa Factory
//    funkcje do zapisu i odczytu struktury fabryki z pliku

#include "nodes.hpp"
#include "storage_types.hpp"
#include <algorithm>

#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP


template <class Node>
class NodeCollection {
public:
    using container_t = typename std::vector<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;


    void add(Node&& node);
    void remove_by_id(ElementID id);


    iterator find_by_id(ElementID id) { return std::find_if(v_.begin(), v_.end(), [&id](Node& node) { return id == node.get_id(); } ); }
    const_iterator find_by_id(ElementID id) const { return std::find_if(v_.cbegin(), v_.cend(), [&id](Node& node) { return id == node.get_id(); } ); }

    const_iterator cbegin() const { return v_.cbegin(); }
    const_iterator cend() const { return v_.cend(); }

    iterator begin() { return v_.begin(); }
    iterator end() { return v_.end(); }
    const_iterator begin() const { return v_.begin(); }
    const_iterator end() const { return v_.end(); }

private:
    container_t v_;
};


class Factory {
public:
    void add_ramp(Ramp&& ramp) { ramps_.add(std::move(ramp)); }
    void remove_ramp(ElementID id) { remove_receiver(ramps_, id); }
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return ramps_.find_by_id(id); }
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramps_.find_by_id(id); }
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const { return ramps_.cbegin(); }
    NodeCollection<Ramp>::const_iterator ramp_cend() const { return ramps_.cend(); }
    NodeCollection<Ramp>::iterator ramp_begin() { return ramps_.begin(); }
    NodeCollection<Ramp>::iterator ramp_end() { return ramps_.end(); }
    NodeCollection<Ramp>::const_iterator ramp_begin() const { return ramps_.begin(); }
    NodeCollection<Ramp>::const_iterator ramp_end() const { return ramps_.end(); }

    void add_worker(Worker&& worker) { workers_.add(std::move(worker)); }
    void remove_worker(ElementID id) { remove_receiver(workers_, id); }
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return workers_.find_by_id(id); }
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return workers_.find_by_id(id); }
    NodeCollection<Worker>::const_iterator worker_cbegin() const { return workers_.cbegin(); }
    NodeCollection<Worker>::const_iterator worker_cend() const { return workers_.cend(); }
    NodeCollection<Worker>::iterator worker_begin() { return workers_.begin(); }
    NodeCollection<Worker>::iterator worker_end() { return workers_.end(); }
    NodeCollection<Worker>::const_iterator worker_begin() const { return workers_.begin(); }
    NodeCollection<Worker>::const_iterator worker_end() const { return workers_.end(); }

    void add_storehouse(Storehouse&& storehouse) { storehouses_.add(std::move(storehouse)); }
    void remove_storehouse(ElementID id) { remove_receiver(storehouses_, id); }
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouses_.find_by_id(id); }
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouses_.find_by_id(id); }
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const { return storehouses_.cbegin(); }
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const { return storehouses_.cend(); }
    NodeCollection<Storehouse>::iterator storehouse_begin() { return storehouses_.begin(); }
    NodeCollection<Storehouse>::iterator storehouse_end() { return storehouses_.end(); }
    NodeCollection<Storehouse>::const_iterator storehouse_begin() const { return storehouses_.begin(); }
    NodeCollection<Storehouse>::const_iterator storehouse_end() const { return storehouses_.end(); }


    bool is_consistent() const;
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);

private:
    template <typename Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id);

    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> storehouses_;
};


#endif //NETSIM_FACTORY_HPP
