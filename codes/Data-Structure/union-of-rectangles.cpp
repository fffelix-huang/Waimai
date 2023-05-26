// 2
// 1 10 1 10
// 0 2 0 2
// ans = 84
vector<int> vx, vy;
struct q { int piv, s, e, x; };
struct tree {
	vector<int> seg, tag;
	tree(int _n) : seg(_n * 16), tag(_n * 16) {}
	void add(int ql, int qr, int x, int v, int l, int r) {
		if(qr <= l || r <= ql) return;
		if(ql <= l && r <= qr) {
			tag[v] += x;
			if(tag[v] == 0) {
				if(l != r) seg[v] = seg[2 * v] + seg[2 * v + 1];
				else seg[v] = 0;
			} else seg[v] = vx[r] - vx[l];
		} else {
			int mid = (l + r) / 2;
			add(ql, qr, x, 2 * v, l, mid);
			add(ql, qr, x, 2 * v + 1, mid, r);
			if(tag[v] == 0 && l != r) seg[v] = seg[2 * v] + seg[2 * v + 1];
		}
	}
	int q() { return seg[1]; }
};
int main() {
	int n; cin >> n;
	vector<int> x1(n), x2(n), y_(n), y2(n);
	for (int i = 0; i < n; i++) {
		cin >> x1[i] >> x2[i] >> y_[i] >> y2[i]; // L R D U
		vx.pb(x1[i]), vx.pb(x2[i]);
		vy.pb(y_[i]), vy.pb(y2[i]);
	}
	vx = sort_unique(vx);
	vy = sort_unique(vy);
	vector<q> a(2 * n);
	REP(i, n) {
		x1[i] = lower_bound(ALL(vx), x1[i]) - vx.begin();
		x2[i] = lower_bound(ALL(vx), x2[i]) - vx.begin();
		y_[i] = lower_bound(ALL(vy), y_[i]) - vy.begin();
		y2[i] = lower_bound(ALL(vy), y2[i]) - vy.begin();
		a[2 * i] = {y_[i], x1[i], x2[i], +1};
		a[2 * i + 1] = {y2[i], x1[i], x2[i], -1};
	}
	sort(ALL(a), [](q a, q b) { return a.piv < b.piv; });
	tree seg(n);
	ll ans = 0;
	REP(i, 2 * n) {
		int j = i;
		while(j < 2 * n && a[i].piv == a[j].piv) {
			seg.add(a[j].s, a[j].e, a[j].x, 1, 0, vx.size());
			j++;
		}
		if(a[i].piv + 1 != SZ(vy)) ans += 1LL * seg.q() * (vy[a[i].piv + 1] - vy[a[i].piv]);
		i = j - 1;
	}
	cout << ans << "\n";
}