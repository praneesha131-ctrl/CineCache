#pragma once
#ifndef DOUBLY_LINKED_LIST_CPP
#define DOUBLY_LINKED_LIST_CPP

#include "common/headers.h"
using namespace std;

// One node in the doubly linked list.
template <typename T>
struct DLLNode {
    string key;
    T data;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(const string& k, const T& d)
        : key(k), data(d), prev(nullptr), next(nullptr) {}
};

// A doubly linked list with dummy head and tail nodes.
template <typename T>
class DoublyLinkedList {
private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    int size;

public:
    DoublyLinkedList() : size(0) {
        head = new DLLNode<T>("HEAD", T());
        tail = new DLLNode<T>("TAIL", T());
        head->next = tail;
        tail->prev = head;
    }

    ~DoublyLinkedList() {
        DLLNode<T>* current = head;

        while (current != nullptr) {
            DLLNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    DLLNode<T>* insertFront(const string& key, const T& data) {
        DLLNode<T>* newNode = new DLLNode<T>(key, data);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        size++;
        return newNode;
    }

    void removeNode(DLLNode<T>* node) {
        if (node == nullptr || node == head || node == tail) {
            return;
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
    }

    void moveToFront(DLLNode<T>* node) {
        if (node == nullptr || node == head || node == tail) {
            return;
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    DLLNode<T>* getLRU() const {
        return tail->prev;
    }

    // Get all items in order (front to back = newest to oldest)
    vector<T> getAllItems() const {
        vector<T> items;
        DLLNode<T>* current = head->next;
        while (current != tail && current != nullptr) {
            items.push_back(current->data);
            current = current->next;
        }
        return items;
    }

    int getSize() const { return size; }
};

#endif
