#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_
#include <vector>
#include <utility>
#include "json.hpp"
typedef double Key;
typedef std::pair<int, int> Value;
typedef std::pair<Key, Value> KeyValuePair;
class PriorityQueue {
public:
PriorityQueue(std::size_t max_nodes);
void insert(Key k);
void insert(KeyValuePair kv);
KeyValuePair min();
KeyValuePair removeMin();
bool isEmpty() const;
size_t size() const;
nlohmann::json JSON() const;
private:
void heapifyUp(size_t i);
void heapifyDown(size_t i);
void removeNode(size_t i);
Key getKey(size_t i);
std::vector<KeyValuePair> nodes_;
size_t max_size_;
size_t size_;
const static size_t ROOT = 1;    //the root of the heap is at index 1
}; // class PriorityQueue
#endif // _PRI

//each heap node stores 
//(key, (player1, player2))

//root node at index 1 of array