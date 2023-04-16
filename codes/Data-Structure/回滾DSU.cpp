struct RollbackDSU {
	int n; vi sz, tag;
	vector<tuple<int, int, int, int>> op;
	void init(int _n) {
		n = _n;
		sz.assign(n, -1);
		tag.clear();
	}
	int leader(int x) {
		while(sz[x] >= 0) x = sz[x];
		return x;
	}
	bool merge(int x, int y) {
		x = leader(x), y = leader(y);
		if(x == y) return false;
		if(-sz[x] < -sz[y]) swap(x, y);
		op.eb(x, sz[x], y, sz[y]);
		sz[x] += sz[y]; sz[y] = x;
		return true;
	}
	int size(int x) { return -sz[leader(x);] }
	void add_tag() { tag.pb(sz(op)); }
	void rollback() {
		int z = tag.back(); tag.ppb();
		while(sz(op) > z) {
			auto [x, sx, y, sy] = op.back(); op.ppb();
			sz[x] = sx;
			sz[y] = sy;
		}
	}
};
