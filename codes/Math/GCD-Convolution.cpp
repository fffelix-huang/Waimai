// 2, 3, 5, 7, ...
vector<int> prime_enumerate(int N) {
	vector<bool> sieve(N / 3 + 1, 1);
	for(int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn; p += d = 6 - d, i++) {
		if(!sieve[i]) continue;
		for(int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p; q < SZ(sieve); q += r = s - r) sieve[q] = 0;
	}
	vector<int> ret{2, 3};
	for(int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++) {
		if(sieve[i]) {
			ret.pb(p);
		}
	}
	while(SZ(ret) && ret.back() > N) ret.pop_back();
	return ret;
}
struct divisor_transform {
	template<class T>
	static void zeta_transform(vector<T>& a) {
		int n = a.size() - 1;
		for(auto p : prime_enumerate(n)) {
			for(int i = 1; i * p <= n; i++) {
				a[i * p] += a[i];
			}
		}
	}
	template<class T>
	static void mobius_transform(vector<T>& a) {
		int n = a.size() - 1;
		for(auto p : prime_enumerate(n)) {
			for(int i = n / p; i > 0; i--) {
				a[i * p] -= a[i];
			}
		}
	}
};
struct multiple_transform {
	template<class T>
	static void zeta_transform(vector<T>& a) {
		int n = a.size() - 1;
		for(auto p : prime_enumerate(n)) {
			for(int i = n / p; i > 0; i--) {
				a[i] += a[i * p];
			}
		}
	}
	template<class T>
	static void mobius_transform(vector<T>& a) {
		int n = a.size() - 1;
		for(auto p : prime_enumerate(n)) {
			for(int i = 1; i * p <= n; i++) {
				a[i] -= a[i * p];
			}
		}
	}
};
// lcm: multiple -> divisor
template<class T>
vector<T> gcd_convolution(const vector<T>& a, const vector<T>& b) {
	assert(a.size() == b.size());
	auto f = a, g = b;
	multiple_transform::zeta_transform(f);
	multiple_transform::zeta_transform(g);
	REP(i, SZ(f)) f[i] *= g[i];
	multiple_transform::mobius_transform(f);
	return f;
}
