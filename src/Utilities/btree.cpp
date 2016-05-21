#include <iostream>
#include "btree.h"
#include <vector>
using namespace std;
//Definition of Node for Binary search tree

template <class T>
btree<T>::btree()
{
  root_node = NULL;
}

template <class T>
btree<T>::~btree(){}

// Function to create a new Node in heap
template <class T>
typename btree<T>::BstNode* btree<T>::new_node(T data) {
  btree<T>::BstNode* newNode = new btree<T>::BstNode();
  newNode->data = data;
  newNode->left = newNode->right = NULL;
  return newNode;
}

template <class T>
typename btree<T>::BstNode* btree<T>::insert_backend(btree<T>::BstNode* root,  T data) {
  if(root == NULL) { // empty tree
    cout << "Insert : " << data << endl;
    root = btree<T>::new_node(data);
  }
  // if data to be inserted is lesser, insert in left subtree<T>.
  else if(data <= root->data) {
    root->left = btree<T>::insert_backend(root->left,data);
  }
  // else, insert in right subtree<T>.
  else {
    root->right = btree<T>::insert_backend(root->right,data);
  }
  return root;
}

template <class T>
void btree<T>::insert(T data)
{
  root_node = btree<T>::insert_backend(root_node, data);
}

template <class T>
bool btree<T>::search_backend(btree<T>::BstNode* root, T search_term)
{
  if(root == NULL) {
    return false;
  }
  else if(root->data == search_term) {
    cout << "Found : " << root->data << endl;
    search_result = root->data;
    return true;
  }
  else if(search_term <= root->data) {
    return btree<T>::search_backend(root->left, search_term);
  }
  else {
    return btree<T>::search_backend(root->right, search_term);
  }
}

template <class T>
string btree<T>::to_lower(string input)
{
  for (size_t iter=0; iter < input.length(); iter++){
    input[iter] = tolower(input[iter]);
  }
  return input;
}

template <class T>
bool btree<T>::rec_comp(string value, string compare)
{
  if (btree<T>::to_lower(value) == btree<T>::to_lower(compare)){
    return true;
  }
  else {
    return false;
  }
}

template <class T>
bool btree<T>::rec_search_backend(btree<T>::BstNode* root, string search_term) {
  if(root == NULL) {
    return false;
  }
  else if(btree<T>::rec_comp((root->data).substr(0, search_term.length()), search_term ) == true) {
    cout << "Comparison : " << (root->data).substr(0, search_term.length()) << endl;
    cout << "Found : " << root->data << endl;
    search_results.push_back(root->data);
    found_node = root;
    while (btree<T>::rec_search_backend(found_node->right, search_term));
    while (btree<T>::rec_search_backend(found_node->left, search_term));
    return true;
  }
  else if(search_term <= root->data) {
    return btree<T>::rec_search_backend(root->left,search_term);
  }
  else {
    return btree<T>::rec_search_backend(root->right,search_term);
  }
}

template <class T>
T btree<T>::search(T search_term)
{
  btree<T>::search_backend(root_node, search_term);
  return search_result;
}

template <class T>
vector<T> btree<T>::rec_search(string search_term)
{
  btree<T>::rec_search_backend(root_node, search_term);
  return search_results;
}

template <class T>
void btree<T>::inorder_trav_backend(btree<T>::BstNode *node)
{
  if (node == NULL) return;
  btree<T>::inorder_trav_backend(node->left);
  cout << "inorder_traversal: " << node->data << endl;
  btree<T>::inorder_trav_backend(node->right);
}

template <class T>
void btree<T>::inorder()
{
  btree<T>::inorder_trav_backend(root_node);
}
