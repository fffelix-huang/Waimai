// abacbaba -> [0, 0, 1, 0, 0, 3, 0, 1]
vi z_algorithm(const vi& a) {
	int n = SZ(a);
	vi z(n); int j = 0;
	FOR(i, 1, n) {
		if(i <= j + z[j]) z[i] = min(z[i - j], j + z[j] - i);
		while(i + z[i] < n && a[i + z[i]] == a[z[i]]) z[i]++;
		if(i + z[i] > j + z[j]) j = i;
	}
	return z;
}