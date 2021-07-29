// Problem's source: https://www.spoj.com/problems/SDITSAVL/en/

#include <iostream>
#include <algorithm>

using namespace std;
using Key = int;

struct Node {
  Key key;
  Node *left;
  Node *right;
  int height;
  int size;
};

struct AVL {
  Node *root;
};

Node *createNode(Key k) {
  Node *newNode = new Node;
  newNode->key = k;
  newNode->left = newNode->right = nullptr;
  newNode->height = 0;
  newNode->size = 1;
  return newNode;
}

AVL createAVL() {
  AVL avl;
  avl.root = nullptr;
  return avl;
}

int getSize(Node *rt){
  if(rt == nullptr){
    return 0;
  }

  return rt->size;
}

int h(Node *rt) {
  if (rt == nullptr) {
    return -1;
  }

  return rt->height;
}

int getBalance(Node *rt) {
  if (rt == nullptr) {
    return 0;
  }

  return (h(rt->left) - h(rt->right));
}

Node *leftRotate(Node *rt){
  Node *r = rt->right;
  Node *rl = r->left;

  r->left = rt;
  rt->right = rl;
  rt->height = max(h(rt->left), h(rt->right)) + 1;
  r->height = max(h(r->left), h(r->right)) + 1;

  rt->size = getSize(rt->left) + getSize(rt->right) + 1;
  r->size = getSize(r->left) + getSize(r->right) + 1;

  return r;
}

Node *rightRotate(Node *rt){
  Node *l = rt->left;
  Node *lr = l->right;

  l->right = rt;
  rt->left = lr;

  rt->height = max(h(rt->left), h(rt->right)) + 1;
  l->height = max(h(l->left), h(l->right)) + 1;

  rt->size = getSize(rt->left) + getSize(rt->right) + 1;
  l->size = getSize(l->left) + getSize(l->right) + 1;

  return l;
}

Node *insertHelp(Node *rt, Key k) {
  if (rt == nullptr) {
    return createNode(k);
  }

  if (k < rt->key) {
    rt->left = insertHelp(rt->left, k);
  } else {
    rt->right = insertHelp(rt->right, k);
  }

  rt->height = 1 + max(h(rt->left), h(rt->right));
  rt->size = 1 + getSize(rt->left) + getSize(rt->right);
  int balance = getBalance(rt);

  if (balance < -1 && k >= rt->right->key) {
    return leftRotate(rt);
  }

  if (balance > 1 && k < rt->left->key) {
    return rightRotate(rt);
  }

  if (balance > 1 && k >= rt->left->key) {
    rt->left = leftRotate(rt->left);
    return rightRotate(rt);
  }

  if (balance < -1 && k < rt->right->key) {
    rt->right = rightRotate(rt->right);
    return leftRotate(rt);
  }

  return rt;
}

void insert(AVL &avl, Key k) {
  avl.root = insertHelp(avl.root, k);
}

Node *findHelp(Node *rt, Key k) {
  if (rt == nullptr) {
    return nullptr;
  }

  if (k < rt->key) {
    return findHelp(rt->left, k);
  } else if (k == rt->key) {
    return rt;
  } else {
    return findHelp(rt->right, k);
  }
}

Node *find(AVL &avl, Key k) {
  return findHelp(avl.root, k);
}

void findIndex(Node *rt, Key k, int &count) {
  if (rt == nullptr) {
    cout << "Data tidak ada" << endl;
    return;
  }

  if (k < rt->key) {
    findIndex(rt->left, k, count);
  } else if (k == rt->key) {
    cout << count + getSize(rt->left) << endl;
  } else {
    count += 1 + getSize(rt->left);
    findIndex(rt->right, k, count);
  }
}

int main() {
  AVL avl = createAVL();

  int n;
  cin >> n;

  int id, key;
  while (n--) {
    cin >> id >> key;
    if (id == 1) {
      insert(avl, key);
    } else {
      int count = 1;
      findIndex(avl.root, key, count);
    }
  }
  
  return 0;
}