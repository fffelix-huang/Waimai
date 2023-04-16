template<class T>
class Dinic {
public:
	struct Edge {
		int from, to;
		T cap;
		Edge(int x, int y, T z) : from(x), to(y), cap(z) {}
	};
	constexpr T INF = 1e9;
	int n;
	vector<Edge> edges;
	vector<vi> g;
	vi cur, h; // h : level graph
	Dinic(int _n) : n(_n), g(_n) {}
	void add_edge(int u, int v, T c) {
		g[u].pb(sz(edges));
		edges.eb(u, v, c);
		g[v].pb(sz(edges));
		edges.eb(v, u, 0);
	}
	bool bfs(int s, int t) {
		h.assign(n, -1);
		queue<int> q;
		h[s] = 0;
		q.push(s);
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(int i : g[u]) {
				const auto& e = edges[i];
				int v = e.to;
				if(e.cap > 0 && h[v] == -1) {
					h[v] = h[u] + 1;
					if(v == t) return true;
					q.push(v);
				}
			}
		}
		return false;
	}
	T dfs(int u, int t, T f) {
		if(u == t) return f;
		T r = f;
		for(int& i = cur[u]; i < sz(g[u]); ++i) {
			int j = g[u][i];
			const auto& e = edges[j];
			int v = e.to;
			T c = e.cap;
			if(c > 0 && h[v] == h[u] + 1) {
				T a = dfs(v, t, min(r, c));
				edges[j].cap -= a;
				edges[j ^ 1].cap += a;
				if((r -= a) == 0) return f;
			}
		}
		return f - r;
	}
	T flow(int s, int t, T f = INF) {
		T ans = 0;
		while(f > 0 && bfs(s, t)) {
			cur.assign(n, 0);
			T cur = dfs(s, t, f);
			ans += cur;
			f -= cur;
		}
		return ans;
	}
};
