int discrete_log(int a, int b, int m) {
	if(b == 1 || m == 1) return 0;
	int n = sqrt(m) + 2, e = 1, f = 1, j = 1;
	unordered_map<int, int> A; // becareful
	while(j <= n && (e = f = 1LL * e * a % m) != b) A[1LL * e * b % m] = j++;
	if(e == b) return j;
	if(__gcd(m, e) == __gcd(m, b))  {
		FOR(i, 2, n + 2) {
			e = 1LL * e * f % m;
			if(A.find(e) != A.end()) return n * i - A[e];
		}
	}
	return -1;
}
