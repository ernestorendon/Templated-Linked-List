//
// Created by Ernesto Rendon on 2/11/23.
//

#ifndef PROJECT_1_LINKEDLIST_H
#define PROJECT_1_LINKEDLIST_H

#include <iostream>
#include <vector>
using namespace std;


template<typename T>
class LinkedList{

public:

    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    /*=== Behaviors ===*/
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    /*=== Accessors ===*/
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    Node* Find(const T& value) const;
    Node* GetNode(unsigned int index) const;
    Node* Head();
    Node* Tail();

    /*=== Insertion ===*/
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& value);
    void InsertBefore(Node* node, const T& value);
    void InsertAt(const T& data, unsigned int index);

    /*=== Removal ===*/
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& value);
    bool RemoveAt(unsigned int index);
    void Clear();

    /*=== Operators ===*/
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    T& operator[](unsigned int index) const;
    bool operator==(const LinkedList<T>& rhs) const;

    /*=== Construction/Destruction ===*/
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T>& rhs_list);


private:

    Node* _list_head;
    Node* _list_tail;
    unsigned int nodeCount;

    };

// This function takes in a pointer to a Node—a starting node.
// From that node, recursively visit each node that follows, in forward order, and print their values.
template<typename T>
void LinkedList<T>::PrintForwardRecursive(const LinkedList::Node *node) const {
    if (node->next != nullptr) {
      cout << node->data << endl;
      node = node->next;
      PrintForwardRecursive(node);
    }

    else {
      cout << node->data << endl;
    }
}

// Same deal as PrintForwardRecursive, but in reverse.
template<typename T>
void LinkedList<T>::PrintReverseRecursive(const LinkedList::Node *node) const {
    if (node->prev != nullptr) {
        cout << node->data << endl;
        node = node->prev;
        PrintReverseRecursive(node);
    }
    else {
        cout << node->data << endl;
    }
}

// Deletes all Nodes. Don’t forget the node count—how many nodes do you have after you deleted all of them?
template<typename T>
void LinkedList<T>::Clear() {

    Node* currentNode = _list_head;

    if (nodeCount > 1) {
        while (currentNode->next!=nullptr){
            _list_head = _list_head->next;
            delete currentNode;
            currentNode = _list_head;
        }
        delete currentNode;
    }

    _list_head = nullptr;
    _list_tail = nullptr;
    nodeCount = 0;
}

// // Deletes the index-th Node from the list, returning whether or not the operation was successful
template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {

    // if list has at least one elem...
    if (nodeCount != 0) {

        // if requested removal is out-of-range, return false
        if (index > nodeCount-1){
            return false;
        }

        // retrieve requested elem...
        Node* currentNode = GetNode(index);

        // if list has more than 1 elem...
        if (nodeCount > 1){

            // if requesting removal of head...
            if (currentNode == _list_head){
                _list_head = currentNode->next;
                _list_head->prev = nullptr;
            }

            // if requesting removal of tail...
            else if (currentNode == _list_tail){
                _list_tail = currentNode->prev;
                _list_tail->next = nullptr;
            }

            // requesting removal of elem that is not head or tail
            else {
                Node* prevNode = currentNode->prev;
                Node* nextNode = currentNode->next;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
            }

            // regardless of what node it is, delete it, remove one from count, and return true
            delete currentNode;
            nodeCount--;
            return true;
        }

        // if list has exactly 1 elem...
        else {
            delete currentNode;
            nodeCount--;
            return true;
        }
    }

    // if list has no elems...
    return false;
}

// Remove ALL Nodes containing values matching that of the passed-in parameter.
// Returns how many instances were removed.
template<typename T>
unsigned int LinkedList<T>::Remove(const T &value) {
    unsigned int removalCount = 0;
    for (unsigned int i = 0; i < nodeCount; i++) {
        if (GetNode(i)->data == value) {
            RemoveAt(i);
            removalCount++;
        }
    }
    return removalCount;
}

// Deletes the first Node in the list. Returns whether or not the Node was removed.
template<typename T>
bool LinkedList<T>::RemoveHead() {
    if (nodeCount != 0) {
        RemoveAt(0);
        return true;
    }
    else {
        return false;
    }
}

