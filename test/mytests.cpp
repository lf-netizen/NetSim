//
// Created by lukas on 14.12.2021.
//

#include "gtest/gtest.h"

#include "package.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"
#include "types.hpp"

TEST(PackageTest, IDfromAssigned) {
    Package p1 = Package();
    Package p2 = Package();

    ASSERT_EQ(p1.get_id(), 1);
    ASSERT_EQ(p2.get_id(), 2);
}

TEST(PackageTest, IDfromFreed) {
    {
        Package p1 = Package();
        Package p2 = Package();
    }

    Package p3 = Package();

    ASSERT_EQ(p3.get_id(), 1);
}

TEST(ReceiverPreferencesTest, ProbabilitiesTest) {

    PackageQueue pq(FIFO);
    PackageQueue pq2(FIFO);

    Storehouse p1(1, std::make_unique<PackageQueue>(pq));
    Storehouse p2(2, std::make_unique<PackageQueue>(pq));
    Storehouse p3(3, std::make_unique<PackageQueue>(pq));

    ReceiverPreferences rp = ReceiverPreferences();
    rp.add_receiver(&p1);
    rp.add_receiver(&p2);
    rp.add_receiver(&p3);

    ReceiverPreferences::preferences_t p = rp.get_preferences();
    ASSERT_EQ(p[&p1], 1.0/3.0);
    rp.remove_receiver(&p2);

    p = rp.get_preferences();
    ASSERT_EQ(p[&p1], 0.5);



}