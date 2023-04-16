const ll INF = 9e18L;
vector<P> a;
sort(all(a), [](P a, P b) { return a.x < b.x; });
ll solve(int l, int r) {
	if(l + 1 == r) return INF;
	int m = (l + r) / 2;
	ll d = min(solve(l, m), solve(m, r));
	inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r, [](P a, P b) {
		return a.y < b.y;
	});
	#define SQ(x) ((x) * (x))
	vector<P> p;
	for(int i = l; i < r; ++i) if(SQ(a[i].x - a[m].x) <= d) p.pb(a[i]);
	REP(i, sz(p)) {
		for(int j = i + 1; j < sz(p); ++j) {
			if((p[i].y - p[j].y) * (p[i].y - p[j].y) > d) break;
			d = min(d, SQ(p[i].x - p[j].x) + SQ(p[i].y - p[j].y));
		}
	}
	return d; // 距離平方
}