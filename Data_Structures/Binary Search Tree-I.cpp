//============================================================================
// Name        : Binary.cpp
// Author      : ivan
// Version     :
// Copyright   : Free
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits\stdc++.h>

using namespace std;

struct BST {

  struct node {
    int key; /* assuming keys are integers */
    node *ch[2];
    node *pi;
    node(int key) : key(key) { ch[0] = ch[1] = pi = 0; }

  } * root;

  node *find(node *x, int k) {
    while (x && k != x->key)
      x = x->ch[!(k < x->key)];
    return x;
  }

  node *get_min(node *x) {
    while (x->ch[0])
      x = x->ch[0];
    return x;
  }

  node *get_max(node *x) {
    while (x->ch[1])
      x = x->ch[1];
    return x;
  }

  node *get_successor(node *x) {
    if (x->ch[1])
      return get_min(x->ch[1]);

    node *y = x->pi;
    while (y && x == y->ch[1]) {
      x = y;
      y = y->pi;
    }
    return y;
  }

  void insert(node *x, int val) {
    node *z = new node(val);
    node *y = 0;
    while (x) {
      y = x;
      x = x->ch[!(val < x->key)];
    }
    z->pi = y;
    if (!y)
      root = z;

    else
      y->ch[!(val < y->key)] = z;
  }

  void erase(node *z) {
    if (!z)
      return;
    node *x = 0;
    node *y = 0;

    if (z->ch[0] == 0 || z->ch[1] == 0)
      y = z;
    else
      y = get_successor(z);

    x = y->ch[!(y->ch[0])];

    if (x != 0)
      x->pi = y->pi;

    if (y->pi == 0)
      root = x;

    else if (y == (y->pi)->ch[0])
      (y->pi)->ch[0] = x;
    else
      (y->pi)->ch[1] = x;

    if (y != z)
      z->key = y->key;

    delete y;
  }

  void in(node *x) {
    if (!x)
      return;
    in(x->ch[0]);
    cout << x->key << " ";
    in(x->ch[1]);
  }

  void clear(node *t) {
    if (!t)
      return;
    clear(t->ch[0]);
    clear(t->ch[1]);
    delete t;
  }

  bool find(const int &key) { return find(root, key); }
  void insert(const int &key) { insert(root, key); }
  void erase(const int &key) { erase(find(root, key)); }
  void clear() { clear(root); }
  int get_min() { return get_min(root)->key; }
  int get_max() { return get_max(root)->key; }

  BST() : root(0) {}
};

int main() {

  BST a;

  a.insert(1);
  a.insert(7);
  a.insert(2);
  a.insert(4);
  a.insert(15);

  a.in(a.root);
  cout << endl;

  a.erase(1);
  a.erase(7);

  a.in(a.root);

  a.clear();

  return 0;
}
