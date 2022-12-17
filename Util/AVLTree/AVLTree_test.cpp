//
// Created by Seun Suberu on 12/16/22.
//

#include "../../catch.hpp"
#include "AVLTree.h"

TEST_CASE( "AVLTree Class" ) {
    auto* tree = new AVLTree<int>();
    SECTION("Checking value and growth"){
        for (int i = 1; i <= 100; i++) {
            tree->insert(i);
            CHECK(tree->getSize() == i);
        }
        for (int i = 1; i <= 100; i++) {
            CHECK(tree->contains(i));
        }
        cout << tree->height() << endl;
    }
}
