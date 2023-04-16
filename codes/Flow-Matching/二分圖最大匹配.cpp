struct bipartite_matching {
	int n, m; // 二分圖左右人數 (0 ~ n-1), (0 ~ m-1)
	vector<vi> g;
	vi lhs, rhs, dist; // i 與 lhs[i] 配對 (lhs[i] == -1 代表沒有配對)
	bipartite_matching(int _n, int _m) : n(_n), m(_m), g(_n), lhs(_n, -1), rhs(_m, -1), dist(_n) {}
	void add_edge(int u, int v) { g[u].pb(v); }
	void bfs() {
		queue<int> q;
		REP(i, n) {
			if(lhs[i] == -1) {
				q.push(i);
				dist[i] = 0;
			} else {
				dist[i] = -1;
			}
		}
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(auto v : g[u]) {
				if(rhs[v] != -1 && dist[rhs[v]] == -1) {
					dist[rhs[v]] = dist[u] + 1;
					q.push(rhs[v]);
				}
			}
		}
	}
	bool dfs(int u) {
		for(auto v : g[u]) {
			if(rhs[v] == -1) {
				rhs[lhs[u] = v] = u;
				return true;
			}
		}
		for(auto v : g[u]) {
			if(dist[rhs[v]] == dist[u] + 1 && dfs(rhs[v])) {
				rhs[lhs[u] = v] = u;
				return true;
			}
		}
		return false;
	}
	int solve() {
		int ans = 0;
		while(true) {
			bfs();
			int aug = 0;
			REP(i, n) if(lhs[i] == -1) aug += dfs(i);
			if(!aug) break;
			ans += aug;
		}
		return ans;
	}
};
