struct SCC {
	int n;
	vector<vi> g, h;
	SCC(int _n) : n(_n), g(_n), h(_n) {}
	void add_edge(int u, int v) {
		g[u].pb(v);
		h[v].pb(u);
	}
	vi solve() { // 回傳縮點的編號
		vi id(n), top;
		top.reserve(n);
		function<void(int)> dfs1 = [&](int u) {
			id[u] = 1;
			for(auto v : g[u]) if(id[v] == 0) dfs1(v);
			top.pb(u);
		};
		REP(v, n) if(id[v] == 0) dfs1(v);
		fill(ALL(id), -1);
		function<void(int, int)> dfs2 = [&](int u, int x) {
			id[u] = x;
			for(auto v : h[u]) if(id[v] == -1) dfs2(v, x);
		};
		for(int i = n - 1, cnt = 0; i >= 0; --i) {
			int u = top[i];
			if(id[u] == -1) dfs2(u, cnt++);
		}
		return id;
	}
};