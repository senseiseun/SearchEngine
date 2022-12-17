//
// Created by Brandon Herman on 11/15/20.
//
#include "Word.h"


Word::Word() {
    freq = 0;
    word = "";
    docTree = new AVLTree<Pair>();
}

Word::Word(string& newWord) {
    freq = 1; //if making word, it shows up atleast once
    word = newWord;
    docTree = new AVLTree<Pair>();
}

Word::~Word() {
    delete this->docTree;
}

void Word::increaseFreq() {
    freq++;
}

string Word::getWord() {
    return word;
}

int Word::getFreq() {
    return freq;
}

void Word::setWord(string newWord) {
    word = newWord;
}

bool Word::operator == (const string& word) const{
    return this->word.compare(word)  == 0;
}

bool Word::operator == (const Word& word) const{
    return this->word.compare(word.word)  == 0;
}

bool Word::operator > (const Word& word) const{
    return this->word.compare(word.word)  > 0;
}

bool Word::operator < (const Word& word) const{
    return this->word.compare(word.word)  < 0;
}

bool Word::operator > (const string& word) const{
    return this->word.compare(word)  > 0;
}

bool Word::operator < (const string& word) const{
    return this->word.compare(word)  < 0;
}

void Word::insertDoc(string &doc) {
    Pair pair(doc);
    docTree->insert(pair);
}

bool Word::hasDocument(string &documentID) {
    return docTree->contains(*(new Pair(documentID)));
}

void Word::increaseDocumentFrequency(string& documentID){
    docTree->getValue(*(new Pair(documentID)))->count++;
    Pair* doc = (docTree->getValue(*(new Pair(documentID))));
}
string Word::getDocument(string& documentID){
    return docTree->getValue(documentID)->word;
}

void Word::newDoc(string& documentID, string& documentTitle, string& firstAuthor){

};

vector<Pair*> Word::getDocTreeInOrder() {
    vector<Pair*> res = docTree->toArrayInOrder();
    return res;
}

void Word::printWordDocuments(char*& documentPath){
}

void Word::wipeDocuments() {
    this->docTree->emptyTree();
    delete docTree;
}

int Word::getDocTreeSize() {
    return docTree->getSize();
}