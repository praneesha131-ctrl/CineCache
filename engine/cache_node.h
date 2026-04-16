#ifndef CACHE_NODE_H
#define CACHE_NODE_H

#include <string>
#include "../src/cache/lru_cache.cpp"

// Cache node in the distributed system
struct CacheNode {
    std::string id;
    LRUCache cache;
    int total_requests;
    
    CacheNode(const std::string& node_id, int cache_size)
        : id(node_id), cache(cache_size), total_requests(0) {
    }
};

#endif 
