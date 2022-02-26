/*
     TASK  : Given a set P of strings and a string S, count how many
             elements of P contain S as a prefix, and how many p(i), for
             some i, have |p(i)|<|S|.

     Remarks: Using English alphabet (|S|=26)
     Performance:
        Insert: O(|p|)
        Count: O(|p|)
        p: string processed
*/

#define MAXLEN 20000

struct Trie {

  struct node {
    int partial, full;
    node *edge[26];
    node() : partial(0), full(0) { memset(edge, 0, sizeof(edge)); }
  } * root;

  Trie() { root = new node(); }

  void insert(char s[], int len) {

    node *t = root;
    for (int i = 0; i < len; i++) {
      char c = s[i] - 'a';
      if (!t->edge[c])
        t->edge[c] = new node();
      t = t->edge[c];
      t->partial++;
    }
    t->full++;
  }

  int count(char s[], int len) {

    if (!root)
      return 0;

    node *t = root;
    int ret = 0;

    for (int i = 0; i < len; i++) {
      if (!t)
        break;
      ret += t->full;
      t = t->edge[s[i] - 'a'];
    }
    if (t)
      ret += t->partial;

    return ret;
  }
};
