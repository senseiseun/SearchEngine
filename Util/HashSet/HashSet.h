//
// Created by Seun Suberu on 12/15/22.
//

#include <iostream>
#include "list"
using namespace std;
#ifndef UNTITLED_HASHSET_H
#define UNTITLED_HASHSET_H

template <typename V>
class HashSet {
private:
    class Entry {
    public:
        V first;
        explicit Entry(const V& first){
            this->first = first;
        }
        Entry()= default;
        //operators for AVLTree
        bool operator > (const Entry& entry) const{ return (this->first > entry.first); };
        bool operator < (const Entry& entry) const{ return (this->first < entry.first); };
        bool operator == (const Entry& entry) const{ return (this->first == entry.first); };
        bool operator > (const string& entry) const{ return (this->first > entry); };
        bool operator < (const string& entry) const{ return (this->first < entry); };
        bool operator == (const string& entry) const{ return (this->first == entry); };

    };
    list<Entry*>* base;
    int capacity;
    int size;
    float growthFactor = .10;
    void grow() {
        const int newCapacity = capacity * 2;
        auto newBase = new list<Entry*>[newCapacity];
        for (int i = 0; i < capacity; i++) {
            typename std::list<Entry*>::iterator it;
            for (it = base[i].begin(); it != base[i].end(); ++it){
                Entry* entry = *it;
                int index = getKeyIndex(entry->first, newCapacity);
                newBase[index].push_back(new Entry(entry->first));
            }
        }

        base = newBase;
        this->capacity = newCapacity;
    }
public:
    HashSet() {
        capacity = 10;
        size = 0;
        base = new list<Entry*>[capacity];
    }
    // TODO
    HashSet(HashSet<V>& other) {
        capacity = other.capacity;
        size = other.size;
        base = new list<Entry*>[capacity];
        growthFactor = other.growthFactor;
    }
    // TODO
    HashSet(HashSet* other) {
        capacity = other->capacity;
        size = other->size;
        base = new list<Entry*>[capacity];
        growthFactor = other->growthFactor;
    }

    ~HashSet() {
        delete[] this->base;
    }

    void add(const V& elem) {
        int maxSize = ((1 - this->growthFactor) * this->capacity);
        if (size + 1 >= maxSize) {
            grow();
        }
        int index = getKeyIndex(elem, this->capacity);
        typename std::list<Entry*>::iterator it;
        for (it = base[index].begin(); it != base[index].end(); ++it) {
            Entry* Entry = *it;
            if (Entry->first == elem) {
                return;
            }
        }
        this->size++;
        this->base[index].push_back(new Entry(elem));
    }

    long long int getKeyIndex(const V& elem, int cap) {
        hash<V> myHashFunc;
        long long unsigned int hash = myHashFunc(elem);
        return hash % cap;
    }

    bool contains (const V& elem){
        int index = getKeyIndex(elem, this->capacity);
        V value;
        typename std::list<Entry*>::iterator it;
        for (it = base[index].begin(); it != base[index].end(); ++it) {
            Entry* Entry = *it;
            if (Entry->first == elem) {
                return true;
            }
        }
        return false;
    }

    //returns number of elements
    int getSize(){
        return this->size;
    }

    void remove(const V& elem) {
        int index = getKeyIndex(elem, this->capacity);
        typename std::list<Entry*>::iterator it;
        for (it = this->base[index].begin(); it != this->base[index].end(); ++it) {
            Entry* Entry = *it;
            if (Entry->first == elem) {
                this->base[index].erase(it);
                this->size--;
                break;
            }
        }
    }

    vector<V> intersection(HashSet<V>& other) {
        vector<V> res;
        for (int i = 0; i < this->capacity; i++) {
            typename std::list<Entry *>::iterator it;
            for (it = this->base[i].begin(); it != this->base[i].end(); ++it) {
                Entry* entry = *it;
                if (other.contains(entry->first)) res.push_back(entry->first);
            }
        }
        return res;
    }
};


#endif //UNTITLED_HASHSET_H
