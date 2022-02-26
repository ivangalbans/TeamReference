/*
Stern-Brocot Tree for enumerating rationals
Enumerating all irreducible rationals ascending order,
Whose sum of N and D is atmost B
*/
void sternBrocot(Int B, Int pl = 0, Int ql = 1, Int pr = 1, Int qr = 0) {
  Int pm = pl + pr, qm = ql + qr;
  if (pm + qm > B)
    return;
  sternBrocot(B, pl, ql, pm, qm); // [pl / ql, pm / qm]
  cout << pm << "/" << qm << endl;
  sternBrocot(B, pm, qm, pr, qr); // [pm / qm, pr / qr]
}
