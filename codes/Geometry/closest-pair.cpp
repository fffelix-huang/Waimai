const ll INF = 9e18L + 5;
vector<P> a;
sort(all(a), [](P a, P b) { return a.x < b.x; });
ll SQ(ll x) { return x * x; }
ll solve(int l, int r) {
	if(l + 1 == r) return INF;
	int m = (l + r) / 2;
	ll midx = a[m].x;
	ll d = min(solve(l, m), solve(m, r));
	inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r, [](P a, P b) {
		return a.y < b.y;
	});
	vector<P> p;
	for(int i = l; i < r; ++i) if(SQ(a[i].x - midx) < d) p.pb(a[i]);
	REP(i, sz(p)) {
		for(int j = i + 1; j < sz(p); ++j) {
		    d = min(d, SQ(p[i].x - p[j].x) + SQ(p[i].y - p[j].y));
			if(SQ(p[i].y - p[j].y) > d) break;
		}
	}
	return d; // 距離平方
}