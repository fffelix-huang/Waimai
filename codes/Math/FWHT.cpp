#define ppc __builtin_popcount
template<class T, class F>
void fwht(vector<T>& a, F f) {
	int n = SZ(a);
	assert(ppc(n) == 1);
	for(int i = 1; i < n; i <<= 1) {
		for(int j = 0; j < n; j += i << 1) {
			REP(k, i) f(a[j + k], a[i + j + k]);
		}
	}
}
template<class T>
void or_transform(vector<T>& a, bool inv) { fwht(a, [&](T& x, T& y) { y += x * (inv ? -1 : +1); }) }
template<class T>
void and_transform(vector<T>& a, bool inv) { fwht(a, [&](T& x, T& y) { x += y * (inv ? -1 : +1); }); }
template<class T>
void xor_transform(vector<T>& a, bool inv) {
	fwht(a, [](T& x, T& y) {
		T z = x + y;
		y = x - y;
		x = z;
	});
	if(inv) {
		T z = T(1) / T(SZ(a));
		for(auto& x : a) x *= z;
	}
}
template<class T>
vector<T> convolution(vector<T> a, vector<T> b) {
	assert(SZ(a) == SZ(b));
	transform(a, false), transform(b, false);
	REP(i, SZ(a)) a[i] *= b[i];
	transform(a, true);
	return a;
}
template<class T>
vector<T> subset_convolution(const vector<T>& f, const vector<T>& g) {
	assert(SZ(f) == SZ(g));
	int n = SZ(f);
	assert(ppc(n) == 1);
	const int lg = __lg(n);
	vector<vector<T>> fhat(lg + 1, vector<T>(n)), ghat(fhat);
	REP(i, n) fhat[ppc(i)][i] = f[i], ghat[ppc(i)][i] = g[i];
	REP(i, lg + 1) or_transform(fhat[i], false), or_transform(ghat[i], false);
	vector<vector<T>> h(lg + 1, vector<T>(n));
	REP(m, n) REP(i, lg + 1) REP(j, i + 1) h[i][m] += fhat[j][m] * ghat[i - j][m];
	REP(i, lg + 1) or_transform(h[i], true);
	vector<T> res(n);
	REP(i, n) res[i] = h[ppc(i)][i];
	return res;
}
