struct BlockCutTree {
	int n;
	vector<vi> g;
	vi dfn, low, stk;
	int cnt = 0, cur = 0;
	vector<pii> edges;
	BlockCutTree(int _n) : n(_n), g(_n), dfn(_n), low(_n) {}
	void ae(int u, int v) {
		g[u].pb(v);
		g[v].pb(u);
	}
	void dfs(int x) {
		stk.pb(x);
		dfn[x] = low[x] = cur++;
		for(auto y : g[x]) {
			if(dfn[y] == -1) {
				dfs(y);
				low[x] = min(low[x], low[y]);
				if(low[y] == dfn[x]) {
					int v;
					do {
						v = stk.back(), stk.pop_back();
						edges.eb(n + cnt, v);
					} while (v != y);
					edges.eb(x, n + cnt);
					cnt++;
				}
			} else low[x] = min(low[x], dfn[y]);
		}
	}
	pair<int, vector<pii>> work() {
		REP(i, n) {
			if(dfn[i] == -1) {
				stk.clear();
				dfs(i);
			}
		}
		return {cnt, edges};
	}
};
