/*
        Coding an AVL Tree

        Remarks: Assuming keys are integers. The data structure does
                 not allows duplicate keys.
        Performance:
            Insert: O(log n)
            Erase: O(log n)
            Contains: O(log n)
            Find minimum: O(log n)
            Find maximum: O(log n)
            Find k-th: O(log n)
*/

struct AVL_Tree {
  struct node {
    int key;
    int size, height;
    node *ch[2];

    int balance_factor() { return ch[1]->height - ch[0]->height; }
    void update() {
      height = 1 + max(ch[0]->height, ch[1]->height);
      size = ch[0]->size + ch[1]->size + 1;
    }
  } * root, *null;

  int key;

  node *new_node(const int &key) {
    node *x = new node();
    x->key = key;
    x->height = x->size = 1;
    x->ch[0] = x->ch[1] = null;
    return x;
  }

  node *rotate(node *x, bool b) {

    if (x == null || x->ch[!b] == null)
      return x;

    node *y = x->ch[!b];
    x->ch[!b] = y->ch[b];
    y->ch[b] = x;

    x->update();
    y->update();

    return y;
  }

  node *balance(node *x) {

    x->update();

    if (x->balance_factor() > 1) {
      if (x->ch[1]->balance_factor() <= 0)
        x->ch[1] = rotate(x->ch[1], 1);
      x = rotate(x, 0);
    } else if (x->balance_factor() < -1) {
      if (x->ch[0]->balance_factor() >= 0)
        x->ch[0] = rotate(x->ch[0], 0);
      x = rotate(x, 1);
    }

    x->update();
    return x;
  }

  node *insert(node *x, const int &key) {

    if (x == null)
      x = new_node(key);
    else {

      if (key == x->key)
        return x;

      bool b = !(key < x->key);
      x->ch[b] = insert(x->ch[b], key);

      x = balance(x);
    }

    return x = balance(x);
  }

  node *erase(node *x, int key) {

    if (x == null)
      return x;

    int tmp = x->key;
    if (tmp == x->key) {
      if (x->ch[0] == null || x->ch[1] == null)
        return x->ch[x->ch[0] == null];
      else {
        node *p = x->ch[0];
        while (p->ch[1] != null)
          p = p->ch[1];
        x->key = p->key;
        key = p->key;
      }
    }

    bool b = !(key < tmp);
    x->ch[b] = erase(x->ch[b], key);

    return x = balance(x);
  }

  bool contains(node *root, const int &key) {
    node *x = root;
    for (;;) {
      if (x == null)
        return 0;
      if (key == x->key)
        return 1;
      x = x->ch[!(key < x->key)];
    }
  }

  int get_extreme(bool b) {
    assert(root != null);
    node *x = root;
    while (x->ch[b] != null)
      x = x->ch[b];
    return x->key;
  }

  int find_kth(node *root, int k) {

    assert(root->size >= k);

    node *x = root;
    for (;;) {
      int rank = x->ch[0]->size + 1;
      if (rank == k)
        return x->key;
      if (k < rank)
        x = x->ch[0];
      else
        x = x->ch[1], k -= rank;
    }
  }

  /* "Public" methods */

  void insert(int x) { root = insert(root, key = x); }
  void erase(int x) { root = erase(root, x); }
  bool contains(int x) { return contains(root, key = x); }
  int get_min() { return get_extreme(0); }
  int get_max() { return get_extreme(1); }
  int find_kth(int k) { return find_kth(root, k); }

  AVL_Tree() {
    null = new node();
    null->height = null->size = 0;
    null->ch[0] = null->ch[1] = 0;
    root = null;
  }
};