// Deletes the last Node, returning whether or not the operation was successful.
template<typename T>
bool LinkedList<T>::RemoveTail() {
    if (nodeCount != 0){
        RemoveAt(nodeCount-1);
        return true;
    }
    else {
        return false;
    }
}

// Inserts a new Node to store the first parameter, at the index-th location.
// Throws an out_of_range exception if given an invalid index.
template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {

    if (index == 0) {
        AddHead(data);
    }

    else if (index == nodeCount) {
        AddTail(data);
    }

    else {
        InsertBefore(GetNode(index), data);
    }
}

// Given a pointer to a node, create a new node to store the passed in value, before the indicated node.
template<typename T>
void LinkedList<T>::InsertBefore(LinkedList::Node *node, const T &value) {

    // given node
    Node* current_node = node;
    // given node's prev node
    Node* prev_node = current_node->prev;

    // create new node;
    Node* added_node = new Node;
    added_node->data = value;

    // new node's prev node is given node's prev
    added_node->prev = prev_node;
    // new node's next node is given node
    added_node->next = current_node;

    // double-back to change nodes ahead and behind
    current_node->prev = added_node;
    prev_node->next = added_node;

    nodeCount++;
}

// Given a pointer to a node, create a new node to store the passed in value, after the indicated node.
template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node *node, const T &value) {

    // given node
    Node* current_node = node;
    // given node's next node
    Node* next_node = current_node->next;

    // create new node;
    Node* added_node = new Node;
    added_node->data = value;

    // new node's prev node is given node
    added_node->prev = current_node;
    // new node's next node is given node's next
    added_node->next = next_node;

    // double-back to change nodes ahead and behind
    current_node->next=added_node;
    next_node->prev = added_node;

    nodeCount++;

}

// Empty constructor
template<typename T>
LinkedList<T>::LinkedList() {
    _list_head = nullptr;
    _list_tail = nullptr;
    nodeCount = 0;
}

// Copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs_list) {

    nodeCount = 0;

    Node* current_rhs_node = rhs_list._list_head;

    while (current_rhs_node->next != nullptr){
        AddTail(current_rhs_node->data);
        current_rhs_node = current_rhs_node->next;
    }

    AddTail(current_rhs_node->data);

}

// Copy assignment operator. After listA = listB, listA == listB is true.
template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs_list) {

    unsigned int copy_count = 0;

    Node* current_rhs_node = rhs_list._list_head;
    Node* current_lhs_node = _list_head;

    while (current_rhs_node->next != nullptr){
        current_lhs_node->data = current_rhs_node->data;
        current_rhs_node = current_rhs_node->next;
        current_lhs_node = current_lhs_node->next;
        copy_count++;
    }

    while (copy_count < rhs_list.nodeCount) {
        AddTail(current_rhs_node->data);
        current_rhs_node = current_rhs_node->next;
        copy_count++;
    }

    return *this;

}

// Given an index, return a pointer to the node at that index.
// Throws an exception of type out_of_range if the index is out of range. Const and non-const versions.
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const{

    if (index > (nodeCount-1)) {
        throw std::out_of_range ("Index is greater than the number of nodes in the list.");
    }

    else {
        Node* currentNode = _list_head;
        for (unsigned int i=0; i < index; i++){
            currentNode = currentNode->next;
        }

        return currentNode;
    }
}

// Find all nodes which match the passed in parameter value, and store a pointer to that node in the passed-in vector.
template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {

    Node* currentNode = _list_head;

    // loop thru all nodes; if a match hits, add the pointer to the vector of Node pointers
    while (currentNode->next != nullptr){
        if (currentNode->data == value){
            outData.push_back(currentNode);
        }
        currentNode = currentNode->next;
    }

    // checking the last node
    if (currentNode->data == value){
        outData.push_back(currentNode);
    }
}

