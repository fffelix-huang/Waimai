struct LiChao { // min
	int n;
	vector<pll> seg;
	LiChao(int _n) : n(_n) {
		seg.assign(4 * n + 5, pll(0, INF));
	}
	ll cal(pll line, ll x) { return line.F * x + line.S; }
	void insert(int l, int r, int id, pll line) {
		if(l == r) {
			if(cal(line, l) < cal(seg[id], l)) seg[id] = line;
			return;
		}
		int mid = (l + r) / 2;
		if(line.F > seg[id].F) swap(line, seg[id]);
		if(cal(line, mid) <= cal(seg[id], mid)) {
			seg[id] = line;
			insert(l, mid, id * 2, seg[id]);
		}
		else insert(mid + 1, r, id * 2 + 1, line);
	}
	ll query(int l, int r, int id, ll x) {
		if(x < l || x > r) return INF;
		if(l == r) return cal(seg[id], x);
		int mid = (l + r) / 2;
		ll val = 0;
		if(x <= mid) val = query(l, mid, id * 2, x);
		else val = query(mid + 1, r, id * 2 + 1, x);
		return min(val, cal(seg[id], x));
	}
};
