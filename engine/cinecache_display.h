#ifndef CINECACHE_DISPLAY_H
#define CINECACHE_DISPLAY_H

#include "../src/common/headers.h"
#include "utils.h"
#include "cache_node.h"
#include "../src/common/types.cpp"
#include "../src/hashing/consistent_hash.cpp"
#include "../src/database/simulated_db.cpp"

using namespace std;

// Display functions for CineCache system
class CineCacheDisplay {
public:
    static void showCacheState(map<string, CacheNode*>& nodes) {
        cout << "\n";
        printLine("=");
        cout << BOLD << CYN << "    LRU CACHE STATE\n" << RST;
        printLine("=");
        map<string, CacheNode*>::iterator it;
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            CacheNode* node = it->second;
            cout << "\n  " << BOLD << MAG << node->id << RST << "\n";
            
            vector<Movie> movies = node->cache.get_movies();
            for (int i = 0; i < 3; i++) {
                cout << "  " << BOLD << BLU << "[" << i+1 << "]" << RST << " ";
                if (i < (int)movies.size()) {
                    cout << GRN << movies[i].title << RST << "\n";
                } else {
                    cout << DIM << "[EMPTY]" << RST << "\n";
                }
            }
        }
        cout << "\n";
        printLine("-");
    }

    static void lookupAndShowMovie(const string& userId, const string& movieId, Movie* movie) {
        if (movie == nullptr) {
            cout << RED << "\n  Could not retrieve movie " << movieId << "\n" << RST;
            return;
        }
        cout << "\n";
        printLine("=");
        cout << BOLD << YLW << "    MOVIE DETAILS\n" << RST;
        printLine("=");
        cout << "  " << BOLD << WHT << movie->title << RST;
        if (movie->year > 0) {
            cout << "  (" << movie->year << ")";
        }
        cout << "\n\n";
        if (movie->rating > 0) {
            cout << "  * Rating  : " << YLW << BOLD << fixed << setprecision(1)
                 << movie->rating << RST << " / 10\n";
        }
        if (!movie->genre.empty()) {
            cout << "  * Genre   : " << movie->genre << "\n";
        }
        if (!movie->director.empty()) {
            cout << "  * Director: " << movie->director << "\n";
        }
        if (!movie->description.empty()) {
            cout << "\n  Summary:\n";
            string text = movie->description;
            int start = 0;
            while (start < (int)text.size()) {
                int end = min(start + 56, (int)text.size());
                if (end < (int)text.size()) {
                    int lastSpace = text.rfind(' ', end);
                    if (lastSpace > start) {
                        end = lastSpace;
                    }
                }
                cout << "    " << text.substr(start, end - start) << "\n";
                if (end < (int)text.size()) {
                    start = end + 1;
                } else {
                    start = end;
                }
            }
        }
        cout << "\n";
        printLine("-");
        delete movie;
    }

    static void showRingStats(ConsistentHash& ring, map<string, CacheNode*>& nodes) {
        cout << "\n";
        printLine("=");
        cout << BOLD << BLU << "    CONSISTENT HASH RING\n" << RST;
        printLine("=");
        ring.printStats();
        cout << "\n  " << BOLD << "Nodes:\n";
        map<string, CacheNode*>::iterator it;
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            CacheNode* node = it->second;
            cout << "    [o] " << BOLD << node->id << RST
                 << "   LRU: " << node->cache.get_size() << "/" << node->cache.get_max_size()
                 << "   Requests: " << node->total_requests << "\n";
        }
        printLine("-");
    }

    static void loadDatabaseFromMenu(SimulatedDB& database, bool& databaseLoaded) {
        cout << "\n";
        printLine("-");
        cout << BOLD << "    LOAD MOVIE DATABASE\n" << RST;
        printLine("-");
        vector<string> possiblePaths;
        possiblePaths.push_back("data/movies_db.txt");
        possiblePaths.push_back("../data/movies_db.txt");
        possiblePaths.push_back("data/movies.txt");
        possiblePaths.push_back("../data/movies.txt");
        possiblePaths.push_back("data/imdb_top_250.txt");
        possiblePaths.push_back("../data/imdb_top_250.txt");
        for (int i = 0; i < (int)possiblePaths.size(); i++) {
            if (database.loadFromFile(possiblePaths[i], 250)) {
                databaseLoaded = true;
                cout << GRN << "  + Loaded from: " << possiblePaths[i] << "\n" << RST;
                cout << "    " << database.size() << " movies in database.\n";
                printLine("-");
                return;
            }
        }
        cout << "  Auto-detect failed. Enter path: ";
        string path;
        getline(cin, path);
        if (path.empty()) {
            printLine("-");
            return;
        }
        if (database.loadFromFile(path, 250)) {
            databaseLoaded = true;
            cout << GRN << "  + Loaded " << database.size() << " movies.\n" << RST;
        } else {
            cout << RED << "  x Could not load: " << path << "\n" << RST;
        }
        printLine("-");
    }
};

#endif
