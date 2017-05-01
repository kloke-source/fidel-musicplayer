#ifndef DIR_DATA_STRUCT_HH
#define DIR_DATA_STRUCT_HH
#include <iostream>
#include <mutex>
#include <vector>

class DirDataStruct {
public:
  // Forward Declarations //
  class RootNode;
  class Node;
  class Level;
  class Children;
  // End of Forward Declarations //

  Node *root_node;
  Node *get_root_node() { return root_node; }

private:
  bool initialized = false;

  void delete_all_nodes() { delete_all_nodes(this->root_node); }

  void delete_all_nodes(Node *node) {
    // Base condition that terminates the recursive function call
    if (node == NULL)
      return;

    Children *node_children = node->get_children();

    // Recursively traverse all nodes in the tree by travelling to the node's
    // children. One node may have multiple children, hence the for loop to
    // iteratively go through each of the node's children
    for (size_t iter = 0; iter < node_children->size(); iter++)
      delete_all_nodes(node_children->get_child(iter));

    // The node at this point has no children, and so can be deleted safely
    // without affecting traversal
    delete_node(node);
  }

public:
  DirDataStruct() {
    this->root_node = new Node();
    root_node->set_root(true);
  }

  ~DirDataStruct() { this->delete_all_nodes(); }

  void traverse_all_nodes() { traverse_all_nodes(this->root_node); }
  void traverse_all_nodes(Node *node) {
    if (node == NULL)
      return;

    std::string spacing(node->get_depth(), '-');
    spacing += ">";
    std::cout << spacing << "Dir : " << node->get_data() << std::endl;

    Children *node_children = node->get_children();
    for (size_t iter = 0; iter < node_children->size(); iter++) {
      traverse_all_nodes(node_children->get_child(iter));
    }
  }

  void delete_node(Node *node_to_del) {
    if (node_to_del != NULL)
      delete node_to_del;
  }

public:
  // Sub classes //
  class Level : public std::vector<std::vector<Node *>> {
  public:
    Level() {}
    ~Level() {}
  };

  class Children {
  public:
    Children() {}
    ~Children() {}

    void add(Node *child) { this->children.push_back(child); }
    size_t size() { return this->children.size(); }
    bool empty() { return this->children.empty(); }

    Node *get_child(int pos) { return this->children[pos]; }

  protected:
    std::vector<Node *> children;
  };

  class Node {
  public:
    Node() { children = new Children(); }
    Node(std::string data, Node *parent, Children *children) {
      this->data = data;
      this->children = children;
      this->parent = parent;
    }

    Node(std::string data, Node *parent) {
      this->data = data;
      this->parent = parent;
      this->children = new Children();
    }
    ~Node() { delete this->children; }

    Node *get_parent() { return this->parent; }
    Children *get_children() { return this->children; }
    std::string get_data() { return this->data; }
    std::string get_path() { return this->path; }
    int get_depth() { return this->depth; }

    bool is_root() { return root; }
    bool is_dir() { return dir; }
    bool has_children() { return !this->children->empty(); }

    void set_root(bool is_root) { this->root = is_root; }
    void set_is_dir(bool is_dir) { this->dir = is_dir; }
    void set_path(std::string path) { this->path = path; }
    void set_data(std::string data) { this->data = data; }
    void set_parent(Node *parent) { this->parent = parent; };
    void set_children(Children *children) {
      this->children = children;
      for (size_t iter = 0; iter < children->size(); iter++) {
        children->get_child(iter)->set_parent(this);
        children->get_child(iter)->set_depth();
        children->get_child(iter)->set_path();
      }
    };

    void add_child(Node *child_node) {
      this->children->add(child_node);
      child_node->set_parent(this);
      child_node->set_depth();
      child_node->set_path();
    }

    Node *add_child(std::string data, bool dir = false) {
      // Creates a child_node with data parameter, and the parent being the
      // current Node
      Node *child_node = new Node(data, this);
      // Sets depth (how many pointers away it is from the root node)
      child_node->set_depth();
      child_node->set_path();
      child_node->set_is_dir(dir);
      // Add newly created child node to current node's children
      this->children->add(child_node);
      return child_node;
    }

  private:
    Node *parent;
    std::mutex node_mutex;

    void set_depth() {
      std::unique_lock<std::mutex> lock(this->node_mutex);
      this->depth = this->get_parent()->get_depth() + 1;
      lock.unlock();
    }

    void set_path() {
      std::unique_lock<std::mutex> lock(this->node_mutex);
      this->path = this->get_parent()->get_path() + "/" + this->get_data();
      lock.unlock();
    }

  protected:
    bool root = false;
    bool dir = true;
    int depth = 1;

    std::string data;
    std::string path;

    Children *children;
  };
  // End of Sub Classes //
};

#endif
