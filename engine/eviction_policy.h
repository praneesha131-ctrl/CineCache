#ifndef EVICTION_POLICY_H
#define EVICTION_POLICY_H

#include "../src/common/headers.h"
#include "utils.h"
#include "../src/common/types.cpp"

using namespace std;

// EvictionPolicy handles what to do when a movie is evicted from cache
class EvictionPolicy {
public:
    // Called when a movie is evicted from the cache
    static void handleEviction(const string& nodeId, Movie* evictedMovie) {
        if (evictedMovie == nullptr) {
            return;  // No eviction happened
        }

        printError("Evicting \"" + evictedMovie->title + "\" from " + nodeId + "'s cache.");
        delete evictedMovie;
    }

    // Called when a movie is successfully stored in cache (with optional eviction)
    static void handleMovieStored(int cacheSize, int maxSize) {
        printSuccess("Movie stored in cache. Cache size is now " +
                     to_string(cacheSize) + "/" + to_string(maxSize));
    }
};

#endif
