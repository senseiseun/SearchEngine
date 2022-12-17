//
// Created by Seun Suberu on 12/16/22.
//

#include <iostream>
#include "../Util/HashMap/HashMap.h"
#include "../Util/AVLTree/AVLTree.h"
#include "../Indexer/Author/Author.h"
#include "../Indexer/Word/Word.h"
#include "../Stemmer/porter2_stemmer.h"
#include "sstream"

using namespace std;
#ifndef UNTITLED_QUERYPROCESSOR_H
#define UNTITLED_QUERYPROCESSOR_H


class QueryProcessor {
public:
    QueryProcessor() = default;
    vector<Pair*> processAND(AVLTree<Word>& words, string& a, string& b);
    vector<Pair*> processAND(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b);
    vector<Pair*> processOR(AVLTree<Word>& words, string& a, string& b);
    vector<Pair*> processOR(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b);
    vector<Pair*> processNOT(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b);
    void processDocumentVector(vector<Pair*>&);
    vector<string> processQuery(AVLTree<Word>& words, HashMap<string, Author*>& authors, string query);
};


#endif //UNTITLED_QUERYPROCESSOR_H
