template<class T>
struct KM {
	static constexpr T INF = numeric_limits<T>::max();
	int n, ql, qr;
	vector<vector<T>> w;
	vector<T> hl, hr, slk;
	vi fl, fr, pre, qu;
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
		fill(all(slk), INF);
		fill(all(vl), 0);
		fill(all(vr), 0);
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
			REP(x, n) if(!vl[x] && d > slk[x]) d = slk[x];
			REP(x, n) {
				if(vl[x]) hl[x] += d;
				else slk[x] -= d;
				if(vr[x]) hr[x] -= d;
			}
			REP(x, n) if(!vl[x] && !slk[x] && !check(x)) return;
		}
	}
	T solve() {
		fill(all(fl), -1);
		fill(all(fr), -1);
		fill(all(hr), 0);
		REP(i, n) hl[i] = *max_element(all(w[i]));
		REP(i, n) bfs(i);
		T ans = 0;
		REP(i, n) ans += w[i][fl[i]]; // i 跟 fl[i] 配對
		return ans;
	}
};
