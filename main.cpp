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

int runCatchTests()
{
    //This line of code causes the Catch library to
    //run the tests in the project.

    return Catch::Session().run();
}

int main(int argc, char** argv) {
    if (argc == 1)
    {
        return runCatchTests();
    }
    HashMap<string, Author*> authors;
    AVLTree<Word> words;
    HashMap<string, Article*> articles;
    Index::build(argv[1], authors, words, articles);
    UserInterface::start();
    UserInterface::runQuery(words, authors, articles, argv[1]);
    UserInterface::endQuery();
    return 0;
}
