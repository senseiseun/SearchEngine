//
// Created by Seun Suberu on 12/16/22.
//

#include "QueryProcessor.h"

vector<Pair*> QueryProcessor::processAND(AVLTree<Word>& words, string& a, string& b) {
    Word* res1 = new Word();
    Word* res2 = new Word();
    HashMap<string, Pair*> set1;
    HashMap<string, Pair*> set2;
    Porter2Stemmer::stem(a);
    Porter2Stemmer::stem(b);
    if (words.contains(a)) {
        res1->setWord(a);
        res1 = words.getValue(*res1);
    }
    vector<Pair*> wordVec1 = res1->getDocTreeInOrder();
    for (Pair* pair: wordVec1) {
        set1.put(pair->word, pair);
    }
    if (words.contains(b)) {
        res2->setWord(b);
        res2 = words.getValue(*res2);
    }
    vector<Pair*> wordVec2 = res2->getDocTreeInOrder();
    for (Pair* pair: wordVec2) {
        set2.put(pair->word, pair);
    }
    vector<Pair*> values;
    for (auto & key : set1.getKeys()) {
        if (set2.containsKey(key)) {
            values.push_back(new Pair(key, set1[key]->count + set2[key]->count));
        }
    }
    return values;
}

vector<Pair*> QueryProcessor::processAND(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b) {
    Word* res2 = new Word();
    HashMap<string, Pair*> set1;
    HashMap<string, Pair*> set2;
    Porter2Stemmer::stem(b);
    if (words.contains(b)) {
        res2->setWord(b);
        res2 = words.getValue(*res2);
    }
    vector<Pair*> wordVec2 = res2->getDocTreeInOrder();
    for (Pair* pair: wordVec2) {
        set2.put(pair->word, pair);
    }
    vector<Pair*> values;
    for (auto & key : set1.getKeys()) {
        if (set2.containsKey(key)) {
            values.push_back(new Pair(key, set1[key]->count + set2[key]->count));
        }
    }
    return values;
}

vector<Pair*> QueryProcessor::processOR(AVLTree<Word>& words, string& a, string& b) {
    Word* res1 = new Word();
    Word* res2 = new Word();
    Porter2Stemmer::stem(a);
    Porter2Stemmer::stem(b);
    if (words.contains(a)) {
        res1->setWord(a);
        res1 = words.getValue(*res1);
    }
    vector<Pair*> wordVec1 = res1->getDocTreeInOrder();
    if (words.contains(b)) {
        res2->setWord(b);
        res2 = words.getValue(*res2);
    }
    vector<Pair*> wordVec2 = res2->getDocTreeInOrder();
    HashMap<string, Pair*> allWord;
    for (auto & pair : wordVec1) {
        if (!allWord.containsKey(pair->word)) {
            allWord.put(pair->word, new Pair(pair->word));
        }
        allWord[pair->word]->count += pair->count;
    }
    for (auto & pair : wordVec2) {
        if (!allWord.containsKey(pair->word)) {
            allWord.put(pair->word, new Pair(pair->word));
        }
        allWord[pair->word]->count += pair->count;
    }
    vector<Pair*> values = allWord.getValues();
    return values;
}

vector<Pair*> QueryProcessor::processOR(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b) {
    Word* res2 = new Word();
    Porter2Stemmer::stem(b);
    if (words.contains(b)) {
        res2->setWord(b);
        res2 = words.getValue(*res2);
    }
    vector<Pair*> wordVec2 = res2->getDocTreeInOrder();
    HashMap<string, Pair*> allWord;
    for (auto & pair : wordVec1) {
        if (!allWord.containsKey(pair->word)) {
            allWord.put(pair->word, new Pair(pair->word));
        }
        allWord[pair->word]->count += pair->count;
    }
    for (auto & pair : wordVec2) {
        if (!allWord.containsKey(pair->word)) {
            allWord.put(pair->word, new Pair(pair->word));
        }
        allWord[pair->word]->count += pair->count;
    }
    vector<Pair*> values = allWord.getValues();
    return values;
}

vector<Pair*> QueryProcessor::processNOT(AVLTree<Word>& words, vector<Pair*>& wordVec1, string& b) {
    HashMap<string, Pair*> set1;
    HashMap<string, Pair*> set2;
    Porter2Stemmer::stem(b);
    Word* res2 = new Word();
    for (Pair* pair: wordVec1) {
        set1.put(pair->word, pair);
    }
    if (words.contains(b)) {
        res2->setWord(b);
        res2 = words.getValue(*res2);
    }
    vector<Pair*> wordVec2 = res2->getDocTreeInOrder();
    for (Pair* pair: wordVec2) {
        set2.put(pair->word, pair);
    }
    vector<Pair*> values;
    for (auto & key : set1.getKeys()) {
        if (!set2.containsKey(key)) {
            values.push_back(new Pair(key, set1[key]->count + set2[key]->count));
        }
    }
    return values;
}
void QueryProcessor::processDocumentVector(vector<Pair*>& vec) {
    sort(vec.begin(), vec.end(), [](Pair* i1, Pair* i2) -> bool {return (i1->count > i2->count);});
}

vector<string> QueryProcessor::processQuery(AVLTree<Word>& words, HashMap<string, Author*>& authors, string query) {
    vector<string> tokens;
    stringstream ss(query);
    string temp;
    enum {AND, OR, NOT};
    int action = -1;
    while(ss >> temp){
        tokens.push_back(temp);
    }
    vector<string> stack;
    vector<Pair*> res;
    for (string token: tokens) {
        if (token == "AND") {
            action = AND;
        } else if (token == "OR") {
            action = OR;
        } else if (token == "NOT") {
            action = NOT;
        } else {
            if (action == -1) {
                stack.push_back(token);
            } else {
                switch (action) {
                    case AND: {
                        if (!stack.empty()) {
                            string str = stack.back();
                            stack.pop_back();
                            vector<Pair *> get = processAND(words, str, token);
                            res = get;
                        } else {
                            vector<Pair *> get = processAND(words, res, token);
                            res = get;
                        }
                        break;
                    }
                    case OR: {
                        if (!stack.empty()) {
                            string str = stack.back();
                            vector<Pair *> get = processOR(words, str, token);
                            res = get;
                        } else {
                            vector<Pair *> get = processOR(words, res, token);
                            res = get;
                        }
                        break;
                    }
                    case NOT: {
                        vector<Pair *> get = processNOT(words, res, token);
                        res = get;
                        break;
                    }
                    default: {

                    }
                }
            }
        }
    }
    processDocumentVector(res);
    vector<string> finalList;
    for (Pair* pair : res) {
        finalList.push_back(pair->word);
    }
    return finalList;
}