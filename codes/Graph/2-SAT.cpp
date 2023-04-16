struct two_sat {
	int n; SCC g;
	vector<bool> ans;
	two_sat(int _n) : n(_n), g(_n * 2) {}
	void add_or(int u, bool x, int v, bool y) {
		g.add_edge(2 * u + !x, 2 * v + y);
		g.add_edge(2 * v + !y, 2 * u + x);
	}
	bool solve() {
		ans.resize(n);
		auto id = g.solve();
		REP(i, n) {
			if(id[2 * i] == id[2 * i + 1]) return false;
			ans[i] = (id[2 * i] < id[2 * i + 1]);
		}
		return true;
	}
};