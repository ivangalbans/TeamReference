
pair<vector<int>, int> rmatrix(int base, int div) {
  vector<int> vis(div, -1);
  vector<int> res;
  res.push_back(1);
  vis[1] = 0;

  while (vis[(res[res.size() - 1] * base) % div] == -1) {
    vis[(res[res.size() - 1] * base) % div] = res.size();
    res.push_back((res[res.size() - 1] * base) % div);
  }
  return make_pair(res, vis[(res[res.size() - 1] * base) % div]);
}

bool div(int base, int div, vector<int> &num) // reverse num
{
  pair<vector<int>, int> r = rmatrix(base, div);
  int pp = 0, b = r.second;
  vector<int> a = r.first;
  for (int i = 0; i < num.size(); ++i) {
    int kk = num[i];
    if (i < b)
      pp += ((kk * a[i]) % div);
    else
      pp += ((kk * a[b + ((i - b) % (a.size() - b))]) % div);
  }
  return pp % div == 0;
}
