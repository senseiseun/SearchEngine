//
// Created by seuns on 11/12/2020.
//

#include "Author.h"

#include <utility>

Author::Author(string authorName){
    this->name = std::move(authorName);
    articles = new vector<Pair>();
}

Author::~Author() {
    delete[] this->articles;
}

void Author::printCopy(){

}
string& Author::getAuthorName(){
    return this->name;
}
vector<string> Author::getArticleList(){
    vector<Pair> res = *(this->articles);
    vector<string> returningArray;
    for (auto & article : res) {
        returningArray.push_back(article.word);
    }
    return returningArray;
}
bool Author::operator < (const Author& author) const{
    return this->name.compare(author.name)  < 0;
}

bool Author::operator > (const Author& author) const{
    return this->name.compare(author.name)  > 0;
}

bool Author::operator == (const Author& author) const{
    return this->name  == author.name;
}

void Author::addArticles(string& article) {
    this->articles->push_back(*(new Pair(article)));
}
