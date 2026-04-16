#ifndef CINECACHE_SYSTEM_H
#define CINECACHE_SYSTEM_H

#include "../src/common/headers.h"
#include "cache_node.h"
#include "utils.h"
#include "eviction_policy.h"
#include "cinecache_display.h"
#include "cinecache_scaling.h"
#include "../src/database/simulated_db.cpp"
#include "../src/hashing/consistent_hash.cpp"

using namespace std;

class CineCacheSystem {
private:
    ConsistentHash ring;
    SimulatedDB database;
    map<string, CacheNode*> nodes;
    bool database_loaded;

    CacheNode* get_node_by_id(const string& node_id) {
        map<string, CacheNode*>::iterator it = nodes.find(node_id);
        if (it != nodes.end()) {
            return it->second;
        }
        nodes[node_id] = new CacheNode(node_id, 3);
        return nodes[node_id];
    }

public:
    CineCacheSystem() : database_loaded(false) {
        vector<string> startNodes;
        startNodes.push_back("Node-A");
        startNodes.push_back("Node-B");
        startNodes.push_back("Node-C");
        for (int i = 0; i < (int)startNodes.size(); i++) {
            ring.addNode(startNodes[i]);
            nodes[startNodes[i]] = new CacheNode(startNodes[i], 3);
        }
    }

    ~CineCacheSystem() {
        map<string, CacheNode*>::iterator it;
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            delete it->second;
        }
    }

    // Load movies from a CSV file into the database
    bool load_database(const string& path) {
        database_loaded = database.loadFromFile(path, 250);
        return database_loaded;
    }

    // Check if database is loaded
    bool is_database_loaded() const {
        return database_loaded;
    }

    // Get the number of movies in database
    int get_database_size() const {
        return database.size();
    }

    // Look up a movie in the cache system for a specific user
    // Returns the movie if found, otherwise fetches from database and caches it
    Movie* lookup_movie(const string& user_id, const string& movie_id, bool show_steps = true) {
        string movie_key = "movie:" + movie_id;
        if (show_steps) {
            cout << "\n";
            printLine("=");
            cout << BOLD << MAG << "    CACHE LOOKUP\n" << RST;
            printLine("=");
            printInfo("User ID  : " + string(BOLD) + user_id + RST);
            printInfo("Movie ID : " + string(BOLD) + movie_id + RST);
            cout << "\n";
            printStep(1, "Consistent hashing picks a node for this user.", CYN);
        }
        string node_id = ring.getNode(user_id);
        CacheNode* node = get_node_by_id(node_id);
        node->total_requests++;
        if (show_steps) {
            printSuccess("User '" + user_id + "' was sent to " + string(BOLD) + CYN + node_id + RST);
            pauseMs(150);
            printStep(2, "Checking " + node_id + "'s LRU cache for movie " + movie_id, YLW);
        }
        Movie* movie_from_cache = node->cache.get(movie_key);
        if (movie_from_cache != nullptr) {
            if (show_steps) {
                cout << BGGRN << BBLK << " CACHE HIT " << RST << "\n";
                cout << GRN << "  Movie was found in " << node_id << "'s cache.\n" << RST;
                printLine("-");
            }
            return new Movie(*movie_from_cache);
        }
        if (show_steps) {
            printError("Cache miss. Movie was not in " + node_id + "'s cache.");
            printStep(3, "Fetching the movie from the database.", RED);
        }
        if (!database_loaded) {
            if (show_steps) {
                printError("Database is not loaded yet. Use option [4] first.");
            }
            return nullptr;
        }
        pauseMs(250);
        Movie* movie_from_db = database.fetch(movie_key);
        if (movie_from_db == nullptr) {
            if (show_steps) {
                printError("Movie " + movie_id + " was not found in the database.");
            }
            return nullptr;
        }
        if (show_steps) {
            printSuccess("Fetched \"" + movie_from_db->title + "\" from the database.");
            printStep(4, "Saving the movie in " + node_id + "'s cache.", BLU);
        }
        Movie* evicted = node->cache.put_and_get_evicted(movie_key, *movie_from_db);
        EvictionPolicy::handleEviction(node_id, evicted);
        if (show_steps) {
            EvictionPolicy::handleMovieStored(node->cache.get_size(), node->cache.get_max_size());
            cout << BGBLU << " READY " << RST << "\n";
            printLine("-");
        }
        return movie_from_db;
    }

    void show_cache_state() {
        CineCacheDisplay::showCacheState(nodes);
    }

    void lookup_and_show_movie(const string& user_id, const string& movie_id) {
        Movie* movie = lookup_movie(user_id, movie_id, true);
        CineCacheDisplay::lookupAndShowMovie(user_id, movie_id, movie);
    }

    void show_ring_stats() {
        CineCacheDisplay::showRingStats(ring, nodes);
    }

    void load_database_from_menu() {
        CineCacheDisplay::loadDatabaseFromMenu(database, database_loaded);
    }

    void remove_node_from_menu() {
        CineCacheScaling::removeNodeFromMenu(ring, nodes);
    }
};

#endif
