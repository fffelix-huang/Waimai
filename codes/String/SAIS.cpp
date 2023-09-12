// mississippi
// 10 7 4 1 0 9 8 6 3 5 2
vi SAIS(string a) {
	int n = SZ(a), m = *max_element(ALL(a)) + 1;
	vi pos(m + 1), x(m), sa(n), val(n), lms;
	for(auto c : a) pos[c + 1]++;
	REP(i, m) pos[i + 1] += pos[i];
	vector<bool> s(n);
	IREP(i, n - 1) s[i] = a[i] != a[i + 1] ? a[i] < a[i + 1] : s[i + 1];
	auto ind = [&](const vi& ls){
		fill(ALL(sa), -1);
		auto L = [&](int i) { if(i >= 0 && !s[i]) sa[x[a[i]]++] = i; };
		auto S = [&](int i) { if(i >= 0 && s[i]) sa[--x[a[i]]] = i; };
		REP(i, m) x[i] = pos[i + 1];
		IREP(i, SZ(ls)) S(ls[i]);
		REP(i, m) x[i] = pos[i];
		L(n - 1);
		REP(i, n) L(sa[i] - 1);
		REP(i, m) x[i] = pos[i + 1];
		IREP(i, n) S(sa[i] - 1);
	};
	auto ok = [&](int i) { return i == n || (!s[i - 1] && s[i]); };
	auto same = [&](int i,int j) {
		do {
			if(a[i++] != a[j++]) return false;
		} while(!ok(i) && !ok(j));
		return ok(i) && ok(j);
	};
	FOR(i, 1, n) if(ok(i)) lms.pb(i);
	ind(lms);
	if(SZ(lms)) {
		int p = -1, w = 0;
		for(auto v : sa) if(v && ok(v)) {
			if(p != -1 && same(p, v)) w--;
			val[p = v] = w++;
		}
		auto b = lms;
		for(auto& v : b) v = val[v];
		b = SAIS(b);
		for(auto& v : b) v = lms[v];
		ind(b);
	}
	return sa;
}