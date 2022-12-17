//
// Created by Seun Suberu on 12/15/22.
//

#include "../../catch.hpp"
#include "HashMap.h"

TEST_CASE( "HashMap Class" ) {
    auto* map = new HashMap<int, int>();
    SECTION("Checking value and growth"){
        for (int i = 1; i <= 100; i++) {
            map->put(i, i);
            CHECK(map->getSize() == i);
        }
        for (int i = 1; i <= 100; i++) {
            cout << (*map)[i] << endl;
            CHECK((*map)[i] == i);
        }
    }
    SECTION("Remove and check size"){
        for (int i = 1; i <= 100; i++) {
            map->put(i, i);
            CHECK(map->getSize() == i);
        }
        for (int i = 100; i > 0; i--) {
            map->remove(i);
            CHECK(map->getSize() == i-1);
            CHECK(!map->containsKey(i));
        }

    }
}
