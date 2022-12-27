//
// Created by Seun Suberu on 12/16/22.
//
#include <iostream>
#include "../Util/HashMap/HashMap.h"
#include "../Util/AVLTree/AVLTree.h"
#include "../Indexer/Author/Author.h"
#include "../Indexer/Word/Word.h"
#include "../QueryProcessor/QueryProcessor.h"
#include "../Indexer/Article/Article.h"
using namespace std;
#ifndef UNTITLED_USERINTERFACE_H
#define UNTITLED_USERINTERFACE_H


class UserInterface {
public:
    UserInterface()=default;
    static void start();
    static void clearConsole();
    static void runQuery(AVLTree<Word>& words, HashMap<string, Author*>& authors, HashMap<string, Article*>& articles, char* directory);
    static void outputQueryResult(vector<string>& res, HashMap<string, Article*>& articles, string& directory);
    static void endQuery();
    static string retrivePreview(string& doc, string& dir);
};


#endif //UNTITLED_USERINTERFACE_H
