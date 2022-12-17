cmake_minimum_required(VERSION 3.22)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Util/HashMap/HashMap.h catch.hpp Util/HashMap/HashMap_test.cpp Util/HashSet/HashSet.h Util/HashSet/HashSet_test.cpp Util/AVLTree/AVLTree.h Indexer/Indexer.cpp Indexer/Article/Article.cpp Indexer/Article/Article.h Indexer/Word/Word.h Indexer/Word/Word.cpp Util/AVLTree/AVLTree_test.cpp Indexer/Index/Index.cpp Indexer/Index/Index.h Indexer/Pair/Pair.h Indexer/Author/Author.h Indexer/Author/Author.cpp Indexer/Pair/Pair.cpp Stemmer/porter2_stemmer.cpp Stemmer/porter2_stemmer.h QueryProcessor/QueryProcessor.cpp QueryProcessor/QueryProcessor.h UserInterface/UserInterface.cpp UserInterface/UserInterface.h)
