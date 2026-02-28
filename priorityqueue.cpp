#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"
PriorityQueue::PriorityQueue(std::size_t max_size) :
nodes_(max_size + 1, KeyValuePair()),
max_size_(max_size), //maximum number of elements allowed
size_(0) {. //size of the heap
}
void PriorityQueue::insert(Key k) {
insert(std::make_pair(k, std::make_pair(0, 0)));
}

//inserts a key-value pair into the priority queue. The types
//key, value, and KeyvaluePair are defined in prioorityqueue.h using typedefs
void PriorityQueue::insert(KeyValuePair kv) {
// TODO: complete this function
    size_++;

    //place new node at the end
    node_[size_] = kv;

    //restore heap property
    heapifyUp(size_);
}

//returns the KeyVeluePair that has the minimum key in the heap
KeyValuePair PriorityQueue::min() {
// TODO: complete this function
    KeyValuePair minKeyNode = nodes_[ROOT];

    return minKeyNode;
}

//returns and removes the keyValuePair that has the minimum key in the heap
//so this is just the top node because the key value is 1
//the root is always at index 1
KeyValuePair PriorityQueue::removeMin() {
// TODO: complete this function
//the keyValuePair that has the minimum key is the root node
    KeyValuePair minKeyNode = nodes_[ROOT];

    //remove the node using removeNode function
    removeNode(ROOT);

    //return the node
    return minKeyNode;
}

//return true if and only if the heap is empty
bool PriorityQueue::isEmpty() const {
// TODO: complete this function
    return size_ == 0;
}

//returns the number of KeyValuePairs in the heap
size_t PriorityQueue::size() const {
// TODO: complete this function
    return size_;  //size tracks how many entries in nodes_ are currentl valid heap elemenets
}
nlohmann::json PriorityQueue::JSON() const {
nlohmann::json result;
for (size_t i = 1; i <= size_; i++) {
nlohmann::json node;
KeyValuePair kv = nodes_[i];
node["key"] = kv.first;
node["value"] = kv.second;
if (i != ROOT) {
node["parent"] = std::to_string(i / 2);
}
if (2 * i <= size_) {
node["leftChild"] = std::to_string(2 * i);
}
if (2 * i + 1 <= size_) {
node["rightChild"] = std::to_string(2 * i + 1);
}
result[std::to_string(i)] = node;
}
result["metadata"]["max_size"] = max_size_;
result["metadata"]["size"] = size_;
return result;
}

//percolates the ith node up the heap to ensure the heap property is preserved
void PriorityQueue::heapifyUp(size_t i) {
// TODO: complete this function

    //repeat until the node is at the root or heap property is satisfied
    //Root  = 1, everything(meaning all children nodes) after are > 1
    while(i > ROOT){
       //node 4 parent is at index 2, node 3index is at index 1, so fourth
        int parent_index = i/2;

        //if the node's key is smaller than the parents key swap the nodes
        if(nodes_[i].first < nodes_[parent_index].first){
            KeyValuePair temp = nodes_[parent_index];
            nodes_[parent_index] = nodes[i];
            nodes[i] = temp;

            i = parent_index; //move upward, update i
        }
        else{
            break;
        }
    }
}


void PriorityQueue::heapifyDown(size_t i) {
// TODO: complete this function
    //while left child exists, basically first check if there are children to begin wwith
    while(2 * i <= size_){
        //find smallest child
        //assume lefr child is smaller
        size_t smallest = (2 * i);

        //if right child exists and is smaller
        if((2 * i + 1) <= size_ && nodes_[2 * i + 1].first < nodes_[2 * i].first){
            //right child is smallest child
            smallest = (2 * i + 1);
        }


        //if smallest child < current
        if(nodes_[smallest].first < nodes_[i].first){
            //swap
            KeyValuePair temp = nodes_[i];
            //swapping the node with the smaller child node(heapify down)
            nodes_[i] = nodes_[smallest];

            nodes_[smallest] = temp;

            i = smallest;
        }
        else{
            break;
        }
    }
}

//removes the ith node from the heap.
void PriorityQueue::removeNode(size_t i) { //revisit logic 
// TODO: complete this function
    // Replace with last element
    nodes_[i] = nodes_[size_];

    size_--;

    // If we removed the last element, nothing to fix
    if (i > size_) return;

    // Decide direction to restore heap
    //this is a min heap condition
    if (i > ROOT && nodes_[i].first < nodes_[i / 2].first) {
        heapifyUp(i);
    } else {
        heapifyDown(i);
    }
}


//returns the key of the ith node in the heap
Key PriorityQueue::getKey(size_t i) {
// TODO: complete this function
    return nodes_[i].first;
}


//each heao is stored in
//std::vector<keyValuePair> node_;

//each element in the vector is 
//KeyVAluePair = std::pair<Key, Value>

//node_[i].first = accesses the key stored in the heap
//node["key"] = kv.first: stores the key in a JSON obhecy for output