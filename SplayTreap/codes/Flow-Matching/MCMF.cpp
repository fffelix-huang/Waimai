template<class S, class T>
class MCMF {
public:
	struct Edge {
		int from;
		int to;
		S cap;
		T cost;
		Edge(int u, int v, S x, T y) : from(u), to(v), cap(x), cost(y) {}
	};
	static constexpr S CAP_INF = numeric_limits<S>::max();
	static constexpr T COST_INF = numeric_limits<T>::max();
	int n;
	vector<Edge> edges;
	vector<vector<int>> g;
	vector<T> d;
	vector<bool> inq;
	vector<int> prev_edge;

	MCMF() : n(0) {}
	explicit MCMF(int _n) : n(_n), g(_n), d(_n), inq(_n), prev_edge(_n) {}

	void add_edge(int u, int v, S cap, T cost) {
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		g[u].push_back(edges.size());
		edges.emplace_back(u, v, cap, cost);
		g[v].push_back(edges.size());
		edges.emplace_back(v, u, 0, -cost);
	}

	bool spfa(int s, int t) {
		bool found = false;
		fill(d.begin(), d.end(), COST_INF);
		d[s] = 0;
		inq[s] = true;
		queue<int> que;
		que.push(s);
		while(!que.empty()) {
			int u = que.front(); que.pop();
			if(u == t) found = true;
			inq[u] = false;
			for(auto& id : g[u]) {
				const Edge& e = edges[id];
				if(e.cap > 0 && d[u] + e.cost < d[e.to]) {
					d[e.to] = d[u] + e.cost;
					prev_edge[e.to] = id;
					if(!inq[e.to]) {
						que.push(e.to);
						inq[e.to] = true;
					}
				}
			}
		}
		return found;
	}

	pair<S, T> flow(int s, int t, S f = CAP_INF) {
		assert(0 <= s && s < n);
		assert(0 <= t && t < n);
		S cap = 0;
		T cost = 0;
		while(f > 0 && spfa(s, t)) {
			S send = f;
			int u = t;
			while(u != s) {
				const Edge& e = edges[prev_edge[u]];
				send = min(send, e.cap);
				u = e.from;
			}
			u = t;
			while(u != s) {
				Edge& e = edges[prev_edge[u]];
				e.cap -= send;
				Edge& b = edges[prev_edge[u] ^ 1];
				b.cap += send;
				u = e.from;
			}
			cap += send;
			f -= send;
			cost += send * d[t];
		}
		return make_pair(cap, cost);
	}
};
