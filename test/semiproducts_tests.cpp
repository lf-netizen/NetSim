//
// Created by lukas on 14.12.2021.
//

#include "gtest/gtest.h"

#include "package.hpp"

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

