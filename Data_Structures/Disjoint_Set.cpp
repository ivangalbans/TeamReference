int N;
int parent[N], cont[N];

void initSet() {
  for (int i = 0; i < N; ++i) {
    parent[i] = i;
    cont[i] = 1;
  }
}

int SetOf(int x) { return (x == parent[x]) ? x : parent[x] = SetOf(parent[x]); }

void Merge(int x, int y) {
  x = SetOf(x);
  y = SetOf(y);

  if (x == y)
    return;

  if (cont[x] < cont[y])
    swap(x, y);

  parent[y] = x;
  cont[x] += cont[y];
}
