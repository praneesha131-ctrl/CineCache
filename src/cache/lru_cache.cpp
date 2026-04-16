#pragma once
#ifndef LRU_CACHE_CPP
#define LRU_CACHE_CPP

#include "common/headers.h"

#include "data_structures/hash_table.cpp"
#include "data_structures/doubly_linked_list.cpp"
#include "common/types.cpp"

using namespace std;

// LRU Cache - removes oldest item when full
class LRUCache {
private:
    int max_size;
    HashTable<DLLNode<Movie>*> table;
    DoublyLinkedList<Movie> usage_list;

public:
    LRUCache(int size) : max_size(size), table(size) {}

    // Get a movie from cache (most recently used)
    Movie* get(const string& key) {
        DLLNode<Movie>* node = nullptr;

        if (table.search(key, node)) {
            usage_list.moveToFront(node);
            return &node->data;
        }

        return nullptr;
    }

    // Add to cache, return evicted movie if any
    Movie* put_and_get_evicted(const string& key, const Movie& movie) {
        DLLNode<Movie>* node = nullptr;

        if (table.search(key, node)) {
            node->data = movie;
            usage_list.moveToFront(node);
            return nullptr;  // No eviction
        }

        Movie* evicted = nullptr;
        if (table.get_size() >= max_size) {
            DLLNode<Movie>* last_node = usage_list.getLRU();

            if (last_node != nullptr) {
                evicted = new Movie(last_node->data);
                table.remove(last_node->key);
                usage_list.removeNode(last_node);
            }
        }

        DLLNode<Movie>* new_node = usage_list.insertFront(key, movie);
        table.insert(key, new_node);
        return evicted;
    }

    int get_size() const {
        return table.get_size();
    }

    int get_max_size() const {
        return max_size;
    }

    vector<Movie> get_movies() const {
        return usage_list.getAllItems();
    }
};

#endif