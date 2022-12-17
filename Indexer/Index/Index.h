//
// Created by Seun Suberu on 12/16/22.
//

#include <iostream>
#include "../Article/Article.h"
#include "../Author/Author.h"
#include "../../Util/HashMap/HashMap.h"
#include "../../Util/AVLTree/AVLTree.h"
#include "../Word/Word.h"
using namespace std;
#ifndef UNTITLED_INDEX_H
#define UNTITLED_INDEX_H


class Index {
public:
    int build(const char* dir, HashMap<string, Author*>& authors, AVLTree<Word>& words, HashMap<string, Article*>& articles);
};


#endif //UNTITLED_INDEX_H
