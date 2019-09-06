#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

enum Color {
  RED, BLACK
};

struct Node {
  int data;
  bool color;
  Node *left, *right, *parent;

  // Constructor
  Node(int data) {
    this->data = data;
    left = right = parent = NULL;
  }
};

class RBTree {
private:  
  Node *root;
protected:
  void rotateLeft(Node *&, Node *&);
  void rotateRight(Node *&, Node *&);
  void fixViolation(Node *&, Node *&);
public:
  // Contructor
  RBTree() { root = NULL; }
  void insert(const int& n);
  void inorder();
  void levelOrder();
};

// A recusive function to do level order traversal
void inorderHelper(Node *root) {
  if(root == NULL) return;
  
  inorderHelper(root->left);
  cout << root->data << " ";
  inorderHelper(root->right);
}

// A utility function to insert a new node in BST 
Node* BSTInsert(Node* root, Node *pt) {
  // if the tree is empty, return a new node
  if(root == NULL) return pt;
  
  // otherwise, recur down the tree
  if(pt->data < root->data) {
    root->left = BSTInsert(root->left, pt);
    root->left->parent = root;
  } else if(pt->data > root->data) {
    root->right = BSTInsert(root->right, pt);
    root->right->parent = root;
  }
  
  return root;
}

// Utility function to do level order traversal
void levelOrderHelper(Node *root) {
  if(root == NULL) return;

  queue<Node *> q;
  q.push(root);

  while(!q.empty()) {
    Node *temp = q.front();
    cout << temp->data << " ";
    q.pop();

    if(temp->left != NULL) {
      q.push(temp->left);
    } 
    if(temp->right != NULL) {
      q.push(temp->right);
    }
  }
}

void RBTree::rotateLeft(Node *&root, Node *&pt) {
  Node *pt_right = pt->right;
  
  pt->right = pt_right->left;

  if(pt->right != NULL) {
    pt->right->parent = pt;
  }

  pt_right->parent = pt->parent;

  if(pt->right == NULL) {
    root = pt_right;
  } else if(pt == pt->parent->left) {
    pt->parent->left = pt_right;
  } else {
    pt->parent->right = pt_right;
  }

  pt_right->left = pt;
  pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt) {
  Node *pt_left = pt->left;

  pt->left = pt_left->right;
  if(pt->left != NULL) {
    pt->left->parent = pt;
  }

  pt_left->parent = pt->parent;
  if(pt->parent == NULL) {
    root = pt_left;
  } else if(pt == pt->parent->left) {
    pt->parent->left = pt_left;
  } else {
    pt->parent->right = pt_left;
  }

  pt_left->right = pt;
  pt->parent = pt_left;
}

// this function fixes violations caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt) {
  Node *parent_pt = NULL;
  Node *grand_parent_pt = NULL;

  while((pt != root) && (pt->color != BLACK) &&
        (pt->parent->color == RED)) {
    parent_pt = pt->parent;
    grand_parent_pt = pt->parent->parent;

    // case A
    // parent of pt is left child of grand-parent of pt
    if(parent_pt == grand_parent_pt->left) {
      Node *uncle_pt = grand_parent_pt->right;

      // case 1
      // the uncle of pt is also red
      // only recoloring required
      if(uncle_pt != NULL && uncle_pt->color == RED) {
        grand_parent_pt->color = RED;
        parent_pt->color = BLACK;
        uncle_pt->color = BLACK;
        pt = grand_parent_pt;
      } else {
        // case 2
        // pt is right child of its parent
        // left-rotation required
        if(pt == parent_pt->right) {
          rotateLeft(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        } 

        // case 3
        // pt is left child of its parent
        // right-rotation required
        rotateRight(root, grand_parent_pt);
        swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    } else {
      // case B
      // parent of pt is right child of grand parent of pt
      Node *uncle_pt = grand_parent_pt->left;

      // case 1
      // the uncle of pt is also red
      // only recoloring required
      if(uncle_pt != NULL && uncle_pt->color == RED) {
        grand_parent_pt->color = RED;
        parent_pt->color = BLACK;
        uncle_pt->color = BLACK;
        pt = grand_parent_pt;
      } else {
        // case 2
        // pt is left child of its parent
        // right rotation required
        if(pt == parent_pt->left) {
          rotateRight(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }

        // case 3
        // pt is right child of its parent
        // left rotation required
        rotateLeft(root, grand_parent_pt);
        swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    }
  }

  root->color = BLACK;
}

void RBTree::insert(const int& data) {
  Node *pt = new Node(data);

  // Do a normal BST insert
  root = BSTInsert(root, pt);

  // fix Red Black Tree violations
  fixViolation(root, pt);
}

// Functino to do inorder and level order traversal
void RBTree::inorder() {
  inorderHelper(root);
}

void RBTree::levelOrder() {
  levelOrderHelper(root);
}

int main(void) {
  RBTree tree;

  tree.insert(7);
  tree.insert(6);
  tree.insert(5);
  tree.insert(4);
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);

  cout << "Inorder tranversal of created tree" << endl;
  tree.inorder();
  cout << endl;


  cout << "Level order traversal of created tree" << endl;
  tree.levelOrder();
  cout << endl;

  return 0;
}


