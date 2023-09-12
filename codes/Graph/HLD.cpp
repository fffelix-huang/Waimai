struct HLD {
	int n;
	vector<vi> g;
	vi siz, par, depth, top, tour, fi, id;
	sparse_table<pii, min> st;
	HLD(int _n) : n(_n), g(_n), siz(_n), par(_n), depth(_n), top(_n), fi(_n), id(_n) {
		tour.reserve(n);
	}
	void add_edge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build(int root = 0) {
		par[root] = -1;
		top[root] = root;
		vector<pii> euler_tour;
		euler_tour.reserve(2 * n - 1);
		dfs_sz(root);
		dfs_link(euler_tour, root);
		st = sparse_table<pii, min>(euler_tour);
	}
	int get_lca(int u, int v) {
		int L = fi[u], R = fi[v];
		if(L > R) swap(L, R);
		return st.prod(L, R).second;
	}
	bool is_anc(int u, int v) {
		return id[u] <= id[v] && id[v] < id[u] + siz[u];
	}
	bool on_path(int a, int b, int x) {
		return (is_ancestor(x, a) || is_ancestor(x, b)) && is_ancestor(get_lca(a, b), x);
	}
	int get_dist(int u, int v) {
		return depth[u] + depth[v] - 2 * depth[(get_lca(u, v))];
	}
	int kth_anc(int u, int k) {
		if(depth[u] < k) return -1;
		int d = depth[u] - k;
		while(depth[top[u]] > d) u = par[top[u]];
		return tour[id[u] + d - depth[u]];
	}
	int kth_node_on_path(int a, int b, int k) {
		int z = get_lca(a, b);
		int fi = depth[a] - depth[z];
		int se = depth[b] - depth[z];
		if(k < 0 || k > fi + se) return -1;
		if(k < fi) return kth_anc(a, k);
		return kth_anc(b, fi + se - k);
	}
	vector<pii> get_path(int u, int v, bool include_lca = true) {
		if(u == v && !include_lca) return {};
		vector<pii> seg;
		while(top[u] != top[v]) {
			if(depth[top[u]] > depth[top[v]]) swap(u, v);
			seg.eb(id[top[v]], id[v]);
			v = par[top[v]];
		}
		if(depth[u] > depth[v]) swap(u, v); // u is lca
		if(u != v || include_lca) seg.eb(id[u] + !include_lca, id[v]);
		return seg;
	}
	void dfs_sz(int u) {
		if(par[u] != -1) g[u].erase(find(ALL(g[u]), par[u]));
		siz[u] = 1;
		for(auto& v : g[u]) {
			par[v] = u;
			depth[v] = depth[u] + 1;
			dfs_sz(v);
			siz[u] += siz[v];
			if(siz[v] > siz[g[u][0]]) swap(v, g[u][0]);
		}
	}
	void dfs_link(vector<pii>& euler_tour, int u) {
		fi[u] = SZ(euler_tour);
		id[u] = SZ(tour);
		euler_tour.eb(depth[u], u);
		tour.pb(u);
		for(auto v : g[u]) {
			top[v] = (v == g[u][0] ? top[u] : v);
			dfs_link(euler_tour, v);
			euler_tour.eb(depth[u], u);
		}
	}
};