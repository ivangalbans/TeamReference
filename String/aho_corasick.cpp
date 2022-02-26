#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl;

const int size = 505;
const int MAXS = size * size + 10;
const int MAXC = 26;

struct aho_corasick {
  vector<string> key;
  vector<bitset<505>> output;
  vector<int> failure;
  vector<vector<int>> gto;

  int buildMachine() {
    int states = 1;
    for (int i = 0; i < key.size(); ++i) {
      const string &word = key[i];
      int currentState = 0;

      for (int j = 0; j < word.size(); ++j) {
        int ch = word[j] - 'a';

        if (gto[currentState][ch] == -1)
          gto[currentState][ch] = states++;

        currentState = gto[currentState][ch];
      }
      output[currentState].set(i);
    }

    for (int ch = 0; ch < MAXC; ++ch)
      if (gto[0][ch] == -1)
        gto[0][ch] = 0;

    queue<int> q;
    for (int ch = 0; ch < MAXC; ++ch) {
      if (gto[0][ch] != 0) {
        failure[gto[0][ch]] = 0;
        q.push(gto[0][ch]);
      }
    }

    while (!q.empty()) {
      int state = q.front();
      q.pop();

      for (int ch = 0; ch < MAXC; ++ch) {
        if (gto[state][ch] != -1) {
          int f = failure[state];
          while (gto[f][ch] == -1)
            f = failure[f];

          f = gto[f][ch];
          failure[gto[state][ch]] = f;
          output[gto[state][ch]] |= output[f];
          q.push(gto[state][ch]);
        }
      }
    }
    return states;
  }

  aho_corasick(const vector<string> &k) : key(k) {
    failure = vector<int>(MAXS, -1);
    gto = vector<vector<int>>(MAXS, vector<int>(MAXC, -1));
    output = vector<bitset<505>>(MAXS);

    buildMachine();
  }

  int nextState(int currentState, char nextInput) {
    int state = currentState;
    int ch = nextInput - 'a';
    while (gto[state][ch] == -1)
      state = failure[state];
    return gto[state][ch];
  }

  vector<int> match(const string &text) {
    vector<int> ans(key.size());
    int currentState = 0;

    for (int i = 0; i < text.size(); ++i) {
      currentState = nextState(currentState, text[i]);

      if (output[currentState].any())
        for (int j = 0; j < key.size(); ++j)
          if (output[currentState].test(j))
            ans[j]++;
    }
    return ans;
  }
};

int main() {
  int nc;
  cin >> nc;
  for (int tc = 1; tc <= nc; ++tc) {
    int n;
    cin >> n;
    string t;
    cin >> t;
    vector<string> key(n);
    for (int i = 0; i < n; ++i)
      cin >> key[i];

    aho_corasick aho(key);

    cout << "Case " << tc << ":\n";
    vector<int> ans = aho.match(t);
    for (int i = 0; i < ans.size(); ++i)
      cout << ans[i] << endl;
  }

  return 0;
}
