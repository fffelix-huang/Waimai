// mississippi
// 10 7 4 1 0 9 8 6 3 5 2
vi SAIS(string a) {
	#define QQ(i, n) for(int i = (n); i >= 0; i--)
	int n = sz(a), m = *max_element(all(a)) + 1;
	vi pos(m + 1), x(m), sa(n), val(n), lms;
	for(auto c : a) pos[c + 1]++;
	REP(i, m) pos[i + 1] += pos[i];
	vector<bool> s(n);
	QQ(i, n - 2) s[i] = a[i] != a[i + 1] ? a[i] < a[i + 1] : s[i + 1];
	auto ind = [&](const vi& ls){
		fill(all(sa), -1);
		auto L = [&](int i) { if(i >= 0 && !s[i]) sa[x[a[i]]++] = i; };
		auto S = [&](int i) { if(i >= 0 && s[i]) sa[--x[a[i]]] = i; };
		REP(i, m) x[i] = pos[i + 1];
		QQ(i, sz(ls) - 1) S(ls[i]);
		REP(i, m) x[i] = pos[i];
		L(n - 1);
		REP(i, n) L(sa[i] - 1);
		REP(i, m) x[i] = pos[i + 1];
		QQ(i, n - 1) S(sa[i] - 1);
	};
	auto ok = [&](int i) { return i == n || (!s[i - 1] && s[i]); };
	auto same = [&](int i,int j) {
		do {
			if(a[i++] != a[j++]) return false;
		} while(!ok(i) && !ok(j));
		return ok(i) && ok(j);
	};
	for(int i = 1; i < n; i++) if(ok(i)) lms.pb(i);
	ind(lms);
	if(sz(lms)) {
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