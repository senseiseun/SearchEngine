//
// Created by Seun Suberu on 12/16/22.
//

#include "Pair.h"

Pair::Pair (string word) {
    this->word = word;
    this->count = 0;
}
Pair::Pair (string word, int count) {
    this->word = word;
    this->count = count;
}
Pair::Pair() {
    this->count = 0;
}
bool Pair::operator<(const Pair& rhs) const {
    return this->word.compare(rhs.word) < 0;
}
bool Pair::operator > (const Pair& rhs) const {
    return this->word.compare(rhs.word) > 0;
}
bool Pair::operator == (const Pair& rhs) const {
    return this->word.compare(rhs.word) == 0;
}