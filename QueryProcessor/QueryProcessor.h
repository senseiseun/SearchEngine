//
// Created by Seun Suberu on 12/16/22.
//

#include <iostream>
#include "../Util/HashMap/HashMap.h"
#include "../Util/HashSet/HashSet.h"
#include "../Util/AVLTree/AVLTree.h"
#include "../Indexer/Author/Author.h"
#include "../Indexer/Word/Word.h"
#include "../Indexer/Article/Article.h"
#include "../Stemmer/porter2_stemmer.h"
#include "sstream"

using namespace std;
#ifndef UNTITLED_QUERYPROCESSOR_H
#define UNTITLED_QUERYPROCESSOR_H


class QueryProcessor {
public:
    QueryProcessor() = default;
    static vector<Pair*> processAND(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b);
    static vector<Pair*> processOR(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b);
    static vector<Pair*> processNOT(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b);
    static vector<Pair*> processAUTHOR(HashMap<string, Author*>& authors, vector<Pair*>& wordVec1, string& b);
    static void processDocumentVector(vector<Pair*>&);
    static vector<string> processQuery(AVLTree<Word>& words, HashMap<string, Author*>& authors, HashMap<string, Article*>& articles, string& query);
};


#endif //UNTITLED_QUERYPROCESSOR_H
