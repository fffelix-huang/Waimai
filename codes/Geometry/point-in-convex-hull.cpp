int point_in_convex_hull(const vector<P>& a, P p) {
	// -1 ON, 0 OUT, +1 IN
	// 要先逆時針排序
	int n = sz(a);
	if(btw(a[0], a[1], p) || btw(a[0], a[n - 1], p)) return -1;
	int l = 0, r = n - 1;
	while(l <= r) {
		int m = (l + r) / 2;
		auto a1 = cross(a[m] - a[0], p - a[0]);
		auto a2 = cross(a[(m + 1) % n] - a[0], p - a[0]);
		if(a1 >= 0 && a2 <= 0) {
			auto res = cross(a[(m + 1) % n] - a[m], p - a[m]);
			return res > 0 ? 1 : (res >= 0 ? -1 : 0);
		}
		if(a1 < 0) r = m - 1;
		else l = m + 1;
	}
	return 0;
}