// Find the first node with a data value matching the passed in parameter, returning a pointer to that node.
// Returns nullptr if no matching node found.
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &value) const {

    Node* currentNode = _list_head;

    // loop thru all nodes; if a match hits, return the pointer to first instance of that match
    while (currentNode->next != nullptr){
        if (currentNode->data == value){
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    // checking the last node
    if (currentNode->data == value){
        return currentNode;
    }
    else {
        return nullptr;
    }
}

// Access last elem in list
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
    return _list_tail;
}

// Access first elem in list
template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
    return _list_head;
}

// Overloaded subscript operator. Takes an index, and returns data from the index- th node.
// Throws an out_of_range exception for an invalid index.
template<typename T>
T &LinkedList<T>::operator[](unsigned int index) const {
    return GetNode(index)->data;
}

// Overloaded equality operator.
template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {

    // start at top of both lists
    Node* currentNode = _list_head;
    Node* current_rhs_Node = rhs._list_head;

    // loop thru all nodes
    while (currentNode->next != nullptr){
        // keep moving as long as data matches
        if (currentNode->data == current_rhs_Node->data){
            currentNode = currentNode->next;
            current_rhs_Node = current_rhs_Node->next;
        }

            // when data doesn't match before tail, return false
        else {
            return false;
        }
    }

    // checking the last node; if by here all are true, lists are equal
    if (currentNode->data == current_rhs_Node->data){
        return true;
    }

    // if tail differs, not equal
    return false;
}

// Create a new Node at the front of the list to store the passed in parameter.
template<typename T>
void LinkedList<T>::AddHead(const T &data) {

    // if adding a head to a nonempty list...
    if (nodeCount != 0) {
        Node* old_head = _list_head;
        _list_head = new Node;
        _list_head->data = data;
        _list_head->next = old_head;
        _list_head->prev = nullptr;
        old_head->prev = _list_head;
    }

    // if adding a head to an empty list...
    else {
        _list_head = new Node;
        // make head the tail since there's only one node...
        _list_tail = _list_head;
        _list_head ->data = data;
        _list_head->next = nullptr;
        _list_head->prev = nullptr;
    }

    nodeCount++;
}

// Given an array of values, insert a node for each of those at the beginning of the list,
// maintaining the original order.
template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {

    for (int i = (count-1); i >= 0; i--){
        AddHead(data[i]);
    }
}

// Create a new Node at the end of the list to store the passed in parameter.
template<typename T>
void LinkedList<T>::AddTail(const T &data) {

    // if adding a tail to a nonempty list...
    if (nodeCount != 0) {

        // iterate thru list to get to end
        Node* currentNode = _list_head;
        while (currentNode->next != nullptr){
            currentNode = currentNode->next;
        }
        _list_tail = new Node;
        _list_tail->data = data;
        _list_tail->next = nullptr;
        _list_tail->prev = currentNode;

        currentNode->next = _list_tail;

    }

    // if adding a tail to an empty list...
    else {
        _list_tail = new Node;

        // make head the tail since there's only one node...
        _list_head = _list_tail;
        _list_tail->data = data;
        _list_tail->next = nullptr;
        _list_tail->prev = nullptr;
    }

    nodeCount++;
}

// Same as AddNodesHead, except adding to the end of the list.
template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++){
        AddTail(data[i]);
    }
}

// How many things are stored in this list?
template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCount;
}

// Iterator through all of the nodes and print out their values, one a time.
template<typename T>
void LinkedList<T>::PrintForward() const {

    Node* currentNode = _list_head;

    while (currentNode->next != nullptr){
        cout << currentNode->data << endl;
        currentNode = currentNode->next;
    }
    cout << currentNode->data << endl;

}

// Exactly the same as PrintForward, except completely the opposite.
template<typename T>
void LinkedList<T>::PrintReverse() const {

    Node* currentNode = _list_tail;

    while (currentNode->prev != nullptr){
        cout << currentNode->data << endl;
        currentNode = currentNode->prev;
    }

    cout << currentNode->data << endl;
}

// Destructor
template<typename T>
LinkedList<T>::~LinkedList() {

    Node* currentNode = _list_head;

    if (nodeCount > 1) {
        while (currentNode->next!=nullptr){
            _list_head = _list_head->next;
            delete currentNode;
            currentNode = _list_head;
        }
        delete currentNode;
    }
}

#endif //PROJECT_1_LINKEDLIST_H