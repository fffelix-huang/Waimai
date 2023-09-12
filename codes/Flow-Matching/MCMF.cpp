template<class S, class T>
class MCMF {
public:
	struct Edge {
		int from, to;
		S cap;
		T cost;
		Edge(int u, int v, S x, T y) : from(u), to(v), cap(x), cost(y) {}
	};
	const ll INF = 1E18L;
	int n;
	vector<Edge> edges;
	vector<vi> g;
	vector<T> d;
	vector<bool> inq;
	vi pedge;
	MCMF(int _n) : n(_n), g(_n), d(_n), inq(_n), pedge(_n) {}
	void add_edge(int u, int v, S cap, T cost) {
		g[u].pb(SZ(edges));
		edges.eb(u, v, cap, cost);
		g[v].pb(SZ(edges));
		edges.eb(v, u, 0, -cost);
	}
	bool spfa(int s, int t) {
		bool found = false;
		fill(ALL(d), INF);
		d[s] = 0;
		inq[s] = true;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(u == t) found = true;
			inq[u] = false;
			for(auto& id : g[u]) {
				const auto& e = edges[id];
				if(e.cap > 0 && d[u] + e.cost < d[e.to]) {
					d[e.to] = d[u] + e.cost;
					pedge[e.to] = id;
					if(!inq[e.to]) {
						q.push(e.to);
						inq[e.to] = true;
					}
				}
			}
		}
		return found;
	}
	pair<S, T> flow(int s, int t, S f = INF) {
		S cap = 0;
		T cost = 0;
		while(f > 0 && spfa(s, t)) {
			S send = f;
			int u = t;
			while(u != s) {
				const Edge& e = edges[pedge[u]];
				send = min(send, e.cap);
				u = e.from;
			}
			u = t;
			while(u != s) {
				Edge& e = edges[pedge[u]];
				e.cap -= send;
				Edge& b = edges[pedge[u] ^ 1];
				b.cap += send;
				u = e.from;
			}
			cap += send;
			f -= send;
			cost += send * d[t];
		}
		return {cap, cost};
	}
};
