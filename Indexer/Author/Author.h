//
// Created by seuns on 11/12/2020.
//
#include "vector"
#include "../Pair/Pair.h"
using namespace std;

#ifndef AUTHOR_H
#define AUTHOR_H
class Author{
    private:
        string name;
        vector<Pair>* articles;
    public:
        Author(){}
        ~Author();
        Author(string);
        void printCopy();
        string& getAuthorName();
        vector<string> getArticleList();
        void addArticles(string& article);
        bool operator < (const Author& author) const;
        bool operator > (const Author& author) const;
        bool operator == (const Author& author) const;

    };
#endif //AUTHOR_H
