template<class T, T (*op)(T, T)>
struct sparse_table {
	int n;
	vector<vector<T>> b;
	sparse_table(const vector<T>& a) : n(SZ(a)) {
		int lg = __lg(n) + 1;
		b.resize(lg); b[0] = a;
		FOR(j, 1, lg) {
			b[j].resize(n - (1 << j) + 1);
			REP(i, n - (1 << j) + 1) b[j][i] = op(b[j - 1][i], b[j - 1][i + (1 << (j - 1))]);
		}
	}
	T prod(int from, int to) {
		int lg = __lg(to - from + 1);
		return op(b[lg][from], b[lg][to - (1 << lg) + 1]);
	}
};
