/*
  TASK  : Coding a treap

  Remarks: Assuming keys are integers. Using Max Heap
  Performance:
     Insert: O(log n)*
     Erase: O(log n)*
     Find: O(log n)*
     Find k-th: O(log n)*

     * expected
*/

struct generator {

  static const int A = 48271;
  static const int M = 2147483647;
  static const int Q = M / A;
  static const int R = M % A;

  int state;

  generator() {
    srand(time(0));
    state = rand() + 1;
  }
  int pseudo_random() {
    state = A * (state % Q) - R * (state / Q);
    return state > 0 ? state : state += M;
  }
} g;

struct treap {

#define SIZE(x) ((x) ? (x)->size : 0)
#define RESIZE(x) (SIZE((x)->ch[0]) + SIZE((x)->ch[1]) + (x)->cnt)

  struct node {
    int key, p, size, cnt;
    node *ch[2];
    node(int key) : key(key), p(g.pseudo_random()), size(1), cnt(1) {
      ch[0] = ch[1] = 0;
    }
  } * root;

  int key;

  node *rotate(node *x, bool b) {
    node *y = x->ch[!b];
    x->ch[!b] = y->ch[b];
    y->ch[b] = x;
    x->size = RESIZE(x);
    y->size = RESIZE(y);
    return y;
  }

  node *insert(node *t, const int &key) {

    if (!t)
      return new node(key);

    if (key == t->key)
      t->cnt++, t->size++;
    else {
      bool b = !(key < t->key);
      t->ch[b] = insert(t->ch[b], key);
      t->size = RESIZE(t);
      if (t->ch[b]->p > t->p)
        t = rotate(t, !b);
    }
    return t;
  }

  node *erase(node *t, const int &key) {

    if (!t)
      return 0;

    if (key != t->key) {
      bool b = !(key < t->key);
      t->ch[b] = erase(t->ch[b], key);
      t->size = RESIZE(t);
    } else {
      if (t->cnt > 1)
        t->cnt--, t->size--;
      else {
        if (!t->ch[0] && !t->ch[1]) {
          delete t;
          return 0;
        } else if (!t->ch[0])
          t = rotate(t, 0);
        else if (!t->ch[1])
          t = rotate(t, 1);
        else
          t = rotate(t, t->ch[0]->p > t->ch[1]->p);
        t = erase(t, key);
      }
    }

    return t;
  }

  /* "Public" methods */

  void insert(int x) { root = insert(root, key = x); }
  void erase(int x) { root = erase(root, key = x); }
  int size() { return SIZE(root); }
  bool find(int x) {
    node *t = root;
    while (t) {
      if (x == t->key)
        return 1;
      t = t->ch[!(x < t->key)];
    }
    return 0;
  }
  int find_kth(int k) { /* assuming k <=
                           SIZE( root ) */
    node *t = root;
    while (1) {
      int lo_rank = SIZE(t->ch[0]) + 1, hi_rank = SIZE(t->ch[0]) + t->cnt;
      if (lo_rank <= k && k <= hi_rank)
        return t->key;
      else if (k < lo_rank)
        t = t->ch[0];
      else {
        k -= hi_rank;
        t = t->ch[1];
      }
    }
  }

  treap() : root(0) {}
};
