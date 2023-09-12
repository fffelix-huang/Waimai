T det(vector<vector<T>> a) {
	int n = SZ(a);
	T ret = 1;
	REP(i, n) {
		int idx = -1;
		FOR(j, i, n) if(a[j][i] != 0) {
			idx = j;
			break;
		}
		if(idx == -1) return 0;
		if(i != idx) {
			ret *= T(-1);
			swap(a[i], a[idx]);
		}
		ret *= a[i][i];
		T inv = T(1) / a[i][i];
		REP(j, n) a[i][j] *= inv;
		FOR(j, i + 1, n) {
			T x = a[j][i];
			if(x == 0) continue;
			FOR(k, i, n) {
				a[j][k] -= a[i][k] * x;
			}
		}
	}
	return ret;
}
