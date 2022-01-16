//
// Created by ewafa on 17.12.2021.
//
// funkcja simulate()
#ifndef NETSIM_SIMULATION_HPP
#define NETSIM_SIMULATION_HPP

#include "factory.hpp"


void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf);

#endif //NETSIM_SIMULATION_HPP
