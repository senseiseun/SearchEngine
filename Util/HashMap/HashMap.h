//
// Created by Seun Suberu on 12/15/22.
//
#include <iostream>
#include "list"
using namespace std;

#ifndef UNTITLED_HASHMAP_H
#define UNTITLED_HASHMAP_H

template <typename K, typename V>
class HashMap {
private:
    class Pair {
    public:
        K first;
        V second;
        Pair(const K& first, const V& second){
            this->first = first;
            this->second = second;
        }
        Pair()= default;
        //operators for AVLTree
        bool operator > (const Pair& pair) const{ return (this->first > pair.first); };
        bool operator < (const Pair& pair) const{ return (this->first < pair.first); };
        bool operator == (const Pair& pair) const{ return (this->first == pair.first); };
        bool operator > (const string& pair) const{ return (this->first > pair); };
        bool operator < (const string& pair) const{ return (this->first < pair); };
        bool operator == (const string& pair) const{ return (this->first == pair); };

    };
    list<Pair*>* base;
    int capacity;
    int size;
    float growthFactor = .10;
    void grow() {
        const int newCapacity = capacity * 2;
        auto newBase = new list<Pair*>[newCapacity];
        for (int i = 0; i < capacity; i++) {
            typename std::list<Pair*>::iterator it;
            for (it = base[i].begin(); it != base[i].end(); ++it){
                Pair* pair = *it;
                int index = getKeyIndex(pair->first, newCapacity);
                newBase[index].push_back(new Pair(pair->first, pair->second));
            }
        }

        base = newBase;
        this->capacity = newCapacity;
    }
public:
    HashMap() {
        capacity = 10;
        size = 0;
        base = new list<Pair*>[10];
    }
    // TODO
    HashMap(HashMap& other) {
        capacity = other.capacity;
        size = other.size;
        base = new list<Pair*>[capacity];
        growthFactor = other.growthFactor;
    }
    // TODO
    HashMap(HashMap* other) {
        capacity = other->capacity;
        size = other->size;
        base = new list<Pair*>[capacity];
        growthFactor = other->growthFactor;
    }

    ~HashMap() {
        delete[] this->base;
    }

    void put(const K& key, const V& value) {
        int maxSize = ((1 - this->growthFactor) * this->capacity);
        if (size + 1 >= maxSize) {
            grow();
        }
        int index = getKeyIndex(key, this->capacity);
        typename std::list<Pair*>::iterator it;
        for (it = base[index].begin(); it != base[index].end(); ++it) {
            Pair* pair = *it;
            if (pair->first == key) {
                pair->second = value;
                return;
            }
        }
        this->size++;
        this->base[index].push_back(new Pair(key, value));
    }

    long long int getKeyIndex(const K& key, int cap) {
        hash<K> myHashFunc;
        long long unsigned int hash = myHashFunc(key);
        return hash % cap;
    }

    V operator[] (const K& key){
        int index = getKeyIndex(key, this->capacity);
        V value;
        typename std::list<Pair*>::iterator it;
        for (it = base[index].begin(); it != base[index].end(); ++it) {
            Pair* pair = *it;
            if (pair->first == key) {
                return pair->second;
            }
        }
        return value;
    }

    V get (const K& key){
        int index = getKeyIndex(key, this->capacity);
        V value;
        typename std::list<Pair*>::iterator it;
        for (it = base[index].begin(); it != base[index].end(); ++it) {
            Pair* pair = *it;
            if (pair->first == key) {
                return pair->second;
            }
        }
        return value;
    }

    bool containsKey (const K& key){
        int index = getKeyIndex(key, this->capacity);
        V value;
        typename std::list<Pair*>::iterator it;
        for (it = base[index].begin(); it != base[index].end(); ++it) {
            Pair* pair = *it;
            if (pair->first == key) {
                return true;
            }
        }
        return false;
    }

    int getSize(){
        return this->size;
    }

    void remove(const K& key) {
        int index = getKeyIndex(key, this->capacity);
        typename std::list<Pair*>::iterator it;
        for (it = this->base[index].begin(); it != this->base[index].end(); ++it) {
            Pair* pair = *it;
            if (pair->first == key) {
                this->base[index].erase(it);
                this->size--;
                break;
            }
        }
    }

    vector<V> getValues() {
        vector<V> res;
        for (int i = 0; i < this->capacity; i++) {
            typename std::list<Pair*>::iterator it;
            for (it = this->base[i].begin(); it != this->base[i].end(); ++it) {
                Pair* pair = *it;
                res.push_back(pair->second);
            }
        }
        return res;
    }

    vector<K> getKeys() {
        vector<K> res;
        for (int i = 0; i < this->capacity; i++) {
            typename std::list<Pair*>::iterator it;
            for (it = this->base[i].begin(); it != this->base[i].end(); ++it) {
                Pair* pair = *it;
                res.push_back(pair->first);
            }
        }
        return res;
    }
};


#endif //UNTITLED_HASHMAP_H
