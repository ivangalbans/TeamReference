/*
        TASK  : Coding a red-black tree

        Remarks: The keys are assumed to be integers. The data structure
                 allows duplicate keys.
        Performance:
                 Insert: O(log n)
                 Erase: O(log n)
                 Report size: Theta(1)
                 Find: O(log n)
                 Find mimimum/maximum: O(log n)
                 Find k-th: O(log n)
                 Find predecessor/successor: O(log n)
*/

struct Red_Black_Tree {

  enum colors { RED, BLACK };

  typedef int key_type;

#define RESIZE(x) ((x)->ch[0]->size + (x)->ch[1]->size + (x)->cnt)

  struct node {

    key_type key;
    int cnt, size;
    colors color;

    node *parent;
    node *ch[2];

    node() {}
  } * root, *null;

  /* Rotate node x to ( b ? right : left ) */
  void rotate(node *x, bool b) {

    node *y = x->ch[!b];
    x->ch[!b] = y->ch[b];

    y->ch[b]->parent = x;
    y->parent = x->parent;

    if (x->parent == null)
      root = y;
    else
      x->parent->ch[!(x == x->parent->ch[0])] = y;

    y->ch[b] = x;
    x->parent = y;

    x->size = RESIZE(x);
    y->size = RESIZE(y);
  }

  /* Find node with a given key in the tree */
  node *find(key_type key) {

    node *x = root;
    while (x) {
      if (key == x->key)
        return x;
      x = x->ch[!(key < x->key)];
    }
    return null;
  }

  /* Find ( b ? maximum : minimum ) key in x's subtree */
  /* The program halts if that subtree is empty!!!     */
  node *extreme(node *x, bool b) {

    assert(x != null);

    node *y = x;
    while (y->ch[b] != null)
      y = y->ch[b];

    return y;
  }

  /* Find a given key's ( b ? successor : predecessor ) */
  node *adjacent(key_type key, bool b) {

    node *x = find(key);

    if (x->ch[b] != null)
      return extreme(x->ch[b], !b);

    node *y = x->parent;
    while (y != null && x == y->ch[b])
      x = y, y = y->parent;
    return y;
  }

  /* Find k-th key in the inorder traversal of the tree */
  /* The program halts if k <= 0 or k > size(T)         */
  key_type rb_find_kth(int k) {

    assert(k > 0 && k <= root->size);

    node *x = root;
    while (1) {
      int lo_rank = x->ch[0]->size + 1, hi_rank = x->ch[0]->size + x->cnt;
      if (lo_rank <= k && k <= hi_rank)
        return x->key;
      if (k < lo_rank)
        x = x->ch[0];
      else
        k -= hi_rank, x = x->ch[1];
    }
  }

  /* Restore red-black properties after insertion */
  void rb_insert_fixup(node *z) {

    while (z->parent->color == RED) {
      bool b = !(z->parent == z->parent->parent->ch[0]);
      node *y = z->parent->parent->ch[!b];

      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->ch[!b]) {
          z = z->parent;
          rotate(z, b);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotate(z->parent->parent, !b);
      }
    }

    root->color = BLACK;
  }

  /* Restore red-black properties after deletion */
  void rb_erase_fixup(node *x) {

    while (x != root && x->color == BLACK) {

      bool b = !(x == x->parent->ch[0]);

      node *w = x->parent->ch[!b];
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotate(x->parent, b);
        w = x->parent->ch[!b];
      }
      if (w->ch[0]->color == BLACK && w->ch[1]->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->ch[!b]->color == BLACK) {
          w->ch[b]->color = BLACK;
          w->color = RED;
          rotate(w, !b);
          w = x->parent->ch[!b];
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->ch[!b]->color = BLACK;
        rotate(x->parent, b);
        x = root;
      }
    }

    x->color = BLACK;
  }

  /* Insert a given key in the tree (allowing duplicates) */
  node *rb_insert(key_type key) {

    node *x = root, *y = null;
    while (x != null && key != x->key) {
      y = x;
      y->size++;
      x = x->ch[!(key < x->key)];
    }

    if (x != null && key == x->key) {
      x->cnt++;
      x->size++;
      return root;
    }

    node *z = new node;

    z->key = key;
    z->cnt = z->size = 1;

    z->parent = y;
    if (y == null)
      root = z;
    else
      y->ch[!(z->key < y->key)] = z;

    z->ch[0] = z->ch[1] = null;
    z->color = RED;

    rb_insert_fixup(z);
    return root;
  }

  /* Delete a given key from the tree */
  node *rb_erase(key_type key) {

    node *z = find(key);
    if (z == null)
      return root;

    for (node *x = z->parent; x != null; x = x->parent)
      x->size--;
    if (z->cnt > 1) {
      z->cnt--;
      z->size--;
      return root;
    }

    node *y = (z->ch[0] == null || z->ch[1] == null) ? z : adjacent(z->key, 1);
    node *x = y->ch[!(y->ch[0] != null)];

    x->parent = y->parent;

    if (y->parent == null)
      root = x;
    else {
      y->parent->ch[!(y == y->parent->ch[0])] = x;
      y->parent->size = RESIZE(y->parent);
    }

    if (y != z) {
      z->key = y->key;
      z->cnt = y->cnt;
      z->size = RESIZE(z);
    }

    if (y->color == BLACK)
      rb_erase_fixup(x);
    delete y;

    return root;
  }

  /* "Public" methods */

  Red_Black_Tree() {
    null = new node;
    null->color = BLACK;
    null->size = null->cnt = 0;
    root = null;
  }
  int size() { return root->size; }
  bool contained(int x) { return find(x) != null; }
  key_type min() { return extreme(root, 0)->key; }
  key_type max() { return extreme(root, 1)->key; }
  key_type find_kth(int k) { return rb_find_kth(k); }
  void insert(int x) { root = rb_insert(x); }
  void erase(int x) { root = rb_erase(x); }
  key_type predecessor(int x) {
    node *y = adjacent(x, 0);
    return (y != null) ? y->key : x;
  }
  key_type successor(int x) {
    node *y = adjacent(x, 1);
    return (y != null) ? y->key : x;
  }

  void in(node *t) {
    if (t == null)
      return;
    in(t->ch[0]);
    cout << t->key << " ";
    in(t->ch[1]);
  }
};
