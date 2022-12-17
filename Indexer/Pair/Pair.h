//
// Created by Seun Suberu on 12/16/22.
//

#include <iostream>
using namespace std;

#ifndef PAIR_H
#define PAIR_H

class Pair {
public:
    string word;
    int count;
    Pair (string word);
    Pair (string word, int count);
    Pair();
    bool operator<(const Pair& rhs) const;
    bool operator > (const Pair& rhs) const;
    bool operator == (const Pair& rhs) const;
};

#endif //PAIR_H
