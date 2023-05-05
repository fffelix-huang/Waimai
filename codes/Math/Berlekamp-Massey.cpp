// - [1, 2, 4, 8, 16] -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1] -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - [] -> (0, [1])
// - [0, 0, 0] -> (0, [1])
// - [-2] -> (1, [1, 2])
template<class T>
pair<int, vector<T>> BM(const vector<T>& S) {
	using poly = vector<T>;
	int N = SZ(S);
	poly C_rev{1}, B{1};
	int L = 0, m = 1;
	T b = 1;
	auto adjust = [](poly C, const poly &B, T d, T b, int m) -> poly {
		C.resize(max(SZ(C), SZ(B) + m));
		T a = d / b;
		REP(i, SZ(B)) C[i + m] -= a * B[i];
		return C;
	};
	REP(n, N) {
		T d = S[n];
		REP(i, L) d += C_rev[i + 1] * S[n - 1 - i];
		if(d == 0) m++;
		else if (2 * L <= n) {
			poly Q = C_rev;
			C_rev = adjust(C_rev, B, d, b, m);
			L = n + 1 - L, B = Q, b = d, m = 1;
		} else C_rev = adjust(C_rev, B, d, b, m++);
	}
	return {L, C_rev};
}

// Calculate $x^N \bmod f(x)$
// Complexity: $O(K^2 \log N)$ ($K$: deg. of $f$)
// (4, [1, -1, -1]) -> [2, 3]
// ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2 )
template<class T>
vector<T> monomial_mod_polynomial(long long N, const vector<T> &f_rev) {
	assert(!f_rev.empty() && f_rev[0] == 1);
	int K = SZ(f_rev) - 1;
	if(!K) return {};
	int D = 64 - __builtin_clzll(N);
	vector<T> ret(K, 0);
	ret[0] = 1;
	auto self_conv = [](vector<T> x) -> vector<T> {
		int d = SZ(x);
		vector<T> ret(d * 2 - 1);
		REP(i, d) {
			ret[i * 2] += x[i] * x[i];
			REP(j, i) ret[i + j] += x[i] * x[j] * 2;
		}
		return ret;
	};
	for(int d = D; d--;) {
		ret = self_conv(ret);
		for(int i = 2 * K - 2; i >= K; i--) {
			REP(j, k) ret[i - j - 1] -= ret[i] * f_rev[j + 1];
		}
		ret.resize(K);
		if (N >> d & 1) {
			vector<T> c(K);
			c[0] = -ret[K - 1] * f_rev[K];
			for(int i = 1; i < K; i++) c[i] = ret[i - 1] - ret[K - 1] * f_rev[K - i];
			ret = c;
		}
	}
	return ret;
}

// Guess k-th element of the sequence, assuming linear recurrence
template<class T>
T guess_kth_term(const vector<T>& a, long long k) {
	assert(k >= 0);
	if(k < 1LL * SZ(a)) return a[k];
	auto f = BM<T>(a).second;
	auto g = monomial_mod_polynomial<T>(k, f);
	T ret = 0;
	REP(i, SZ(g)) ret += g[i] * a[i];
	return ret;
}
