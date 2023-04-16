void convex_hull(vector<P>& dots) {
	sort(all(dots));
	vector<P> ans(1, dots[0]);
	for(int it = 0; it < 2; it++, reverse(all(dots))) {
		for(int i = 1, t = sz(ans); i < sz(dots); ans.pb(dots[i++])) {
			while(sz(ans) > t && ori(ans[sz(ans) - 2], ans.back(), dots[i]) < 0) {
				ans.ppb();
			}
		}
	}
	ans.ppb();
	swap(ans, dots);
}