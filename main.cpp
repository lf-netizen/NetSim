//#include <iostream>
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "factory.hpp"
#include "nodes.hpp"
#include "config.hpp"
#include "helpers.hpp"

#include <iostream>
#include <set>
#include <stdexcept>

int main() {


    Factory factory;
    factory.add_ramp(Ramp(1, 1));
    factory.add_worker(Worker(1, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_worker(Worker(2, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_worker(Worker(3, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));

    Ramp& r = *(factory.find_ramp_by_id(1));

    r.receiver_preferences_.add_receiver(&(*(factory.find_worker_by_id(1))));
    r.receiver_preferences_.add_receiver(&(*(factory.find_worker_by_id(2))));
    r.receiver_preferences_.add_receiver(&(*(factory.find_worker_by_id(3))));

//    ReceiverPreferences::preferences_t p;
//    p[&(*(factory.find_worker_by_id(1)))] = 1.0 / 3.0;
//    p[&(*(factory.find_worker_by_id(2)))] = 1.0 / 3.0;
//    p[&(*(factory.find_worker_by_id(3)))] = 1.0 / 3.0;
//    r.receiver_preferences_.set_preferences(p);

    factory.remove_worker(1);

    auto prefs = r.receiver_preferences_.get_preferences();

    auto it = prefs.find(&(*(factory.find_worker_by_id(2))));

    it = prefs.find(&(*(factory.find_worker_by_id(3))));

    return 0;
}