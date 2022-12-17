//
// Created by Seun Suberu on 12/15/22.
//

#include "../../catch.hpp"
#include "HashSet.h"

TEST_CASE( "HashSet Class" ) {
    auto* set = new HashSet<int>();
    SECTION("Checking value and growth"){
        for (int i = 1; i <= 100; i++) {
            set->add(i);
            CHECK(set->getSize() == i);
        }
        for (int i = 1; i <= 100; i++) {
            CHECK(set->contains(i));
        }
    }
    SECTION("Remove and check size"){
        for (int i = 1; i <= 100; i++) {
            set->add(i);
            CHECK(set->getSize() == i);
        }
        for (int i = 100; i > 0; i--) {
            set->remove(i);
            CHECK(set->getSize() == i-1);
            CHECK(!set->contains(i));
        }

    }
}
