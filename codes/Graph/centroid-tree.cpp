pair<int, vector<vi>> centroid_tree(const vector<vi>& g) {
	int n = sz(g);
	vi siz(n);
	vector<bool> vis(n);
	auto dfs_sz = [&](auto f, int u, int p) -> void {
		siz[u] = 1;
		for(auto v : g[u]) {
			if(v == p || vis[v]) continue;
			f(f, v, u);
			siz[u] += siz[v];
		}
	};
	auto find_cd = [&](auto f, int u, int p, int all) -> int {
		for(auto v : g[u]) {
			if(v == p || vis[v]) continue;
			if(siz[v] * 2 > all) return f(f, v, u, all);
		}
		return u;
	};
	vector<vi> h(n);
	auto build = [&](auto f, int u) -> int {
		dfs_sz(dfs_sz, u, -1);
		int cd = find_cd(find_cd, u, -1, siz[u]);
		vis[cd] = true;
		for(auto v : g[cd]) {
			if(vis[v]) continue;
			int child = f(f, v);
			h[cd].pb(child);
		}
		return cd;
	};
	int root = build(build, 0);
	return {root, h};
}
