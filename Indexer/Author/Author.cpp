//
// Created by seuns on 11/12/2020.
//

#include "Author.h"

Author::Author(string authorName){
    this->name = authorName;
    articles = new vector<Pair>();
}

void Author::printCopy(){

}
string& Author::getAuthorName(){
    return this->name;
}
vector<string> Author::getArticleList(){
    vector<Pair> res = *(this->articles);
    vector<string> returningArray;
    for (int i = 0; i < res.size(); i++) {
        returningArray.push_back(res.at(i).word);
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
    return this->name.compare(author.name)  == 0;
}

void Author::addArticles(string& article) {
    this->articles->push_back(*(new Pair(article)));
}
