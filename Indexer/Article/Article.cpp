//
// Created by Seun Suberu on 12/15/22.
//

#include "Article.h"

Article::Article(string articleTitle, string printCopy, string datePublished, string articleID){
    this->articleID = articleID;
    this->printCopy = printCopy;
    this->datePublished = datePublished;
    this->articleTitle = articleTitle;
    this->authors = new vector<string>();
    this->ratio = 0;
}

Article::Article(string articleTitle, string articleID){
    this->articleID = articleID;
    this->articleTitle = articleTitle;
    this->authors = new vector<string>();
    this->ratio = 0;
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

void Article::setRatio(double ratio) {
    this->ratio = ratio;
}

double Article::getRatio() {
    return this->ratio;
}