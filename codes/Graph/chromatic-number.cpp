// vi to(n);
// to[u] |= 1 << v;
// to[v] |= 1 << u;
int chromatic_number(vi g) {
	constexpr int MOD = 998244353;
	int n = SZ(g);
	vector<int> I(1 << n); I[0] = 1;
	FOR(s, 1, 1 << n) {
		int v = __builtin_ctz(s), t = s ^ (1 << v);
		I[s] = (I[t] + I[t & ~g[v]]) % MOD;
	}
	auto f = I;
	FOR(k, 1, n + 1) {
		int sum = 0;
		REP(s, 1 << n) {
			if((__builtin_popcount(s) ^ n) & 1) sum -= f[s];
			else sum += f[s];
			sum = ((sum % MOD) + MOD) % MOD;
			f[s] = 1LL * f[s] * I[s] % MOD;
		}
		if(sum != 0) return k;
	}
	return 48763;
}