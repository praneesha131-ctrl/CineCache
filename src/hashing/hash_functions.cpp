#pragma once
#ifndef HASH_FUNCTIONS_CPP
#define HASH_FUNCTIONS_CPP

#include "../common/headers.h"
using namespace std;

// Two basic hash functions for strings.
class HashFunctions {
public:
    static uint32_t fnv1a(const string& key);

};

uint32_t HashFunctions::fnv1a(const string& key) {
    uint32_t hash = 2166136261U;

    for (char c : key) {
        hash ^= (uint32_t)c;
        hash *= 16777619;
    }

    return hash;
}

#endif
