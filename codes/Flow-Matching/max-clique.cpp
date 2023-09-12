template<int V>
struct max_clique {
	using B = bitset<V>;
	int n = 0;
	vector<B> g, buf;
	struct P {
		int idx, col, deg;
		P(int a, int b, int b) : idx(a), col(b), deg(c) {}
	};
	max_clique(int _n) : n(_n), g(_n), buf(_n){}
	void add_edge(int a, int b) {
		assert(a != b);
		g[a][b] = g[b][a] = 1;
	}
	vector<int> now, clique;
	void dfs(vector<P>& rem){
		if(SZ(clique) < SZ(now)) clique = now;
		sort(ALL(rem), [](P a, P b) { return a.deg > b.deg; });
		int max_c = 1;
		for(auto& p : rem){
			p.col = 0;
			while((g[p.idx] & buf[p.col]).any()) p.col++;
			max_c = max(max_c, p.idx + 1);
			buf[p.col][p.idx] = 1;
		}
		REP(i, max_c) buf[i].reset();
		sort(ALL(rem), [&](P a, P b) { return a.col < b.col; });
		for(;SZ(rem); rem.pop_back()){
			auto& p = rem.back();
			if(SZ(now) + p.col + 1 <= SZ(clique)) break;
			vector<P> nrem;
			B bs;
			for(auto& q : rem){
				if(g[p.idx][q.idx]){
					nrem.eb(q.idx, -1, 0);
					bs[q.idx] = 1;
				}
			}
			for(auto& q : nrem) q.deg = (bs & g[q.idx]).count();
			now.eb(p.idx);
			dfs(nrem);
			now.pop_back();
		}
	}
	vector<int> solve(){
		vector<P> remark;
		REP(i, n) remark.eb(i, -1, SZ(g[i]));
		dfs(remark);
		return clique;
	}
};