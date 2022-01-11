//
// Created by lucas on 17.12.2021.
//
//    klasy SpecificTurnsReportNotifier, IntervalReportNotifier
//    funkcje generate_structure_report(), generate_simulation_turn_report()

#ifndef NETSIM_REPORTS_HPP
#define NETSIM_REPORTS_HPP
#include<sstream>
#include "factory.hpp"

void generate_structure_report(const Factory& factory, std::ostream& oss);
void generate_simulation_turn_report(const Factory& factory, std::ostream& oss, Time t);


void gener_receivers(const Factory& factory, std::ostringstream& os);








#endif //NETSIM_REPORTS_HPP
