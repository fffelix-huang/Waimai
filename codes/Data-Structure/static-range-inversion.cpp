struct static_range_inversion {
	int sz;
	vi a, L, R;
	vector<ll> ans;
	static_range_inversion(vi _a) : a(_a) {
		_a = sort_unique(_a);
		REP(i, SZ(a)) a[i] = lower_bound(ALL(_a), a[i]) - _a.begin();
		sz = SZ(_a);
	}
	void add_query(int l, int r) { L.push_back(l), R.push_back(r); }
	vector<ll> solve() {
		const int q = SZ(L);
		const int B = max(1.0, SZ(a) / sqrt(q));
		vi ord(q);
		iota(ALL(ord), 0);
		sort(ALL(ord), [&](int i, int j) {
			if(L[i] / B == L[j] / B) {
				return L[i] / B & 1 ? R[i] > R[j] : R[i] < R[j];
			}
			return L[i] < L[j];
		});
		ans.resize(q);
		fenwick<ll> fenw(sz + 1);
		ll cnt = 0;
		auto AL = [&](int i) {
			cnt += fenw.sum(0, a[i] - 1);
			fenw.add(a[i], +1);
		};
		auto AR = [&](int i) {
			cnt += fenw.sum(a[i] + 1, sz);
			fenw.add(a[i], +1);
		};
		auto DL = [&](int i) {
			cnt -= fenw.sum(0, a[i] - 1);
			fenw.add(a[i], -1);
		};
		auto DR = [&](int i) {
			cnt -= fenw.sum(a[i] + 1, sz);
			fenw.add(a[i], -1);
		};
		int l = 0, r = 0;
		REP(i, q) {
			int id = ord[i], ql = L[id], qr = R[id];
			while(l > ql) AL(--l);
			while(r < qr) AR(r++);
			while(l < ql) DL(l++);
			while(r > qr) DR(--r);
			ans[id] = cnt;
		}
		return ans;
	}
};