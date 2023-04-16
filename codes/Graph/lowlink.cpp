struct lowlink {
	int n, cnt = 0, tecc_cnt = 0, tvcc_cnt = 0;
	vector<vector<pii>> g;
	vector<pii> edges;
	vi roots, id, low, tecc_id, tvcc_id;
	vector<bool> is_bridge, is_cut, is_tree_edge;
	lowlink(int _n) : n(_n), g(_n), is_cut(_n, false), id(_n, -1), low(_n, -1) {}
	void add_edge(int u, int v) {
		g[u].eb(v, sz(edges));
		g[v].eb(u, sz(edges));
		edges.eb(u, v);
		is_bridge.pb(false);
		is_tree_edge.pb(false);
		tvcc_id.pb(-1);
	}
	void dfs(int u, int peid = -1) {
		static vi stk;
		static int rid;
		if(peid < 0) rid = cnt;
		if(peid == -1) roots.pb(u);
		id[u] = low[u] = cnt++;
		for(auto [v, eid] : g[u]) {
			if(eid == peid) continue;
			if(id[v] < id[u]) stk.pb(eid);
			if(id[v] >= 0) {
				low[u] = min(low[u], id[v]);
			} else {
				is_tree_edge[eid] = true;
				dfs(v, eid);
				low[u] = min(low[u], low[v]);
				if((id[u] == rid && id[v] != rid + 1) || (id[u] != rid && low[v] >= id[u])) {
					is_cut[u] = true;
				}
				if(low[v] >= id[u]) {
					while(true) {
						int e = stk.back();
						stk.pop_back();
						tvcc_id[e] = tvcc_cnt;
						if(e == eid) break;
					}
					tvcc_cnt++;
				}
			}
		}
	}
	void build() {
		REP(i, n) if(id[i] < 0) dfs(i);
		REP(i, sz(edges)) {
			auto [u, v] = edges[i];
			if(id[u] > id[v]) swap(u, v);
			is_bridge[i] = (id[u] < low[v]);
		}
	}
	vector<vi> two_ecc() { // 邊雙
		tecc_cnt = 0;
		tecc_id.assign(n, -1);
		vi stk;
		REP(i, n) {
			if(tecc_id[i] != -1) continue;
			tecc_id[i] = tecc_cnt;
			stk.pb(i);
			while(sz(stk)) {
				int u = stk.back(); stk.pop_back();
				for(auto [v, eid] : g[u]) {
					if(tecc_id[v] >= 0 || is_bridge[eid]) {
						continue;
					}
					tecc_id[v] = tecc_cnt;
					stk.pb(v);
				}
			}
			tecc_cnt++;
		}
		vector<vi> comp(tecc_cnt);
		REP(i, n) comp[tecc_id[i]].pb(i);
		return comp;
	}
	vector<vi> bcc_vertices() { // 點雙
		vector<vi> comp(tvcc_cnt);
		REP(i, sz(edges)) {
			comp[tvcc_id[i]].pb(edges[i].first);
			comp[tvcc_id[i]].pb(edges[i].second);
		}
		for(auto& v : comp) {
			sort(all(v));
			v.erase(unique(all(v)), v.end());
		}
		REP(i, n) if(g[i].empty()) comp.pb({i});
		return comp;
	}
	vector<vi> bcc_edges() {
		vector<vi> ret(tvcc_cnt);
		REP(i, sz(edges)) ret[tvcc_id[i]].pb(i);
		return ret;
	}
};