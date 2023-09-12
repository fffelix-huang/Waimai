void convex_hull(vector<P>& dots) {
	sort(ALL(dots));
	vector<P> ans(1, dots[0]);
	for(int it = 0; it < 2; it++, reverse(ALL(dots))) {
		for(int i = 1, t = SZ(ans); i < SZ(dots); ans.pb(dots[i++])) {
			while(SZ(ans) > t && ori(ans[SZ(ans) - 2], ans.back(), dots[i]) < 0) {
				ans.ppb();
			}
		}
	}
	ans.ppb();
	swap(ans, dots);
}