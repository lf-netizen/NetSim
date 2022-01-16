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


class IntervalReportNotifier {
public:
    IntervalReportNotifier(TimeOffset to) : to_(to) {}

    bool should_generate_report(Time t);
private:
    TimeOffset to_;
};

class SpecificTurnsReportNotifier {
public:
    SpecificTurnsReportNotifier(std::set<Time> turns) : turns_(turns) {}

    bool should_generate_report(Time t);
private:
    std::set<Time> turns_;
};

//void gener_receivers(const Factory& factory, std::ostringstream& os);

//void sort(std::map<IPackageReceiver *, double> M);
//bool cmp(std::pair<IPackageReceiver *, double>& a,
//         std::pair<IPackageReceiver *, double>& b);






#endif //NETSIM_REPORTS_HPP
