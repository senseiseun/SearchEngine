//
// Created by Seun Suberu on 12/15/22.
//

#include "Article.h"

#include <utility>

Article::Article(string articleTitle, string printCopy, string datePublished, string articleID){
    this->articleID = std::move(articleID);
    this->printCopy = std::move(printCopy);
    this->datePublished = std::move(datePublished);
    this->articleTitle = std::move(articleTitle);
    this->authors = new vector<string>();
    this->ratio = 0;
}

Article::Article(string articleTitle, string articleID){
    this->articleID = std::move(articleID);
    this->articleTitle = std::move(articleTitle);
    this->authors = new vector<string>();
    this->ratio = 0;
}

Article::~Article() {
    delete[] this->authors;
}

string& Article::getPrintCopy(){
    return this->printCopy;
}

string& Article::getTitle(){
    return this->articleTitle;
}
string& Article::getDatePub(){
    return this->datePublished;
}
string& Article::getID(){
    return this->articleID;
}

vector<string>* Article::getAuthors() {
    return this->authors;
}

void Article::addAuthor(string& author) {
    this->authors->push_back(author);
}

void Article::setRatio(double newRatio) {
    this->ratio = newRatio;
}

double Article::getRatio() {
    return this->ratio;
}