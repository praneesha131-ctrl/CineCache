#pragma once
#ifndef CONSISTENT_HASH_CPP
#define CONSISTENT_HASH_CPP

#include "../common/headers.h"
#include "hash_functions.cpp"
using namespace std;

// A simple consistent hashing ring.
// We put many virtual copies of each node on the ring
// so the load is spread more evenly.

class ConsistentHash {
private:
    struct VirtualNode {
        uint32_t hash;
        string nodeId;
    };

    vector<VirtualNode> ring;
    vector<string> nodes;
    int virtualNodesPerNode;

    int findNodeIndex(uint32_t hash) const;

public:
    ConsistentHash(int vnodes = 150);

    void addNode(const string& nodeId);

    void removeNode(const string& nodeId);

    string getNode(const string& key) const;

    int getNodeCount() const { return nodes.size(); }
    int getRingSize() const { return ring.size(); }
    void printStats() const;
};

ConsistentHash::ConsistentHash(int vnodes) : virtualNodesPerNode(vnodes) {
}

int ConsistentHash::findNodeIndex(uint32_t hash) const {
    int left = 0;
    int right = ring.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (ring[mid].hash < hash) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (left >= (int)ring.size()) {
        left = 0;
    }

    return left;
}

void ConsistentHash::addNode(const string& nodeId) {
    for (int i = 0; i < (int)nodes.size(); i++) {
        if (nodes[i] == nodeId) {
            return;
        }
    }

    nodes.push_back(nodeId);

    for (int i = 0; i < virtualNodesPerNode; i++) {
        string virtualKey = nodeId + "#" + to_string(i);
        uint32_t virtualHash = HashFunctions::fnv1a(virtualKey);
        ring.push_back({virtualHash, nodeId});
    }

    sort(ring.begin(), ring.end(), [](const VirtualNode& a, const VirtualNode& b) {
        return a.hash < b.hash;
    });
}

void ConsistentHash::removeNode(const string& nodeId) {
    nodes.erase(remove(nodes.begin(), nodes.end(), nodeId), nodes.end());

    ring.erase(remove_if(ring.begin(), ring.end(),
                         [&nodeId](const VirtualNode& v) { return v.nodeId == nodeId; }),
               ring.end());
}

string ConsistentHash::getNode(const string& key) const {
    if (ring.empty()) {
        return "";
    }

    uint32_t hash = HashFunctions::fnv1a(key);
    int index = findNodeIndex(hash);

    return ring[index].nodeId;
}

void ConsistentHash::printStats() const {
    cout << "  Hash Ring: " << nodes.size() << " nodes, "
         << ring.size() << " positions (vnodes=" << virtualNodesPerNode << ")\n";
}

#endif
