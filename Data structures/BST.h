#include <bits/stdc++.h>

using Key = int;
using E = int;

struct Node {
  Key key;
  E element;
  Node* left;
  Node* right;
};

struct BST {
  BSTNode* root;
  int nodeCount;
};

Node* createNode(Key k, E e) {
  Node* newNode = new Node;
  newNode->key = k;
  newNode->element = e;
  newNode->left = newNode->right = nullptr;
  return newNode;
}

BST createBST() {
  BST bst;
  bst.root = nullptr;
  bst.nodeCount = 0;
  return bst;
}

std::optional<E> findHelp(Node* rt, Key k) {
  // Using optional 'cause not everything in C++ is a pointer.
  if (rt == nullptr) {
    return std::nullopt;
  }

  if (k < rt->key) {
    return findHelp(rt->left, k);
  } else if (k == rt->key) {
    return rt->element;
  } else {
    return findHelp(rt->right, k);
  }
}

std::optional<E> find(BST& bst, Key k) {
  return findHelp(bst.root, k);
}

Node* insertHelp(Node* rt, Key k, E e) {
  if (rt == nullptr) {
    return createNode(k, e);
  }

  if (k < rt->key) {
    rt->left = insertHelp(rt->left, k, e);
  } else {
    // Considering that repeated keys go on the right subtree.
    rt->right = insertHelp(rt->right, k, e);
  }

  return rt;
}

void insert(BST& bst, Key k, E e) {
  bst.root = insertHelp(bst.root, k, e);
  ++bst.nodeCount;
}

Node* getMin(Node* rt) {
  if (rt->left == nullptr) {
    return rt->right;
  }

  return getMin(rt->left);
}

Node* deleteMin(Node* rt) {
  if (rt->left == nullptr) {
    Node* aux = rt->right;
    delete rt;
    return aux;
  }

  rt->left = deleteMin(rt->left);
  return rt;
}

Node* removeHelp(Node* rt, Key k) {
  if (rt == nullptr) {
    return nullptr;
  }

  if (k < rt->key) {
    rt->left = removeHelp(rt->left, k, e);
  } else if (k > rt->key) {
    rt->right = removeHelp(rt->right, k, e);
  } else {
    if (rt->left == nullptr) {
      return rt->right;
    } else if (rt->right == nullptr) {
      return rt->left;
    } else {
      Node* aux = getMin(rt->right);
      rt->element = aux->element;
      rt->key = aux->key;
      rt->right = deleteMin(rt->right);
    }
  }
}

std::optional<E> remove(BST& bst, Key k) {
  std::optional<E> aux = findHelp(bst.root, k);

  if (aux != std::nullopt) {
    bst.root = removeHelp(bst.root, k);
    --bst.nodeCount;
  }

  return aux;
}

void removeAll(BST& bst) {
  while (bst.root != nullptr) {
    remove(bst, bst.root->key);
  }
}

void preOrder(Node* rt) {
  if (rt != nullptr) {
    std::cout << rt->key << endl;
    preOrder(rt->left);
    preOrder(rt->right);
  }
}

void inOrder(Node* rt) {
  if (rt != nullptr) {
    inOrder(rt->left);
    std::cout << rt->key << endl;
    inOrder(rt->right);
  }
}

void posOrder(Node* rt) {
  if (rt != nullptr) {
    posOrder(rt->left);
    posOrder(rt->right);
    std::cout << rt->key << endl;
  }
}