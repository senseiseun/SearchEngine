#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Util/HashMap/HashMap.h"
#include "Indexer/Word/Word.h"
#include "Indexer/Author/Author.h"
#include "Indexer/Article/Article.h"
#include "Indexer/Index/Index.h"
#include "QueryProcessor/QueryProcessor.h"
#include "UserInterface//UserInterface.h"
#define TEST true

int runCatchTests(int argc, char* const argv[])
{
    //This line of code causes the Catch library to
    //run the tests in the project.

    return Catch::Session().run();
}

int main(int argc, char** argv) {
    if (argc == 1)
    {
        return runCatchTests(argc, argv);
    }
    HashMap<string, Author*> authors;
    AVLTree<Word> words;
    HashMap<string, Article*> articles;
    Index indexer;
    indexer.build(argv[1], authors, words, articles);
    QueryProcessor qp;
    UserInterface ui;
    ui.start();
    ui.runQuery(words, authors, articles);
//    vector<string> res = qp.processQuery(words, authors, "patient AND intent");
//    for (int i = 0; i < 5 && i < res.size(); i++) {
//        cout << res.at(i) << endl;
//        Article* article = articles[res.at(i)];
//        cout << article->getTitle() << " " << endl;
//        vector<string>* authors = article->getAuthors();
//        if (authors != nullptr) {
//            for (string author : *authors) cout << author << " ";
//        }
//        cout << endl;
//    }
    return 0;
}
