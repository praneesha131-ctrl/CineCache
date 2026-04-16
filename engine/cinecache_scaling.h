#ifndef CINECACHE_SCALING_H
#define CINECACHE_SCALING_H

#include "../src/common/headers.h"
#include "utils.h"
#include "cache_node.h"
#include "../src/hashing/consistent_hash.cpp"

using namespace std;

// Scaling and removal operations for CineCache
class CineCacheScaling {
public:
    static void removeNodeFromMenu(ConsistentHash& ring, map<string, CacheNode*>& nodes) {
        cout << "\n";
        printLine("=");
        cout << BOLD << RED << "    REMOVE A NODE (Power Saving)\n" << RST;
        printLine("=");

        vector<string> allNodes;
        map<string, CacheNode*>::iterator it;
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            allNodes.push_back(it->first);
        }

        cout << "\n  Available nodes to remove:\n";
        for (int i = 0; i < (int)allNodes.size(); i++) {
            cout << "    " << allNodes[i] << "\n";
        }

        cout << "\n  Enter node name to remove: ";
        string nodeToRemove;
        getline(cin, nodeToRemove);

        if (nodeToRemove.empty()) {
            cout << RED << "  x Empty input.\n" << RST;
            printLine("-");
            return;
        }

        bool nodeExists = false;
        for (int i = 0; i < (int)allNodes.size(); i++) {
            if (allNodes[i] == nodeToRemove) {
                nodeExists = true;
                break;
            }
        }

        if (!nodeExists) {
            cout << RED << "  x Node not found: " << nodeToRemove << "\n" << RST;
            printLine("-");
            return;
        }

        ring.removeNode(nodeToRemove);
        
        map<string, CacheNode*>::iterator nodeIt = nodes.find(nodeToRemove);
        if (nodeIt != nodes.end()) {
            delete nodeIt->second;
            nodes.erase(nodeIt);
        }

        cout << RED << "  x Removed: " << nodeToRemove << "\n" << RST;
        cout << "  Remaining nodes: " << nodes.size() << "\n";
        
        printLine("-");
    }
};

#endif
