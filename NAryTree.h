//
//  NaryTree.h
//  A class template of N-ary Tree.
//  N-ary tree is a rooted tree in which each node has no more than n children
//  Write by Zhenghui Li

#ifndef NAryTree_h
#define NAryTree_h

#include <string>
#include <unordered_set>
#include "Queue.h"

const int MAX_CHILDREN = 96;
// Printable ASCII code is 32~127
const bool DE_BUG = false;

using std::string;
using std::unordered_set;


//**************************************************
// The NAryTreeNode class creates a type used to   *
// store a node of the N-ary Tree.                 *
//**************************************************
template <typename T, typename HashT>
class NAryTreeNode {
public:
  NAryTreeNode* children[MAX_CHILDREN] = {nullptr};
    // The array stores all of the child nodes of this tree node
  bool isEndOfWord; // A flag shows whether the node is the end of a word
  unordered_set<T, HashT>* item_set;
    // A pointer to the result data collection.
    // If the node is not end-of-word, it remains nullptr.

  NAryTreeNode() {
    isEndOfWord = false;
    item_set = nullptr;
  }

  ~NAryTreeNode() {
    if (item_set != nullptr) {
      delete item_set;
    }
  }
    
};


//*********************************************
// NAryTree class                             *
//*********************************************
template <typename T, typename HashT>
class NAryTree {
public:
  NAryTreeNode<T, HashT> *root;

  NAryTree() { root = nullptr; }
  ~NAryTree();
  void insert(std::string str, T &item);
  NAryTreeNode<T, HashT>* search(std::string str);
  unordered_set<T, HashT> findResultSet(NAryTreeNode<T, HashT> *node);

private:
  void findItemsAfterNode(NAryTreeNode<T, HashT> *node, unordered_set<T, HashT> &result);
};


//******************************************************
// insertString function insert every character of the
// string as a node in N-ary Tree, set the last
// node's isEndOfWord to true.
// Then insert the item into an unordered set that
// the last node points to.
//******************************************************
template <typename T, typename HashT>
void NAryTree<T, HashT>::insert(std::string str, T &item) {
  // If the tree is empty, create a root
  if (root == nullptr) {
    root = new NAryTreeNode<T, HashT>();
  }
  NAryTreeNode<T, HashT> *cur_node = root;
  for (int i = 0; i < str.size(); i++) {
    // For each char in str, its index is its decimal ASCII code minus 32
    // We skip the first 32 chars in ASCII table because they are unprintable
    size_t pos = str[i] - 32;
    // Create a new node in children array if its position is not null
    if (cur_node->children[pos] == nullptr) {
      cur_node->children[pos] = new NAryTreeNode<T, HashT>();
      cur_node = cur_node->children[pos];
    } else {
      cur_node = cur_node->children[pos];
    }
    if (DE_BUG)
      std::cout << "Children: " << static_cast<char>(pos + 32) << std::endl;
  }
    
  // Set the isEndOfWord flag to true in the last node of the word
  cur_node->isEndOfWord = true;
  // Insert the item into an unordered set in the last node
  if (cur_node->item_set == nullptr) {
    cur_node->item_set = new unordered_set<T, HashT>;
  }
  cur_node->item_set->insert(item);
}


//******************************************************
// search function search for a node that exactly
// matches the given string.
// Return the node, otherwise return nullptr.
//******************************************************
template <typename T, typename HashT>
NAryTreeNode<T, HashT> *NAryTree<T, HashT>::search(std::string str) {
  if (root == nullptr) {
    if (DE_BUG)
      std::cout << "The data tree is empty!" << std::endl;
    return nullptr;
  }

  NAryTreeNode<T, HashT> *cur_node = root;
  for (int i = 0; i < str.size(); i++) {
    size_t pos = str[i] - 32;
    if (cur_node->children[pos] == nullptr) {
      if (DE_BUG)
        std::cout << "No results found!" << std::endl;
      return nullptr;
    } else {
      cur_node = cur_node->children[pos];
    }
  }
  return cur_node;
}


//******************************************************
// findItemsAfterNode function recursively find a union
// item set after a given node.
// If a node is the end of a word, add that node's item set
// into a result set.
// Then recursively call itself to add item sets of the
// node's children.
//******************************************************
template <typename T, typename HashT>
void NAryTree<T, HashT>::findItemsAfterNode(NAryTreeNode<T, HashT> *node, unordered_set<T, HashT> &result)
{
  if (node == nullptr){
        return;
   }
  if (node->isEndOfWord) {
      unordered_set<T, HashT>* set = node->item_set;
      for (auto it = set->begin(); it != set->end(); it++){
          result.insert(*it);
      }
  }
  for (int i = 0; i < MAX_CHILDREN; i++) {
    if (node->children[i] != nullptr) {
      findItemsAfterNode(node->children[i], result);
    }
  }
  return;
}


//******************************************************
// findResultSet function call findItemsAfterNode, and
// return a result set.
//******************************************************
template <typename T, typename HashT>
unordered_set<T, HashT>
NAryTree<T, HashT>::findResultSet(NAryTreeNode<T, HashT> *node) {
  unordered_set<T, HashT> result;
  findItemsAfterNode(node, result);
  return result;
}


//******************************************************
// Destructor
//******************************************************
template <typename T, typename HashT> NAryTree<T, HashT>::~NAryTree() {
  if (root != nullptr) {
    Queue<NAryTreeNode<T, HashT>*> queue;
    queue.push(root);
    while (!queue.isEmpty()) {
      NAryTreeNode<T, HashT>* cur_node = queue.pop();
      for (int i = 0; i < MAX_CHILDREN; i++) {
        if (cur_node->children[i] != nullptr) {
          queue.push(cur_node->children[i]);
        }
      }
      delete cur_node;
    }
  }
}

#endif /* NAryTree_h */
