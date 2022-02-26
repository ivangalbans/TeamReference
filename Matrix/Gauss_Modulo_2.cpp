/*
        [TESTED: SPOJ XMAX, LightOJ 1272,1288
        Matrix: (2) sol|x1 x2...xn
        Answer: 	ans[vars-1...0]
*/
const int MAXN = 110;
const int MAXR = 70;

bitset<MAXN> row[MAXR];

int ans[MAXN];
int first[MAXR];
int vars;
int rows;

void init(int _vars) {
  vars = _vars;
  rows = 0;
}

bool add(bitset<MAXN> cur) {
  for (int i = 0; i < rows; i++) {
    if (cur[first[i]] != 0) {
      cur ^= row[i];
    }
  }
  first[rows] = 0;
  while (first[rows] < vars && !cur[first[rows]])
    first[rows]++;

  /*remove if want to add always the equation*/
  if (first[rows] == vars && cur[vars])
    return false;
  row[rows++] = cur;
  return true;
}

void solve() {
  memset(ans, 0, sizeof ans);
  for (int i = rows - 1; i >= 0; i--) {
    int aux = row[i][vars];
    for (int j = first[i]; j < vars; j++)
      aux ^= (ans[j] * row[i][j]);
    ans[first[i]] = aux;
  }
}

int main() {

  init(3);

  bitset<MAXN> eq1(14), eq2(3), eq3(4);
  /*
           1|1 1 0
           0|0 1 1
           0|1 0 0
     ---------
     Ans:0 1 1
   */
  cout << add(eq1);
  cout << add(eq2);
  cout << add(eq3) << endl;

  solve();

  for (int i = vars - 1; i >= 0; --i)
    cout << ans[i] << " ";

  return 0;
}
