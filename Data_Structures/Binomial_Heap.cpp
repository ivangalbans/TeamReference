/*
          TASK: Coding a binomial heap

          Remarks: Assuming keys are integers. The data structure obeys the
                   min-heap property.
          Performance:
              Get minimum/maximum key: O(log n)
              Insert: O(log n)
              Erase mimimum/maximum: O(log n)
              Decrease key: O(log n)
              Erase: O(log n)
              Merge: O(log n)
*/
struct Binomial_Heap {

  static const int oo = 1 << 30;

  struct node {

    int key, degree;
    node *parent;
    node *child, *sibling; /* left-child right-sibling representation */

    node() {}
    node(int key) : key(key), degree(0) { parent = child = sibling = 0; }

  } * head;

  /* It returns the minimum key in the heap */
  int get_min() {
    assert(head);
    int minim = head->key;
    for (node *x = head->sibling; x; x = x->sibling)
      minim = min(minim, x->key);
    return minim;
  }

  /* It links the B(k-1) tree rooted at y to the B(k-1) tree */
  /* rooted at z (i.e. it makes z the parent of y). Node z   */
  /* becomes the root of a B(k) tree                         */
  void binomial_link(node *y, node *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
  }

  /* It merges the root lists of two binomial heaps into */
  /* a single linked list that is sorted by degree into  */
  /* monotonically increasing oder                       */
  node *binomial_heap_merge(node *h1, node *h2) {

    node *start, *curr;
    node *x = h1, *y = h2;

    if (!x || !y)
      return x ? x : y;

    if (x->degree < y->degree)
      start = x, x = x->sibling;
    else
      start = y, y = y->sibling;

    curr = start;

    while (x && y) {
      if (x->degree < y->degree)
        curr->sibling = x, curr = x, x = x->sibling;
      else
        curr->sibling = y, curr = y, y = y->sibling;
    }

    while (x)
      curr->sibling = x, curr = x, x = x->sibling;
    while (y)
      curr->sibling = y, curr = y, y = y->sibling;

    return start;
  }

  /* It unites two binomial heaps */
  node *binomial_heap_union(node *h1, node *h2) {

    node *h = binomial_heap_merge(h1, h2);

    h1 = h2 = 0;
    delete h1;
    delete h2;

    if (!h)
      return 0;

    node *prev_x = 0, *x = h, *next_x = x->sibling;

    while (next_x) {
      if (x->degree != next_x->degree ||
          (next_x->sibling && next_x->sibling->degree == x->degree)) {
        prev_x = x;
        x = next_x;
      } else {
        if (x->key <= next_x->key) {
          x->sibling = next_x->sibling;
          binomial_link(next_x, x);
        } else {
          if (!prev_x)
            h = next_x;
          else
            prev_x->sibling = next_x;
          binomial_link(x, next_x);
          x = next_x;
        }
      }
      next_x = x->sibling;
    }
    return h;
  }

  /* It inserts a new node into the heap */
  node *binomial_heap_insert(int x) {
    node *h = new node(x);
    return binomial_heap_union(head, h);
  }

  /* It erases the node with minimum key from the heap */
  node *binomial_heap_erase_min() {

    assert(head);

    int minim = head->key;
    node *y = head, *prev_y = 0;
    for (node *x = head->sibling; x; x = x->sibling)
      if (x->key < minim) {
        minim = x->key;
        prev_y = y;
        y = x;
      }

    if (!prev_y)
      head = head->sibling;
    else
      prev_y->sibling = y->sibling;

    // h-> Reverse order of the linked list of y's children
    node *h = 0, *next;
    node *to_destroy = y;
    for (y = y->child; y; y = next) {
      next = y->sibling;
      y->sibling = h;
      h = y;
    }

    delete to_destroy;
    return binomial_heap_union(head, h);
  }

  /* It decreases node x's key (if the new value is, however, */
  /* bigger than the original, then nothing is done)          */
  void binomial_heap_decrease_key(node *x, int key) {

    if (key > x->key)
      return;

    x->key = key;
    node *y = x, *z = y->parent;

    while (z && y->key < z->key) {
      swap(y->key, z->key);
      y = z;
      z = y->parent;
    }
  }

  /* It erases node x from the heap */
  node *binomial_heap_erase(node *x) {
    /* assuming there is no key < -2^30 */
    binomial_heap_decrease_key(x, -oo);
    return binomial_heap_erase_min();
  }

  /* "Public" methods */

  Binomial_Heap() : head(0) {}
  int min_key() { return get_min(); }
  void insert(int x) { head = binomial_heap_insert(x); }
  void erase_min() { head = binomial_heap_erase_min(); }
  void decrease_key(node *x, int key) { binomial_heap_decrease_key(x, key); }
  void erase(node *x) { head = binomial_heap_erase(x); }
  void merge(Binomial_Heap *h) { head = binomial_heap_union(head, h->head); }
};
