int main() {
  int test;
  scanf("%d", &test);
  getchar();
  string line;
  for (int i = 0; i < test; i++) {
    getline(cin, line);
    istringstream in(line);

    while (in >> line)
      cout << line << endl;
  }
  return 0;
}
