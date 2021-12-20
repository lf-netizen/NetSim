//#include <iostream>
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

int main() {

    PackageQueue fifo_queue(PackageQueueType::FIFO);

    for(int i=0; i<5; i++) {
        fifo_queue.push(Package());
    }
    Package pp = fifo_queue.pop();

    return 0;
}