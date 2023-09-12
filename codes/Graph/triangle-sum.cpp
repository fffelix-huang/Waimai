// Three vertices a < b < cconnected by three edges {a, b}, {a, c}, {b, c}. Find xa * xb * xc over all triangles.
int triangle_sum(vector<array<int, 2>> edges, vi x) {
	int n = SZ(x);
	vi deg(n);
	vector<vi> g(n);
	for(auto& [u, v] : edges) {
		if(u > v) swap(u, v);
		deg[u]++, deg[v]++;
	}
	REP(i, n) g[i].reserve(deg[i]);
	for(auto [u, v] : edges) {
		if(deg[u] > deg[v]) swap(u, v);
		g[u].pb(v);
	}
	vi val(n);
	__int128 ans = 0;
	REP(a, n) {
		for(auto b : g[a]) val[b] = x[b];
		for(auto b : g[a]) {
			ll tmp = 0;
			for(auto c : g[b]) tmp += val[c];
			ans += __int128(tmp) * x[a] * x[b];
		}
		for(auto b : g[a]) val[b] = 0;
	}
	return ans % mod;
}