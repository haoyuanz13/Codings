#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

// LRU: Least Recently Used
// the basic idea is to design a new structure to store key and value


/*
  The structure Node stores the key and value of each created structure.
  Also contains the relationship between its priori and behind one.
 */
struct Node
{
  int key;
  int value;

  Node* pre;
  Node* next;

  Node(int k, int v) {
    key = k;
    value = v;
  }
};


// create a linked list node
// put the most recent used node at the head of list
// put the least recent used node at the tail of list
class LRUCache {
public:
  unordered_map<int, Node*> hash;
  int storage;
  int count;

  Node* dummyHead;
  Node* dummyTail;

  LRUCache(int capacity) {
    storage = capacity;
    count = 0;

    // create a dummy linked list for initialization
    dummyHead = new Node(0, 0);
    dummyTail = new Node(0, 0);

    dummyHead->next = dummyTail;
    dummyHead->pre = nullptr;

    dummyTail->pre = dummyHead;
    dummyTail->next = nullptr;

  }

  // get the value of key if key exists in the memory, otherwise, return -1
  int get(int key) {
    if (hash.count(key) <= 0)
      return -1;

    Node* target = hash[key];
    int res = target->value;

    // update linked list
    remove(target);
    putToHead(target);
    return res;      
  }

  // put a new pair or update the one already exits
  // if the size exceeds the capacity, remove the one least recently used
  void put(int key, int value) {
    // two cases: update already existed one or insert a new one
    if (hash.count(key) > 0) {
      Node* target = hash[key];
      target->value = value;
      remove(target);
      putToHead(target);
    } 

    // create a new node and insert into the linked list
    else {
      Node* newone = new Node(key, value);
      hash[key] = newone;

      if (count < storage) {
        putToHead(newone);
        count ++;
      } else {
        // remove the tail one
        Node* LRU = dummyTail->pre;
        hash.erase(LRU->key);
        remove(LRU);
        putToHead(newone);
      }
    }
    
    return;
  }

  // remove the target node in the linked list
  void remove(Node* n) {
    n->pre->next = n->next;
    n->next->pre = n->pre;
    return;
  }

  // put the target node to the head of linked list
  void putToHead(Node* n) {
    n->next = dummyHead->next;
    dummyHead->next->pre = n;
    n->pre = dummyHead;
    dummyHead->next = n;
    return;
  }

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */