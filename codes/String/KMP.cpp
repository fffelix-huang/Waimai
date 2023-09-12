// abacbaba -> [0, 0, 1, 0, 0, 1, 2, 3]
vi KMP(const vi& a) {
	int n = SZ(a);
	vi k(n);
	FOR(i, 1, n) {
		int j = k[i - 1];
		while(j > 0 && a[i] != a[j]) j = k[j - 1];
		j += (a[i] == a[j]);
		k[i] = j;
	}
	return k;
}
