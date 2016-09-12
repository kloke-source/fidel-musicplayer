#ifndef BTREE
#define BTREE
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class btree {
public:
  struct BstNode {
    T data;
    int id;
    BstNode* left;
    BstNode* right;
  };
  btree();
  ~btree();
  BstNode* root_node;

  BstNode* new_node(T data);
  BstNode* new_node(T data, int id);
  BstNode* insert_backend(BstNode* root, T data);
  BstNode* insert_backend(BstNode* root, T data, int id);

  void clear();
  void clear_backend(BstNode* root);
  
  void insert(T data);
  void insert(T data, int id);

  BstNode* found_node;
  vector<T> iterative_search(string search_term);
  bool rec_search_backend(BstNode* root, string search_term);
  bool search_backend(BstNode* root, T search_term);
  int node_num;
  T search_result;
  vector<T> search_results;
  vector<T> ordered_list;
  vector<int> iterated_ids;
  vector<int> search_ids;
  T search(T search_term);
  bool check(T search_term);
  int get_search_id();
  size_t size();
  vector<int> get_search_ids();
  vector<int> get_iterated_ids();
  vector<T> rec_search(string search_term);
  void inorder_trav_backend(BstNode *node);
  vector<T> inorder();
private:
  int search_id;
  string to_lower(string input);
  bool rec_comp(string value, string compare);
};


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
typename btree<T>::BstNode* btree<T>::new_node(T data, int id) {
  btree<T>::BstNode* newNode = new btree<T>::BstNode();
  newNode->data = data;
  newNode->id = id;
  newNode->left = newNode->right = NULL;
  return newNode;
}

template <class T>
typename btree<T>::BstNode* btree<T>::insert_backend(btree<T>::BstNode* root,  T data) {
  if(root == NULL) { // empty tree
    root = btree<T>::new_node(data);
    node_num++;
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
typename btree<T>::BstNode* btree<T>::insert_backend(btree<T>::BstNode* root,  T data, int id) {
  if(root == NULL) { // empty tree
    root = btree<T>::new_node(data, id);
    node_num++;
  }
  // if data to be inserted is lesser, insert in left subtree<T>.
  else if(data <= root->data) {
    root->left = btree<T>::insert_backend(root->left,data, id);
  }
  // else, insert in right subtree<T>.
  else {
    root->right = btree<T>::insert_backend(root->right,data, id);
  }
  return root;
}

template <class T>
void btree<T>::insert(T data)
{
  root_node = btree<T>::insert_backend(root_node, data);
}

template <class T>
void btree<T>::insert(T data, int id)
{
  root_node = btree<T>::insert_backend(root_node, data, id);
}

template <class T>
void btree<T>::clear()
{
  btree<T>::clear_backend(root_node);
  root_node = NULL;
}

template <class T>
void btree<T>::clear_backend(BstNode* root)
{
  if(!root) return;
  if(root->left){
    std::cout << endl << "deleting left" << std::endl;
    btree<T>::clear_backend(root->left);
  }
  if(root->right){
    std::cout << endl << "deleting right" << std::endl;
    btree<T>::clear_backend(root->right);
  }
  delete root;
}

template <class T>
bool btree<T>::search_backend(btree<T>::BstNode* root, T search_term)
{
  if(root == NULL) {
    return false;
  }
  else if(root->data == search_term) {
    search_result = root->data;
    search_id = root->id;
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
  if (strcmp(btree<T>::to_lower(value).c_str(),btree<T>::to_lower(compare).c_str()) == 0)
    return true;
  else
    return false;
}

template <class T>
vector<T> btree<T>::iterative_search(string search_term)
{
  search_results.clear();
  if (ordered_list.size() == 0){
    btree<T>::inorder();
  }
  for (size_t iter=0; iter < ordered_list.size(); iter++){
    int found_pos = btree<T>::to_lower(ordered_list[iter]).find(btree<T>::to_lower(search_term));
    if (found_pos != -1){
      search_results.push_back(ordered_list[iter]);
      iterated_ids.push_back(iterated_ids[iter]);
    }
  }
  return search_results;
}

template <class T>
bool btree<T>::rec_search_backend(btree<T>::BstNode* root, string search_term) {
  if(root == NULL) {
    return false;
  }
  else if (btree<T>::rec_comp((root->data).substr(0, search_term.length()), search_term ) == true) {
    search_results.push_back(root->data);
    search_ids.push_back(root->id);
    found_node = root;
    while (btree<T>::rec_search_backend(found_node->right, search_term));
    while (btree<T>::rec_search_backend(found_node->left, search_term));
    return true;
  }
  else if (btree<T>::to_lower(search_term) <= btree<T>::to_lower(root->data)) {
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
  T obtained_results = search_result;
  search_results.clear();
  return search_result;
}

template <class T>
bool btree<T>::check(T search_term)
{
  bool check_value =  btree<T>::search_backend(root_node, search_term);
  if (check_value == false){
  }
  else {
  }
  return check_value;
}

template <class T>
size_t btree<T>::size()
{
  return node_num;
}

template <class T>
int btree<T>::get_search_id()
{
  return search_id;
}

template <class T>
vector<int> btree<T>::get_search_ids()
{
  vector<int> obtained_ids = search_ids;
  search_ids.clear();
  return obtained_ids;
}

template <class T>
vector<int> btree<T>::get_iterated_ids()
{
  vector<int> obtained_ids = iterated_ids;
  iterated_ids.clear();
  return obtained_ids;
}

template <class T>
vector<T> btree<T>::rec_search(string search_term)
{
  search_results.clear();
  btree<T>::rec_search_backend(root_node, search_term);
  vector<T> obtained_results = search_results;
  search_results.clear();
  return obtained_results;
}

template <class T>
void btree<T>::inorder_trav_backend(btree<T>::BstNode *node)
{
  if (node == NULL) return;
  btree<T>::inorder_trav_backend(node->left);
  ordered_list.push_back(node->data);
  iterated_ids.push_back(node->id);
  btree<T>::inorder_trav_backend(node->right);
}

template <class T>
vector<T> btree<T>::inorder()
{
  btree<T>::inorder_trav_backend(root_node);
  return ordered_list;
}

#endif
