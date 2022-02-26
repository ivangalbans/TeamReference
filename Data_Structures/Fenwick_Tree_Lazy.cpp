/*
 *   Performance:
 *   0-based
 *   To start the index on 1
 *   lowbit  --> O(1)
 *   query  --> O(log N)
 *   update --> O(log N)
 */

// Tested Dibujo de Fito MOG
int n;
int l, r;
const int MaxN = 100005;
vector<int> ft(MaxN);

int lowbit(int x) { return x & -x; }

// a[pos] += val
void update(int pos, int val) {
  for (; pos <= MaxN; pos += lowbit(pos))
    ft[pos] += val;
}

// a[l...r] += val
void update(int l, int r, int val) {
  update(l, val);
  update(r + 1, -val);
}

// Return a[pos]
int query(int pos) {
  int sum = 0;
  for (; pos > 0; pos -= lowbit(pos))
    sum += ft[pos];
  return sum;
}
