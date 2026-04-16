#pragma once
#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include <string>
#include <cstdint>
#include <vector>
using namespace std;

// One entry in the hash table.
template <typename T>
struct HashEntry {
    string key;
    T value;
    bool occupied;
    bool deleted;   

    HashEntry() : key(""), occupied(false), deleted(false) {}
};

// A simple hash table that uses linear probing.
template <typename T>
class HashTable {
private:
    vector<HashEntry<T>> table;
    int capacity;
    int count;
    const double LOAD_FACTOR = 0.75;

    uint32_t hash(const string& key) const {
        uint32_t h = 0;

        for (char c : key) {
            h = h * 31 + c;
        }

        return h % capacity;
    }

    void resize() {
        int oldCapacity = capacity;
        vector<HashEntry<T>> oldTable = table;

        capacity *= 2;
        table.clear();
        table.resize(capacity);
        count = 0;

        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i].occupied && !oldTable[i].deleted) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
    }

public:
    HashTable(int initialCapacity = 16) : capacity(initialCapacity), count(0) {
        table.resize(capacity);
    }

    void insert(const string& key, const T& value) {
        // Check load factor and resize if needed
        if ((double)count / capacity >= LOAD_FACTOR) {
            resize();
        }

        uint32_t idx = hash(key);
        uint32_t probes = 0;

        // Try to find existing key or empty slot
        while (probes < capacity) {
            if (table[idx].occupied && !table[idx].deleted && table[idx].key == key) {
                // Key exists, update value
                table[idx].value = value;
                return;
            }
            if (!table[idx].occupied || table[idx].deleted) {
                // Found empty or deleted slot
                bool wasCompletelyEmpty = !table[idx].occupied && !table[idx].deleted;
                table[idx].occupied = true;
                table[idx].deleted = false;
                table[idx].key = key;
                table[idx].value = value;
                
                // Increment count only if was completely empty or being undeleted
                if (wasCompletelyEmpty) count++;
                return;
            }
            idx = (idx + 1) % capacity;
            probes++;
        }
    }

    bool search(const string& key, T& value) const {
        uint32_t idx = hash(key);
        uint32_t startIdx = idx;
        int probes = 0;

        while ((table[idx].occupied || table[idx].deleted) && probes < capacity) {
            if (table[idx].occupied && !table[idx].deleted && table[idx].key == key) {
                value = table[idx].value;
                return true;
            }

            idx = (idx + 1) % capacity;
            probes++;
        }

        return false;
    }



    bool remove(const string& key) {
        uint32_t idx = hash(key);
        int probes = 0;

        while ((table[idx].occupied || table[idx].deleted) && probes < capacity) {
            if (table[idx].occupied && !table[idx].deleted && table[idx].key == key) {
                table[idx].deleted = true;  // Mark as deleted, don't clear occupied
                table[idx].key = "";
                count--;
                return true;
            }

            idx = (idx + 1) % capacity;
            probes++;
        }

        return false;
    }

    int get_size() const { return count; }
    int get_capacity() const { return capacity; }
};

#endif
