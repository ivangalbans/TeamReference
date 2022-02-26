typedef long long ptype;

ptype seed = 47;

ptype my_rand() {
  seed = (seed * 279470273) % 4294967291LL;
  return seed;
}

struct ImplicitTreap {

  struct item {
    int value;
    ptype prior;
    item *l, *r;
    int sons;

    bool rev;
    long long sum;

    item() {}
    item(int value) : value(value), l(0), r(0), sons(0), rev(0), sum(value) {
      prior = my_rand();
    }
  } * root;

  void fix(item *t) {
    if (!t)
      return;
    t->sons = (t->l ? t->l->sons + 1 : 0) + (t->r ? t->r->sons + 1 : 0);
    t->sum = (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0) + t->value;
  }

  void push(item *it) {
    if (it && it->rev) {
      it->rev = 0;
      swap(it->l, it->r);
      if (it->l)
        it->l->rev ^= 1;
      if (it->r)
        it->r->rev ^= 1;
    }
  }

  void merge(item *&t, item *l, item *r) {
    push(l);
    push(r);

    if (!l || !r)
      t = l ? l : r;
    else if (l->prior > r->prior)
      merge(l->r, l->r, r), t = l;
    else
      merge(r->l, l, r->l), t = r;

    fix(t);
  }

  void split(item *t, item *&l, item *&r, int pos, int add = 0) {
    if (!t)
      l = r = NULL;
    else {
      push(t);
      int cur_pos = add + (t->l ? 1 + t->l->sons : 0);

      if (pos <= cur_pos)
        split(t->l, l, t->l, pos, add), r = t;
      else
        split(t->r, t->r, r, pos, cur_pos + 1), l = t;

      fix(t);
    }
  }

  void insert(item *&t, item *&it, int pos, int add = 0) {
    if (!t)
      t = it;
    else {
      push(t);
      int cur_pos = add + (t->l ? 1 + t->l->sons : 0);

      if (it->prior > t->prior) {
        split(t, it->l, it->r, pos, add), t = it;
      } else {
        if (pos <= cur_pos)
          insert(t->l, it, pos, add);
        else
          insert(t->r, it, pos, cur_pos + 1);
      }
      fix(t);
    }
  }

  void remove(item *&t, int pos, int add = 0) {
    int cur_pos = add + (t->l ? 1 + t->l->sons : 0);

    if (cur_pos == pos)
      merge(t, t->l, t->r);
    else if (pos < cur_pos)
      remove(t->l, pos, add);
    else
      remove(t->r, pos, cur_pos + 1);

    fix(t);
  }

  void reverse(item *t, int l, int r) {
    item *t1, *t2, *t3;

    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);

    t2->rev ^= 1;
    merge(t, t1, t2);
    merge(t, t, t3);
  }

  long long sum(item *&t, int lo, int hi, int a, int b, int add = 0) {
    if (!t || lo > b || hi < a)
      return 0;

    if (a <= lo && hi <= b)
      return t->sum;

    if (t->rev)
      push(t);
    int cur_key = add + (t->l ? 1 + t->l->sons : 0);

    long long ret = (a <= cur_key && cur_key <= b ? t->value : 0);

    ret += sum(t->l, lo, cur_key - 1, a, b, add);
    ret += sum(t->r, cur_key + 1, hi, a, b, cur_key + 1);

    return ret;
  }

  void print(item *t) {
    if (!t)
      return;
    push(t);
    print(t->l);
    printf("%d ", t->value);
    print(t->r);
  }

  void clear(item *t) {
    if (!t)
      return;
    clear(t->l);
    delete t;
    clear(t->r);
  }

  ImplicitTreap() { root = 0; }

  /*Public Methods*/

  void print() { print(root); }

  int size() { return root->sons + 1; }

  long long sum(int l, int r) { return sum(root, 0, this->size() - 1, l, r); }

  void reverse(int l, int r) { reverse(root, l, r); }

  void remove(int pos) { remove(root, pos); }

  void insert(int pos, int val) {
    item *node = new item(val);
    insert(root, node, pos);
  }

  void clear() { clear(root); }
};
