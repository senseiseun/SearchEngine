//
// Created by Seun Suberu on 12/15/22.
//
#include <iostream>
#include <vector>

using namespace std;
#ifndef UNTITLED_ARTICLE_H
#define UNTITLED_ARTICLE_H


class Article {
private:
    string articleTitle;
    string printCopy;
    string datePublished;
    string articleID;
    vector<string>* authors;
    double ratio;
public:
    Article(string, string, string, string);
    Article(string, string);
    ~Article();
    string& getPrintCopy();
    string& getTitle();
    string& getDatePub();
    string& getID();
    vector<string>* getAuthors();
    void addAuthor(string& author);
    void setRatio(double ratio);
    double getRatio();
};


#endif //UNTITLED_ARTICLE_H
