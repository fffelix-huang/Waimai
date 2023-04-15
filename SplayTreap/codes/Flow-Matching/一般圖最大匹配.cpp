mt19937 rng(time(0));
struct GeneralMaxMatch {
	int n;
	vector<pair<int, int>> es;
	vector<int> g, vis, mate; // i 與 mate[i] 配對 (mate[i] == -1 代表沒有匹配)
	GeneralMaxMatch(int n) : n(n), g(n, -1), mate(n, -1) {}
	bool dfs(int u) {
		if(vis[u]) return false;
		vis[u] = true;
		for(int ei = g[u]; ei != -1; ) {
			auto [x, y] = es[ei]; ei = y;
			if(mate[x] == -1) {
				mate[mate[u] = x] = u;
				return true;
			}
		}
		for(int ei = g[u]; ei != -1; ) {
			auto [x, y] = es[ei]; ei = y;
			int nu = mate[x];
			mate[mate[u] = x] = u;
			mate[nu] = -1;
			if(dfs(nu)) return true;
			mate[mate[nu] = x] = nu;
			mate[u] = -1;
		}
		return false;
	}
	void add_edge(int a, int b) {
		auto f = [&](int a, int b) {
			es.emplace_back(b, g[a]);
			g[a] = es.size() - 1;
		};
		f(a, b); f(b, a);
	}
	int solve() {
		vector<int> o(n);
		iota(o.begin(), o.end(), 0);
		int ans = 0;
		for(int it = 0; it < 100; ++it) {
			shuffle(o.begin(), o.end(), rng);
			vis.assign(n, false);
			for(auto i : o) if(mate[i] == -1) ans += dfs(i);
		}
		return ans;
	}
};
