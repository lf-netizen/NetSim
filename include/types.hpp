//
// Created by adamf on 01.12.2021.
//
#include "functional"
#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP

// definicja ElementID

using ElementID = std::size_t;

using ProbabilityGenerator = std::function<double()>;

using Time = std::size_t;
using TimeOffset = std::size_t;

#endif //NETSIM_TYPES_HPP
