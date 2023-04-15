struct RollbackDSU {
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
		op.emplace_back(x, sz[x], y, sz[y]);
		sz[x] += sz[y];
		sz[y] = x;
		return true;
	}
	int size(int x) { return -sz[leader(x);] }
	void add_tag() { tag.push_back(op.size()); }
	void rollback() {
		int z = tag.back(); tag.pop_back();
		while(sz(op) > z) {
			auto [x, sx, y, sy] = op.back(); op.pop_back();
			sz[x] = sx;
			sz[y] = sy;
		}
	}
	int n;
	vector<int> sz, tag;
	vector<tuple<int, int, int, int>> op;
};
