/*
    TASK  : Coding a splay tree

    Remarks: Assuming keys are integers. This version uses a
    top-down splay approach, although it is necessary to traverse the root's
   left and right paths (once the tree has been splayed) for size maintaining.

    Performance:
    Splay: O(log n)*
    Insert: O(log n)*
    Erase: O(log n)*
    Find: O(log n)*
    Count lesser than: O(log n)*
    Count greater than: O(log n)*

    * amortized
*/

const int oo = 1 << 30;

struct SplayTree {

#define SIZE(x) ((x) ? (x)->size : 0)
#define RESIZE(x) (SIZE((x)->l) + SIZE((x)->r) + (x)->cnt)

  struct node {
    int key, size, cnt;
    node *l, *r;
    node(int key = 0, int size = 1, int cnt = 1, node *l = 0, node *r = 0)
        : key(key), size(size), cnt(cnt), l(l), r(r) {}
  } * root;

  int key;

  node *leftRotate(node *x) {
    node *y = x->r;
    x->r = y->l;
    y->l = x;
    x->size = RESIZE(x);
    y->size = RESIZE(y);
    return y;
  }

  node *rightRotate(node *x) {
    node *y = x->l;
    x->l = y->r;
    y->r = x;
    x->size = RESIZE(x);
    y->size = RESIZE(y);
    return y;
  }

  void update_size(node *t, bool right) {
    if (!t)
      return;
    update_size(!right ? t->l : t->r, right);
    t->size = RESIZE(t);
  }

  node *splay(node *t, const int &key) {

    if (!t)
      return NULL;
    node header, *L = &header, *R = &header;
    header.size = header.cnt = 0;

    for (;;) {
      if (key < t->key) {
        if (t->l && key < t->l->key)
          t = rightRotate(t);
        if (!t->l)
          break;
        R->l = t;
        R = t;
        t = t->l;
      } else if (key > t->key) {
        if (t->r && key > t->r->key)
          t = leftRotate(t);
        if (!t->r)
          break;
        L->r = t;
        L = t;
        t = t->r;
      } else
        break;
    }

    L->r = t->l;
    R->l = t->r;
    t->l = header.r;
    t->r = header.l;

    update_size(t->l, 1);
    update_size(t->r, 0);
    t->size = RESIZE(t);

    return t;
  }

  node *find(int x) {
    root = splay(root, key = x);
    return (root && x == root->key) ? root : NULL;
  }

  void insert(int x) {
    if (!root)
      root = new node(x, 1, 1, NULL, NULL);
    else {
      root = splay(root, key = x);
      if (x < root->key) {
        node *t = new node(x, SIZE(root) + 1, 1, root->l, root);
        root->l = NULL;
        root->size = RESIZE(root);
        root = t;
      } else if (x > root->key) {
        node *t = new node(x, SIZE(root) + 1, 1, root, root->r);
        root->r = NULL;
        root->size = RESIZE(root);
        root = t;
      } else
        root->cnt++, root->size++;
    }
  }

  void erase(int x) {
    if (!find(x))
      return;
    if (root->cnt > 1)
      root->cnt--, root->size--;
    else {
      if (!root->l)
        root = root->r;
      else {
        node *hold = root->r;
        root = splay(root->l, key = x);
        root->r = hold;
      }
    }
  }

  int getMin() { /* assuming there is no key < -2^30 */
    root = splay(root, -oo);
    return root->key;
  }

  int getMax() { /* assuming there is no key > 2^30 */
    root = splay(root, +oo);
    return root->key;
  }

  int countLesserThan(int x) {
    if (!root)
      return 0;
    root = splay(root, key = x);
    if (root->key >= x)
      return SIZE(root->l);
    else
      return SIZE(root->l) + root->cnt;
  }

  int countGreaterThan(int x) {
    if (!root)
      return 0;
    root = splay(root, key = x);
    if (root->key <= x)
      return SIZE(root->r);
    else
      return SIZE(root->r) + root->cnt;
  }

  SplayTree() : root(0){};
};
