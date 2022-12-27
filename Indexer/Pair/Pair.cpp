//
// Created by Seun Suberu on 12/16/22.
//

#include "Pair.h"

#include <utility>

Pair::Pair (string word) {
    this->word = std::move(word);
    this->count = 0;
}
Pair::Pair (string word, int count) {
    this->word = std::move(word);
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
    return this->word == rhs.word;
}