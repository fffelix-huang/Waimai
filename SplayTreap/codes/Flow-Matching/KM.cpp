template<class T>
struct KM {
	static constexpr T INF = numeric_limits<T>::max();
	int n, ql, qr;
	vector<vector<T>> w;
	vector<T> hl, hr, slk;
	vector<int> fl, fr, pre, qu;
	vector<bool> vl, vr;
	KM(int n) : n(n), w(n, vector<T>(n, -INF)), hl(n), hr(n), slk(n), fl(n), fr(n), pre(n), qu(n), vl(n), vr(n) {}
	void add_edge(int u, int v, int x) { w[u][v] = x; } // 最小值要加負號
	bool check(int x) {
		vl[x] = 1;
		if(fl[x] != -1) return vr[qu[qr++] = fl[x]] = 1;
		while(x != -1) swap(x, fr[fl[x] = pre[x]]);
		return 0;
	}
	void bfs(int s) {
		fill(slk.begin(), slk.end(), INF);
		fill(vl.begin(), vl.end(), 0);
		fill(vr.begin(), vr.end(), 0);
		ql = qr = 0, qu[qr++] = s, vr[s] = 1;
		while(true) {
			T d;
			while(ql < qr) {
				for(int x = 0, y = qu[ql++]; x < n; ++x) {
					if(!vl[x] && slk[x] >= (d = hl[x] + hr[y] - w[x][y])) {
						pre[x] = y;
						if(d) slk[x] = d;
						else if(!check(x)) return;
					}
				}
			}
			d = INF;
			for(int x = 0; x < n; ++x) if(!vl[x] && d > slk[x]) d = slk[x];
			for(int x = 0; x < n; ++x) {
				if(vl[x]) hl[x] += d;
				else slk[x] -= d;
				if(vr[x]) hr[x] -= d;
			}
			for(int x = 0; x < n; ++x) if(!vl[x] && !slk[x] && !check(x)) return;
		}
	}
	T solve() {
		fill(fl.begin(), fl.end(), -1);
		fill(fr.begin(), fr.end(), -1);
		fill(hr.begin(), hr.end(), 0);
		for(int i = 0; i < n; ++i) hl[i] = *max_element(w[i].begin(), w[i].end());
		for(int i = 0; i < n; ++i) bfs(i);
		T ans = 0;
		for(int i = 0; i < n; ++i) ans += w[i][fl[i]]; // i 跟 fl[i] 配對
		return ans;
	}
};
