//
// Created by Adam on 16.01.2022.
//

#include "simulation.hpp"
#include "reports.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf) {
    /*
    -> uruchamiamy symulację na Factory f
            -> dla każdej tury n < d:
    -> czy generować raport?
    -> koniec
    */

    for(TimeOffset i=1; i<d+1; i++) {
        // symulacja



        // czy generować raport?
        rf(f, i);




    }

}



